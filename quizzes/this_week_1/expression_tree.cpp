#include <iostream>

typedef struct Node node_t;

struct Node
{
    char data;
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
    std::cout << (int)root->data << ' ';
    Print(root->right);
}

int Action(char data, int left, int right)
{
    switch (data)
    {
        case '*':
            return left * right;
            break;
        case '+':
            return left + right;
            break;
        case '/':
            return left / right;
            break;
        default:
            return 0;
            break;
    }
}

int Calculate(node_t* root)
{
    if(root->left == nullptr && root->right == nullptr)
    {
        return root->data - 48;
    }

    int left = Calculate(root->left);
    int right = Calculate(root->right);

    return Action(root->data, left, right);   
}





int main()
{
    node_t* root = new Node('*', new Node('+', new Node('2'), new Node('2')), new Node('+', new Node('4'), new Node('5')));

    std::cout << Calculate(root) << std::endl;

    return 0;
}