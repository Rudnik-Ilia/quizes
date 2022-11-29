
#define _POSIX_C_SOURCE 1

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

void Handler_User1();
void Handler_User2();

int count = 4;

int main ()
{
	struct sigaction user1;
	struct sigaction user2;

	pid_t child_pid;
	pid_t parent_pid;

	user1.sa_handler = Handler_User1;
	user1.sa_flags = 0;
	sigemptyset(&user1.sa_mask);

	user2.sa_handler = Handler_User2;
	user2.sa_flags = 0;
	sigemptyset(&user2.sa_mask);

	sigaction(SIGUSR1, &user1, NULL);
	sigaction(SIGUSR2, &user2, NULL);

	child_pid = fork();

	while (count)
	{
		if (child_pid == 0)      
		{
		    parent_pid = getppid();
		    kill(parent_pid, SIGUSR2);
			pause();
		    sleep(1);
		}
		
		if (child_pid > 0)       
		{
		    kill(child_pid, SIGUSR1);
			pause();
		    sleep(1);
		}

	}

	return 0;
}

void Handler_User1()
{
	if (count)
	{
		puts("PING\n");
		count--;
	}
}

void Handler_User2()
{
	if (count)
	{
		puts("PONG\n");
		count--;
	}
}
