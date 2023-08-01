#include <iostream>

using namespace std;


int Jump(int levels)
{
    int jumps = 0;
    
    if(levels == 1)
    {
        return 1;
    }
    if(levels >= 1)
    {
        jumps += Jump(levels - 2);
    }
    if(levels >= 1)
    {
        jumps += Jump(levels - 1);
    }
    return jumps;
}



int main()
{

    cout << Jump(5) << endl;




    return 0;
}



