#include <iostream>
#include <cstring>

int Check(char * str1, char * str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int count = 0;

    if(len1 != len2)
    {
        return -1;
    }

    for(int i = 0; i < len1; ++i)
    {
        for (int j = 0; j < len2; ++j)
        {
            count += (str1[i] == str2[j]);
        }
        if(!count)
        {
            return -1;
        }
        count = 0;
    }
    return 1;
}

int Check2(char * str1, char * str2)
{   
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int arr1[256] = {0};
    int arr2[256] = {0};

    if(len1 != len2)
    {
        return -1;
    }

    for (size_t i = 0; i < len1; ++i)
    {
        arr1[str1[i]] += 1;
    }

    for (size_t i = 0; i < len2; ++i)
    {
        arr2[str2[i]] += 1;
    }

    for (size_t i = 0 ; i < 256; ++i)
    {
        if(arr1[i] != arr2[i])
        {
            return -1;
        }
    }
    return 1;
}


int main()
{
    char str1[] = "AAC";
    char str2[] = "QAA";

    std::cout << Check2(str1, str2) << std::endl;

    return 0;
}