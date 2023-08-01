#include <iostream>
#include <cstring>

using namespace std;

int Rec(char * str, int i, int r)
{
    if(str[i] != str[r] || i == r)
    { 
        return abs(i - r);
    }
    return Rec(str, i + 1, r -1);   
}

int main()
{
    char arr[] = {"geeks"};
    cout << Rec(arr, 0, strlen(arr)-1);
    return 0;
}