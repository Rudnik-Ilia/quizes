#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/
#include <stdlib.h> /*abort*/
#include <sys/wait.h> /*wait*/
#include <pthread.h>

#include <watchdog.h>

int main()
{
    return 0;
}