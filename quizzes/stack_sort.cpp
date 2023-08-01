#include <iostream>
#include <stack>
#include <gtest/gtest.h>

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

void IterSort(Stack_t &stack)
{
    Stack_t tmp_stack;

    while (!stack.empty())
    {
        int curr = stack.top();
        stack.pop();

        if(!tmp_stack.empty() && curr > tmp_stack.top())
        {
            stack.push(tmp_stack.top());
            tmp_stack.pop();
        }

        tmp_stack.push(curr);
    }

    while(!tmp_stack.empty())
    {
        stack.push(tmp_stack.top());
        tmp_stack.pop();
    }  
   
}

TEST(IterSort, Test1) 
{
    Stack_t stack;
    stack.push(3);
    stack.push(5);
    stack.push(8);
    stack.push(1);
    stack.push(23);

    IterSort(stack);

    while(stack.size() > 1)
    {
        int tmp = stack.top();
        stack.pop();
        ASSERT_TRUE(tmp > stack.top());
    }
}

TEST(SortStack, Test1) 
{
    Stack_t stack;
    stack.push(3);
    stack.push(5);
    stack.push(8);
    stack.push(1);
    stack.push(23);

    SortStack(stack);

    while(stack.empty() > 1)
    {
        int tmp = stack.top();
        stack.pop();
        ASSERT_TRUE(tmp > stack.top());
    }
}

int main()
{
    // Stack_t stack;
    // stack.push(3);
    // stack.push(5);
    // stack.push(8);
    // stack.push(1);
    // stack.push(23);

    // SortStack(stack);
    // IterSort(stack);

    // while(!stack.empty())
    // {
    //     std::cout << stack.top() << std::endl;
    //     stack.pop();
    // }
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

    return 0;
}