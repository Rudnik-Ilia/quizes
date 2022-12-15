#include <stdio.h>

#include <wd.h>



int main(int argc, char const *argv[])
{

    puts("Start");

    KeepMeAlive(argc, argv[0], argv[1], argv[3]);

    sleep(10);

    DoNotResuscitate(); 

    puts("Stop");



    return 0;
}