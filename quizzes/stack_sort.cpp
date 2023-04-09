#include <iostream>
#include <stack>

typedef std::stack<int> Stack_t;

void PutStack(Stack_t &stack, int x)
{
    if(stack.empty())
    {
        stack.push(x);
        return;
    }
    else if(x <= stack.top())
    {
        stack.push(x);
        return;
    }
    else
    {
        int tmp = stack.top();
        stack.pop();
        PutStack(stack, x);
        stack.push(tmp);
    }
}

void SortStack(Stack_t &stack)
{
    if(stack.empty())
    {
        return;
    }

    int tmp = stack.top();
    stack.pop();
    SortStack(stack);
    PutStack(stack, tmp);
}


int main()
{
    Stack_t stack;
    stack.push(3);
    stack.push(5);
    stack.push(8);
    stack.push(1);
    stack.push(23);

    SortStack(stack);

    while(!stack.empty())
    {
        std::cout << stack.top() << std::endl;
        stack.pop();
    }

    return 0;
}