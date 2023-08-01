#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *RemDup(char *str)
{
    unsigned char arr[128] = {0};
    size_t i = 0;
    size_t j = 0;

    for( i = 0; i < strlen(str); ++i)
    {
        arr[str[i]] += 1;
    }
    for( i = 0, j = 0; i < 128; ++i)
    {   
        if(arr[i] > 0)
        {
            str[j] = i;
            ++j;
        }
    }
    str[j] = '\0';


    return str;
}


int main()
{
    char str[] = "dtggwvansbcabc";

    RemDup(str);

    for(int i = 0; i < strlen(str); ++i)
    {
        printf("%c ", str[i]);
    }


}