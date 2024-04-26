#include <iostream>
#include <malloc.h>
#include <cassert>

typedef struct Node node_t;

struct Node
{
    int data;
    node_t *next;
};





struct One
{
    One() = default;
};

struct Two
{
    Two(){};
};




node_t *CreateNode(int data)
{
    node_t *newone = (node_t *)malloc(sizeof(Node));
    newone->data = data;
    newone->next = nullptr;
    return newone;
}

void Show(node_t *head)
{
    node_t *iter = head;
    while (iter)
    {
        std::cout << iter->data << ' ';
        iter = iter->next;
    }
    std::cout << '\n';
}

class Result
{
public:
    static bool HasLoop(node_t *head);
    static int LoopSize(node_t *head);
    static node_t *LastBeforeLoop(node_t *head);
};

bool Result::HasLoop(node_t *head)
{
    assert(head);

    node_t *fast = head;
    node_t *slow = head;

    while (fast && slow && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (fast == slow)
        {
            return true;
        }
    }
    return false;
}

int Result::LoopSize(node_t *head)
{
    assert(head);

    node_t *fast = head;
    node_t *slow = head;
    int count = 0;

    while (fast && slow && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow)
        {
            break;
        }
    }
    do
    {
        fast = fast->next;
        ++count;
    } while (fast != slow);

    return count;
}

node_t* Result::LastBeforeLoop(node_t* head)
{
    assert(head);

    node_t *fast = head;
    node_t *slow = head;
    node_t *result = nullptr;

    while (fast && slow && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow)
        {
            slow = head;
            while(slow != fast)
            {
                result = slow;
                slow = slow->next;
                fast = fast->next;
            }

            return result;
        }
    }

    return nullptr;

}

int main()
{
    // node_t *head = CreateNode(10);
    // head->next = CreateNode(20);
    // head->next->next = CreateNode(30);
    // head->next->next->next = CreateNode(40);
    // head->next->next->next->next = CreateNode(50);
    // head->next->next->next->next->next = CreateNode(60);

    // // head->next->next->next->next->next->next = head->next->next;

    // // Show(head);

    // std::cout << Result::HasLoop(head) << std::endl;
    // // std::cout << Result::LoopSize(head) << std::endl;
    // std::cout << Result::LastBeforeLoop(head) << std::endl;

    bool one= std::is_pod<One>::value;
    bool two = std::is_pod<Two>::value;

    std::cout << one << std::endl;
    std::cout << two << std::endl;

    return 0;
}