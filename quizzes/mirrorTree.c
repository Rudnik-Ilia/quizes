#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *right;
    struct Node *left;
};

struct Node* CreateNode(int data)
{
    struct Node* new = malloc(sizeof(struct Node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

void Traverse(struct Node* root)
{
    if(root == NULL)
    {
        return;
    }
    Traverse(root->left);
    printf("%d ", root->data);
    Traverse(root->right);
}

void Mirror(struct Node* root)
{
    struct Node* tmp = NULL;

    if(root == NULL)
    {
        return;
    }
    
    Mirror(root->left);
    Mirror(root->right);

    tmp = root->left;
    root->left = root->right;
    root->right = tmp;
}

int main()
{

    struct Node* root = CreateNode(10);
    struct Node* node1 = CreateNode(5);
    struct Node* node2= CreateNode(15);
    struct Node* node3 = CreateNode(1);
    struct Node* node4 = CreateNode(3);
    struct Node* node5 = CreateNode(20);

    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->right = node5;

    Traverse(root);

    Mirror(root);

    Traverse(root);


    return 0;
}