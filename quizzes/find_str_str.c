#include <stdio.h>
#include <string.h>

int Find(char * scr, char* str)
{
    size_t len = strlen(scr) - strlen(str);
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t count = 0;
    
    for (i = 0; i < len; ++i)
    {
        for (j = i, k = 0; scr[j] == str[k]; ++j, ++k)
        {
            ++count;
        }
        if(count == strlen(str))
        {
            return i;
        }
        count = 0;
    }
    return -1;
}

int BMH(char *str, char* needle)
{
    int size = strlen(needle);
    int size_2 = strlen(str);
    int arr[128] = {0};
    int count = 1;
    int j = 0;
    int k = 0;
    for(int i = size - 2; i >= 0; --i)
    {
        if(arr[needle[i]] == 0)
        {
            arr[needle[i]] = count;
        }
        ++count;
    }
    if(arr[needle[size - 1]] == 0)
    {
        arr[needle[size - 1]] = size;
    }

    for(int i = size - 1; str[i] != '\0';)
    {
        j = i;
        k = (size -1);
        while(str[j] == needle[k] && k >= 0)
        {
            --j;
            --k;
        }
        if(k == -1)
        {   
            return 0;
        }
        if(k == (size - 1))
        {
            if(arr[str[i]] == 0)
            {
                i += size;
            }
            else
            {
                i += arr[str[i]];
            }
        }
        else
        {
            i += arr[needle[k]];
        }
        if(i > size_2 - 1)
        {
            return 1;
        }
        
    }
    return 1;
}

int main()
{
    char *one = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, \
                    sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \
                    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \
                    Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. \
                    Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, \
                    sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \
                    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \
                    Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. \
                    Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. \
                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, \
                    sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \
                    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \
                    Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. \
                    Excepteur sint occaecat cupidatat non proigggdent, sunt in culpa qui officia deseruntf mollit anim id 55est labzorum.";

    char *two = "dolor";

    printf("%d\n", Find(one, two));
    /*
    printf("%d\n", BMH(one, two));
    
    */
    
    return 0;
}