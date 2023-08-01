#include <iostream>
#include <queue>
#include <stack>

typedef struct Node node_t;

struct Node
{
    int data;
    node_t * left;
    node_t * right;
    Node(int data, node_t* left = nullptr, node_t* right = nullptr): data(data), left(left), right(right){}
};

void Print(node_t* root)
{
    if(root == nullptr)
    {
        return;
    }
    Print(root->left);
    std::cout << root->data << ' ';
    Print(root->right);
}

void Print_by_Level(node_t* root)
{
    std::queue<node_t*> q;
    q.push(root);

    while(!q.empty())
    {
        int level = q.size();

        for (size_t i = 0; i < level; ++i)
        {
            node_t * tmp = q.front();
            q.pop();

            std::cout << tmp->data << ' ';

            if(tmp->left)
            {
                q.push(tmp->left);
            }

            if(tmp->right)
            {
                q.push(tmp->right);
            }

        }  
        std::cout << std::endl;
    }  
}

void Print_Iter(node_t* root)
{
    std::stack<node_t*> st;
    node_t* tmp = root;

    while(!st.empty() || tmp != nullptr)
    {
        while (tmp != nullptr)
        {
            st.push(tmp);
            tmp = tmp->left;
        }
        tmp = st.top();
        std::cout << tmp->data << std::endl;
        st.pop();
        tmp = tmp->right;   
    }
}



int main()
{
    node_t* root = new Node(4, new Node(2, new Node(1), new Node(3)), new Node(6, new Node(5), new Node(7)));
    // Print_Iter(root);

    std::cout << ((-1lu) == (~0lu)) << std::endl;



    return 0;
}