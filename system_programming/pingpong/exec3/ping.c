#define _POSIX_C_SOURCE 199309L

#include <signal.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/types.h>  
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void Handler_Ping(int sig, siginfo_t *sa , void *param);

int main()
{
	struct sigaction ping;

	ping.sa_sigaction = Handler_Ping;
	ping.sa_flags = SA_SIGINFO;
	sigemptyset(&ping.sa_mask);

	sigaction(SIGUSR1, &ping, NULL);

	printf("USE THIS PID :%d\n", getpid());

	while(1)
	{
	}
}

void Handler_Ping(int sig, siginfo_t *sa , void *param)
{   	
	(void)sig;
	(void)param;
	sleep(1);
	write(1, "PING\n", 5);
	if(kill(sa->si_pid, SIGUSR2) != 0)
	{
		return;
	}
}
