#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <signal.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/types.h>  
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t state =  1;

void Handler_Pong();

int main(int argc, char const *argv[])
{
	pid_t ping_pid = 0;

	struct sigaction pong;
	
	(void)argc;
	
	pong.sa_flags = 0;
	pong.sa_handler = Handler_Pong;
	sigemptyset(&pong.sa_mask);
	sigaction(SIGUSR2, &pong, NULL);

	ping_pid = atoi(argv[1]);

	while(1)
	{
		while(0 == state)
		{

		}

		state = 0;
		if(kill(ping_pid, SIGUSR1) != 0)
		{
			return 1;
		}
	}

	return 0;
}

void Handler_Pong()
{	
	sleep(1);
	write(1, "PONG\n", 5);
	state = 1;
}
