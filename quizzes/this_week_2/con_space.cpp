#include <iostream>
#include <cstring>

void RemoveConsecutiveSpaces(char* str, int len)
{
    int j = 0;

    for (int i = 0; i < len; ++i) 
    {
        if (str[i] == ' ' && str[i + 1] == ' ') 
        {
            continue;
        }
        str[j] = str[i];
        ++j;
    }
    str[j] = '\0';
}

void Remove(char* str)
{
    char* read = str;
    char* write = str;

    char prev = '\0';

    while(*read)
    {
        if(*read != ' ' || prev != ' ')
        {
            *write = *read;
            ++write;  
        }
        prev = *read;
        ++read;
    }
    *write = '\0';
}
void Remove2(char* str)
{
    char* read = str;
    char* write = str;
    char prev = '\0';

    while(*read)
    {
        if(*read == ' ' || prev == ' ')
        {
            continue;
            prev = 
        }
        *write = *read;
        ++write;
    }
    *write = '\0';
}

int main()
{
    char str[] = {"ab  cd"};
    size_t size = strlen(str);
    Remove(str);
    std::cout << str << std::endl;
    return 0;
}