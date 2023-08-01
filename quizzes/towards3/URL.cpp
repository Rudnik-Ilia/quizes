#include <iostream>

void printURL(std::string url)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < url.size(); ++i)
    {
        if(url[i] == '/' || url[i] == '\0')
        {
            for(j = 0; j < i; ++j)
            {
                std::cout << url[j];
            }
            std::cout << std::endl;
        }
    }
}

void printURLRec(std::string url, int start)
{
    if(url[start] == '\0')
    {
        return;
    }
    if(url[start] == '/')
    {
        for(int i = 0; i < start; ++i)
        {
            std::cout << url[i];
        }
        std::cout << std::endl;
        printURLRec(url, start + 1);
    }
    else
    {
        printURLRec(url, start + 1);
    }
}


int main()
{
    std::string url = {"www.walter.com/doors/chance/math/"};
    printURLRec(url, 0);
    return 0;
}