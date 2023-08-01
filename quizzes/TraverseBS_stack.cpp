#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int d, Node *l, Node *r): data(d), left(l), right(r){}
};

void Traverse(Node *root)
{
    if(root == NULL)
    {
        return;
    }
    Traverse(root->left);
    cout << root->data << endl;
    Traverse(root->right);
}

void TraverseIter(Node *root)
{
    stack<Node *> st;
    Node *tmp = root;

    while(tmp != NULL || !st.empty())
    {
        while (tmp != NULL)
        {
            st.push(tmp);
            tmp = tmp->left;
        }

        tmp = st.top();
        st.pop();
        cout <<  tmp->data << endl;
        tmp = tmp->right;
    }
}

void TraverseLevel(Node *root)
{
    queue<Node*> q;
    Node *tmp = root;

    q.push(tmp);

    while(!q.empty())
    {
        tmp = q.front();
        if(tmp->left)
        {
            q.push(tmp->left);
        }
        if(tmp->right)
        {
            q.push(tmp->right);
        }

        cout <<  tmp->data << ' ';
        q.pop();
    }
}

int main()
{
    Node *node1 = new Node(10, NULL, NULL);
    Node *node2 = new Node(15, NULL, NULL);
    Node *node3 = new Node(20, NULL, NULL);
    Node *node4 = new Node(7, NULL, NULL);
    Node *node5 = new Node(5, NULL, NULL);
    Node *node6 = new Node(9, NULL, NULL);

    node1->right = node2;
    node1->left = node4;
    node2->right = node3;
    node4->left = node5;
    node4->right = node6;

    TraverseLevel(node1);

    return 0;
}