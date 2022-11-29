
#define _POSIX_C_SOURCE 1
#define POSIX_C_SOURCE 200112L
#include <signal.h>/*sigaction*/
#include <stdio.h>
#include <unistd.h>/*fork*/
#include <sys/wait.h>/*wait*/
#include <sys/types.h>/*pid_t*/
#include <stdlib.h>


void handler_usr_1();
void handler_usr_2();


int main()
{
	pid_t pid_child;
	pid_t pid_paren;
	
	struct sigaction user_1;
	struct sigaction user_2;

	user_1.sa_handler = handler_usr_1;
	user_1.sa_handler = handler_usr_2;
	

	pid_child = fork();

	if(0 == pid_child)
	{
		puts("im child");
		kill(getppid(), SIGUSR1);
		sleep(1);
	}
	else
	{
		puts("im parent");
		sigaction(SIGUSR1, &user_1, NULL);

		wait(NULL);
	}




return 0;
}

void handler_usr_1(int child)
{
	puts("ive got it from child");
	kill(child, SIGUSR2);
}

void handler_usr_2()
{
	puts("ive got it from parent");
}