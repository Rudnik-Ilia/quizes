#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;



void Reverse(char* str)
{
    int len = strlen(str);
    int i,j;
    char tmp;

    for(i = 0, j = len - 1; i < j; ++i, --j)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        
    }
    cout << str << endl;
}

void ReverseRec(char* str, int start, int end)
{
    if(start >= end)
    {
        cout << str << endl;
        return;
    }
    char tmp;
    tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    ReverseRec(str, start+1, end-1);
}

void ReverseN(char *str)
{
    char tmp;
    int len = strlen(str);

    for(int i = 0; i < strlen(str)/2; ++i)
    {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - i - 1] = tmp;

    }
    cout << str << endl;
}

void FastReverse(char * str)
{
    char *start = str;
    char *end = str + strlen(str) - 1;

    while(start < end)
    {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        ++start;
        --end;
    }
}

int main()
{   
   
    char arr[] = "Rudnik";
 
    
    // Reverse(arr);
    // ReverseRec(arr1, 0, 5);
    // ReverseN(arr);



   


    FastReverse(arr);
    cout << arr << endl;
    


    

    return 0;
}