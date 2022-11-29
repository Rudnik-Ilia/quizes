
#define _POSIX_C_SOURCE 1
#define _USE_POSIX199309
#define _XOPEN_SOURCE

#include <signal.h>/*sigaction*/
#include <stdio.h>
#include <unistd.h>/*fork*/
#include <sys/wait.h>/*wait*/
#include <sys/types.h>/*pid_t*/
#include <stdlib.h>

int count = 10;

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

	sigaction(SIGUSR1, &user_1, NULL);
	sigaction(SIGUSR2, &user_2, NULL);

	while(count)
	{
		if(0 == pid_child)
		{
			puts("im child");
			kill(getppid(), SIGUSR1);
			sleep(1);
			
		}

		if(0 < pid_child)
		{
			puts("im parent");
			kill(pid_child, SIGUSR2);
			sleep(1);
			/*
			
			*/
			
		}
	}

return 0;
}

void handler_usr_1()
{
	puts("ive got it from child");
	count--;;
}

void handler_usr_2()
{
	puts("ive got it from parent");
	count--;
}