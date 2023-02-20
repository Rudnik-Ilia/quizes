#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef struct node node_t;
typedef struct bst bst_t;
typedef struct linklist ll_t;

struct node
{
    int data;
    node_t *left;
    node_t *right;
    
};

struct bst
{
    int data;
    bst_t *next;
};

struct linklist
{
    bst_t *start;
    bst_t *end;
    size_t len;
};


node_t *CreateNode(int data)
{
    node_t* node = (node_t *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bst_t *CreateBst(int data)
{
    bst_t* node = (bst_t *)malloc(sizeof(struct bst));
    node->data = data;
    node->next = NULL;
    return node;
}

ll_t *CreateList(int data)
{
    ll_t* list = (ll_t *)malloc(sizeof(struct linklist));
    list->len = 1;
    bst_t *nod = CreateBst(data);
    list->start= nod;
    list->end = nod;
    return list;
}

void InsertBst(ll_t* root, int data)
{
    bst_t *nod = CreateBst(data);
    root->end->next = nod;
    root->end = nod;
    ++(root->len);
}

void DeletetBst(ll_t* root)   // need dummy
{   
    bst_t *iter = NULL;; 
    for(iter = root->start; iter->next->next != NULL; iter = iter->next);
    free(iter->next);
    iter->next = NULL;
    --(root->len);
}

bst_t* Find(ll_t *root, int data)
{
    bst_t *iter = NULL;; 
    for(iter = root->start; iter != NULL; iter = iter->next)
    {
        if(iter->data == data)
        {
            return iter;
        }
    }
    return NULL;

}

void ShowTree(node_t* root)
{
    if(root == NULL)
    {
        return;
    }
    ShowTree(root->left);
    cout << (root->data)<< ' ';
    ShowTree(root->right);

}

void ShowBst(bst_t* root)
{
    bst_t *iter = root;
    while(iter != NULL)
    {
        cout << (iter->data)<< ' ';
        iter = iter->next;
    }
}

size_t Size(ll_t* root)
{
    return root->len;
}

void Flip(bst_t *root)
{
    bst_t *prev = NULL;
    bst_t *curr = root;
    bst_t *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
}
/**************************************************************/

void Lock(ll_t *one, ll_t *two, int pos)
{
    bst_t *iter = NULL;
    int i = 0;
    for(iter = one->start, i = 0; iter != NULL; iter = iter->next, ++i)
    {
        if(i == pos)
        {
            two->end->next = iter;
            return;
        }
    }

}
void FollowList(ll_t *list)
{
    bst_t *iter = list->start;
    while (iter != NULL)
    {
        cout << iter->data << ' ';
        iter = iter->next;
    } 
}


int main()
{
    // node_t *node1 = CreateNode(10);
    // node1->left = CreateNode(5);
    // node1->right = CreateNode(15);
    // node1->left->left = CreateNode(1);
    // node1->left->right = CreateNode(3);
    // Show(node1);



    // bst_t* node1 = CreateBst(1);
    // bst_t* node2 = CreateBst(2);
    // bst_t* node3 = CreateBst(3);
    // bst_t* node4 = CreateBst(4);



    // node1->next = node2;
    // node1->next->next = node3;
    // node1->next->next->next = node4;

    // ShowBst(node1);
    // Flip(node1);
    // ShowBst(node4);

    ll_t *list = CreateList(1);
    InsertBst(list, 2);
    InsertBst(list, 3);
    InsertBst(list, 4);
    InsertBst(list, 5);
    ShowBst(list->start);
    cout << Size(list) << endl;

    cout << "-------------------" << endl;;

    ll_t *list2= CreateList(11);
    InsertBst(list2, 22);
    InsertBst(list2, 33);
    InsertBst(list2, 44);
    InsertBst(list2, 55);
    ShowBst(list2->start);
    cout << Size(list2) << endl;

    Lock(list, list2, 3);

    bst_t *s = Find(list2, 5);
    cout << s->data << endl;

    FollowList(list2);
    cout << "-------------------" << endl;;
    FollowList(list);



   






    




    

    




    return 0;
}