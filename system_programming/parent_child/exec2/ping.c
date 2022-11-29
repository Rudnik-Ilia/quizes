#define _POSIX_C_SOURCE 1

#include <signal.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/types.h>  
#include <unistd.h>
#include <sys/wait.h>

void Handler_2();

int main(int argc, char *const argv[])
{
	pid_t child_pid = 0;
	struct sigaction user1;
	
	(void)argc;
	
	user1.sa_handler = Handler_2;
	user1.sa_flags = 0;
	sigemptyset(&user1.sa_mask);

	sigaction(SIGUSR2, &user1, NULL);

	child_pid = fork();

	if(0 == child_pid)
	{
		execv(argv[1], argv);
	}
	if(0 < child_pid)
	{

		while(1)
		{
			pause();
			if(kill(child_pid, SIGUSR1) != 0)
			{
				return 1;
			}
			sleep(1);
		}
		
	}
	return 0;
}

void Handler_2()
{
	puts("PONG\n");
	
}
