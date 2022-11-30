
#define _POSIX_C_SOURCE 1

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void Handler_User1();
void Handler_User2();

int main ()
{
	struct sigaction user1;
	struct sigaction user2;

	pid_t child_pid = 0;
	pid_t parent_pid = 0;

	user1.sa_handler = Handler_User1;
	user1.sa_flags = 0;
	sigemptyset(&user1.sa_mask);

	user2.sa_handler = Handler_User2;
	user2.sa_flags = 0;
	sigemptyset(&user2.sa_mask);

	sigaction(SIGUSR1, &user1, NULL);
	sigaction(SIGUSR2, &user2, NULL);

	child_pid = fork();

	while (1)
	{
		if (child_pid == 0)      
		{	
			parent_pid = getppid();
			if(kill(parent_pid, SIGUSR2) != 0)
			{
				return 1;
			}
			pause();
			sleep(2);
		}
		
		if (child_pid > 0)       
		{
			
		    if(kill(child_pid, SIGUSR1) != 0)
			{
				return 1;
			}
			pause();
		    	sleep(1);
		}

	}
	return 0;
}

void Handler_User1()
{	
	sleep(1);
	write(1, "PING\n", 5);
	
}

void Handler_User2()
{	
	sleep(1);
	write(1, "PONG\n", 5);
}
