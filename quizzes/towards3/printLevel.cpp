#include <iostream>
#include <queue>
#include <stack>
#include <deque>

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

    int side = 0;

    while(!q.empty())
    {
        int level = q.size();

        while (level)
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
            --level;

        }  
        std::cout << std::endl;
    }
}
void Print_by_Level_Zig(node_t* root)
{
    std::deque<node_t*> q;
    q.push_front(root);

    int side = 1;

    while(!q.empty())
    {
        int level = q.size();

        while (level)
        {
            node_t * tmp;
            if(side == 0)
            {
                tmp = q.back();
                q.pop_back();
            }
            else
            {
                tmp = q.front();
                q.pop_front();
            }

            std::cout << tmp->data << ' ';

            if(tmp->left)
            {
                q.push_front(tmp->left);
            }

            if(tmp->right)
            {
                q.push_front(tmp->right);
            }
            --level;

        } 

        if(side == 0)
        {
            side = 1;
        }
        else
        {
            side = 0;
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

int High_Tree(node_t* root)
{
    if(root == NULL)
    {
        return 0;
    }

    int left = High_Tree(root->left);
    int right = High_Tree(root->right);

    return left > right ? 1 + left : 1 + right;
}

int main()
{
    node_t* root = new Node(4, new Node(2, new Node(1), new Node(3)), new Node(6, new Node(5), new Node(7)));
    // Print_Iter(root);
    Print_by_Level_Zig(root);

    // std::cout << High_Tree(root) << std::endl;



    return 0;
}