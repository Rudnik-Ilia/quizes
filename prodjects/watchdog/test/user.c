#include <stdio.h>



int main(int argc, char const *argv[])
{

    puts("Start");

    KeepMeAlive(argc, *argv, argv[3], argv[4]);

    sleep(10);

    DoNotResuscitate();

    return 0;
}