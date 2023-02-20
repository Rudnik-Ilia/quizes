#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;




int main()

{   long x = 100000000;
    while (--x)
    {
        char *buff = strdup("qwertyuiop");
        free(buff);
    }
    
}