#include <iostream>

using namespace std;

int FibRec(long long x)
{
    if(x == 0)
    {
        return 0;
    }
    if((x == 1) | (x == 2))
    {
        return 1;
    }

    return FibRec(x - 1) + FibRec(x - 2);
}

int FibLoop(int x)
{
    int prev = 0;
    int cur = 1;
    int next = prev + cur;

    for(int i = 1; i < x - 1; ++i)
    {
        prev = cur;
        cur = next;
        next = prev + next;
    }
    return next;
}

int main()
{
    cout << FibRec(9) << endl;
    cout << FibLoop(9) << endl;

    return 0;
}


