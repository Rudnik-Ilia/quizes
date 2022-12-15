#include <stdio.h>
#include <unistd.h>

#include <wd.h>



int main(int argc, const char* argv[])
{
    
    puts("Start");

    KeepMeAlive(argc, argv, 3, 3);

    sleep(60);

    DoNotResuscitate(); 

    puts("Stop");



    return 0;
}