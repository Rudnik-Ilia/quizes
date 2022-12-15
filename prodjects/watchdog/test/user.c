#include <stdio.h>
#include <unistd.h>

#include <wd.h>
#define COLOR "\033[1;31m" 
#define OFFCOLOR "\033[0m"


int main(int argc, const char* argv[])
{
    
    puts(COLOR"Start"OFFCOLOR);

    KeepMeAlive(argc, argv, 3, 3);

    sleep(60);

    DoNotResuscitate(); 

    puts(COLOR"Stop"OFFCOLOR);



    return 0;
}