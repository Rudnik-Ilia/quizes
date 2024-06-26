#include <iostream>
#include <cstdlib>

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

void Show(node_t* root)
{
    if(root == NULL)
    {
        return;
    }
    Show(root->left);
    cout << root->data << endl;
    Show(root->right);
}

void Show_List(node_t* root)
{
    node_t* iter = root;
    while (iter != NULL)
    {
        cout << iter->data << endl;
        iter = iter->right;
    }
}

void Convert(node_t* root, node_t* head)
{
    if(root == NULL)
    {
        return;
    }

    static node_t* prev = NULL;

    Convert(root->left, head);

    if(prev == NULL)
    {
        head = root;
    }
    else
    {
        root->left = prev;
        prev->right = root;
    }

    prev = root;

    Convert(root->right, head);
}

int Len(node_t* root)
{
    if(root == NULL)
    {
        return 0;
    }

    int left = Len(root->left);
    int right = Len(root->right);

    std::cout << left << ' ' << right << std::endl;

    return 1 + ((left >= right) ? left : right);
} 





int main()
{
    node_t * node1 = CreateNode(10);
    node_t * node2 = CreateNode(6);
    node_t * node3 = CreateNode(14);
    node_t * node4 = CreateNode(4);
    node_t * node5 = CreateNode(8);

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;

    node_t * ptr = node1;

    Show(node1);

    Convert(ptr, node1);

    Show_List(node4);

    return 0;
}