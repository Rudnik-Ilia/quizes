#include <iostream>
#include <cstring>
#include <cctype>


std::string Compress(std::string str)
{
    std::string res;
    int num = 1;
    int len = str.size();
    res.push_back(str[0]);

    for (size_t i = 1; i < len; ++i)
    {
        if(str[i] == res.back())
        {
            ++num;
        }
        else
        {
            if(num > 9)
            {
                for(int j = 0; j < std::to_string(num).size(); ++j)
                {
                    res.push_back(std::to_string(num)[j]);
                }
            }
            else
            {
                res.push_back(num + 48);
            }
            res.push_back(str[i]);
            num = 1;
        } 
    }
    res.push_back(num + 48);

    return res;
}


std::string DeCompress(std::string str)
{
    std::string res;
    int num = 0;
    int len = str.size();
    char tmp = ' ';

    for(size_t i = 0; i < len;)
    {
        if(!isdigit(str[i]))
        {
            tmp = str[i];
            ++i;
        }
        while(isdigit(str[i]))
        {
            num = num * 10 + (str[i] - 48);
            ++i;
        }
        while(num)
        {
            res.push_back(tmp);
            --num;
        }
    }

    return res;
}


int main()
{
    std::string str = {"Looooooooooooooooooorrryy"};
    std::string str3 = {"Loooooooooooooooooorrreeeeeeeeeeeeeeeeyy"};
    char str2[] = {"L1o20r3y2"};

    std::cout << Compress(str3) << std::endl;
    // std::cout << str3.compare(DeCompress(Compress(str))) << std::endl;

    return 0;
}