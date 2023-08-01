#include <iostream>
#include <cstring>



char* Summ(char *one, char*two)
{
    int len1 = strlen(one) - 1;
    int len2 = strlen(two) - 1;
    int sum = 0;
    int rest = 0;
    char num = 0;
    char* arr = new char[len1 + 2];
    int i = 0;
    int j = 0; 
    int tmp  = 0;

    for(i = len1, j = len2; j >= 0; --i, --j)
    {
        sum = (one[i] - 48) + (two[j] - 48) + rest;
        num = (sum % 10) + 48;
        rest = (sum - (num - 48)) / 10;
        arr[i] = num;
    }
    while(i >= 0)
    {
        tmp = (one[i] - 48) + rest;
        num = (tmp % 10) + 48;
        arr[i] = num;
        rest = tmp / 10;
        --i;
    }
    
    return arr;
}


int main()
{
    char one[] = {"179835"};
    char two[] = {"6767"};

    std::cout << Summ(one, two) << std::endl;

    return 0;
}