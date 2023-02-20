#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;




int main()

{   long x = 100000000;
    char* str = "qwertyuiop";
    while (--x)
    {
        char *buff = new char[11];
        memcpy(buff, str, strlen(str));
    }
    
}