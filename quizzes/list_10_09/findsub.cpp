#include <iostream>
#include <cstring>



int FindSub(char *text, char *str)
{
    size_t lenText = strlen(text); 
    size_t lenStr = strlen(str);
    size_t count = 0;
    size_t idx1 = 0;
    size_t idx2 = 0;

    for(size_t i = 0; i < lenText - lenStr; ++i)
    {
        idx1 = i;
        idx2 = 0;
        while(text[idx1] == str[idx2])
        {
            ++count;
            ++idx1;
            ++idx2;
        }
        if(count == lenStr)
        {
            return 1;
        }
        count = 0;
    } 
    return -1;
}



int main()
{
    char text[] = {"jdkfkfjvnvknvievnoifwoiecmwoei3mcoeivmeoivmcewocmeo"};
    char str[] = {"oei3mc"};

    std::cout << FindSub(text, str) << std::endl;

    return 0;
} 