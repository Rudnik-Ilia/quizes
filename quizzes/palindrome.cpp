#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;


bool Pal(char *str, int f, int  l)
{
    if(f >= l)
    {
        return true;
    }
    return (str[f] == str[l]) ? Pal(str, f + 1, l - 1) : false;
    
}

bool Check(int x)
{
    if(x == 1)
    {
        return true;
    }
    else
    {
        return ((x % 2) == 0) && Check(x / 2);
    } 
}

bool Check2(int x)
{
    return (x & (x -1)) == 0 ? true : false;
}

bool IterCheck(char * str)
{
    assert(str);
    int i = 0;
    int j = strlen(str) - 1; 

    for(i, j; i <= j; ++i, --j)
    {
        if(str[i] != str[j])
        {
            return false;
        }
    }

    return true;
}


int main()
{
    char arr[] = "abbae";
    char arr1[] = "abba";
    char arr2[] = "aba";
    cout <<  Pal(arr, 0, strlen(arr) - 1) << endl;
    cout <<  Pal(arr1, 0, strlen(arr1) - 1) << endl;
    cout <<  Pal(arr2, 0, strlen(arr2) - 1) << endl;

    // int arr1[] = {2,3,4,8,6,9,16,64};

    // for(int i = 0; i < 8; ++i)
    // {
    //     cout <<  Check(arr1[i]) << endl;
    // }

    // cout <<  IterCheck(arr) << endl;

    return 0;
}