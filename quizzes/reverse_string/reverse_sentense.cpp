#include <iostream>
#include <cstring>

using namespace std;

char* Reverse(char * str)
{
    int len = strlen(str);
    int i = 0;
    int j = 0;
    int t = 0;
    int count = 0;
    int letter = 0;

    char* tmp = (char*)malloc(len + 1);

    for(i = (len - 1); i >= 0; --i)
    {
        if(str[i] == ' ' || 0 == i) 
        {
            count = letter;
            for(j = i + (i != 0); j < (len - count); ++j)
            {
                // cout << str[j] << ' ';

                tmp[t++] = str[j];

                ++letter;
            }
            tmp[t++] = ' ';
            // cout << ' ';
            ++letter;
        }
    }
    return tmp;
}

int CountWords(char *str)
{
    int count = 0;
    int len = strlen(str);
    int flag = 0;

    for(int i = 0; i < len; ++i)
    {
        if(str[i] != ' ' && flag == 0)
        {
            ++count;
            flag = 1;
        }
        else
        {
            if(str[i] == ' ')
            {
                flag = 0;
            }
        }
 
    }
    return count;
}



int main()
{

    char str[] = {"             I am                     a student!             "};

    cout << Reverse(str) << endl;


    return 0;
}