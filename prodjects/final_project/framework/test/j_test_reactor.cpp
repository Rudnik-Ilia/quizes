#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fstream>

#include "Reactor.hpp"
#include "Listener.hpp"

using namespace ilrd;
using namespace std;

Reactor r(std::unique_ptr<IFDListener>(new Listener));

int counter = 0;

#define MAX_BUFF 100

void WriteFunc(int fd)
{
    char text[100] = "Hey there :)";
    write(fd, text, strlen(text));
    ++counter;
    if(counter >= 5)
    {
        r.Unregister({fd, Reactor::ioMode::WRITE});
    }
}

void ReadFunc(int fd)
{
    char buff[MAX_BUFF] = {0};
    read(fd, buff, MAX_BUFF);
    cout << "Reading: " << buff << endl;
    if(counter >= 5)
    {
        r.Unregister({fd, Reactor::ioMode::READ});
    }
}

int main()
{
    int pipefd[2];
    pipe(pipefd);

    r.Register({pipefd[0], Reactor::ioMode::READ}, [&pipefd](){ReadFunc(pipefd[0]);});
    r.Register({pipefd[1], Reactor::ioMode::WRITE}, [&pipefd](){WriteFunc(pipefd[1]);});

    r.Register({STDIN_FILENO, Reactor::ioMode::READ},
               []()
               {
                   char buff[5] = {0};
                   read(STDIN_FILENO, &buff, 4);
                   if (!strcmp(buff, "stop"))
                   {
                       r.Stop();
                   }
               });
    r.Run();
    return 0;
}
