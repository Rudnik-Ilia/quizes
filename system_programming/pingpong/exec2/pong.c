#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <signal.h>  
#include <unistd.h>

void Handler_1();


int main()
{
	struct sigaction user1;

	user1.sa_handler = Handler_1;
	user1.sa_flags = 0;
	sigemptyset(&user1.sa_mask);

	sigaction(SIGUSR1, &user1, NULL);

	while(1)
	{	
		if(kill(getppid(), SIGUSR2) != 0)
		{
			return 1;
		}
		pause();
		sleep(1);
	}

	return 0;
}

void Handler_1()
{	
	sleep(1);
	write(1, "PING\n", 5);
	
}

