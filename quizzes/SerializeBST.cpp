#include <iostream>
#include <vector>
#include <stack>
#include <limits>

using namespace std;

typedef struct node node_t;

struct node
{
    int data;
    node_t *left;
    node_t *right;
};

node_t *CreateNode(int data)
{
    node_t* node = (node_t *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

node_t* Deserialize(vector<int> inorder, vector<int> postorder)
{
    if(inorder.size() == 0 || postorder.size() == 0)
    {
        return NULL;
    }
    
    node_t *root = CreateNode(postorder[postorder.size() - 1]);
    node_t *node = NULL;
    int min_val = 0;


    stack<pair<node_t *, int>> st;
    st.push({root, numeric_limits<int>::max()});

    for(int i = (postorder.size() - 2); i >= 0; --i)
    {
        node_t *new_node = CreateNode(postorder[i]);

        node = st.top().first;
        min_val = st.top().second;

        if(new_node->data > node->data)
        {
            node->right = new_node;
            st.push({new_node, node->data});
        }
        else
        {
            while(new_node->data < st.top().second && st.top().second != numeric_limits<int>::max())
            {
                st.pop();
            }

            node = st.top().first;
            min_val = st.top().second;

            node->left = new_node;
            st.push({new_node, min_val});
        }        
    }
    return root;

}

void Traverse(node_t* root)
{
    if(root == NULL)
    {
        return;
    }

    Traverse(root->left);
    cout << root->data << endl;
    Traverse(root->right);
}

int main()
{
    vector<int> inorder = {5,7,9,10,15,20};
    vector<int> postorder = {5,9,7,20,15,10};

    node_t *root = Deserialize(inorder, postorder);

    Traverse(root);




    return 0;
}