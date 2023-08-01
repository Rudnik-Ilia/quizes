#include <iostream>


int Foo(std::string str)
{
    size_t words = 0;

    for(size_t i = 0; i < str.size(); ++i)
    {
        if((str[i] != ' ' && str[i+1] == ' ') || (str[i] != ' ' && str[i+1] == '\0'))
        {
            ++words;
        }
    }
    return words;
}



int bar(int x, int c)
{   
    if(x == 0)
    {    
        return c;
    }
    int summ = bar(x/10, c+1);
    return summ;
}


int Find(std::string str)
{
    int words = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if((str[i] == 'd' && str[i+1] == 'u') || (str[i] == 'd' && str[i+1] == '\0'))
        {
            ++words;
        }
    }
    return words;
}
int Find2(std::string str)
{
    int words = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if((str[i] == 'd' && str[i+1] == 'd'))
        {
            str[i] = 'u';
        }
    }
    for (int i = 0; i < str.size(); i++)
    {
        if(str[i] == 'd')
        {
            ++words;
        }
    }

    return words;
}

int Find3(std::string str)
{
    int level = 0;
    int pits = 0;
    int flag = 0;
    for (int i = 0; i < str.size(); i++)
    {
        level += (str[i] == 'd') ? -1 : 1;

        std::cout << "level " << level<<  std::endl;
        if(level < 0 && flag == 0)
        {
            std::cout << "pit " <<  pits <<std::endl;
            ++pits;
            flag = 1;
        }
        flag =  (level == 0) ? 0 : flag;
    }
    return pits;
}
int main()
{
  
    // std::cout << bar(12345, 0) << std::endl;

    std::cout << Find3("ddddddddduuuuuuddddddddduuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu")<< std::endl;

    return 0;
}