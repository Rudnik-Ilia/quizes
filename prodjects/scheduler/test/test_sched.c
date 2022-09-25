
#include <stdio.h>
#include <unistd.h> /* getpid */
#include <time.h>
#include <stdlib.h>
#include "scheduler.h"
#include "ilrd_uid.h"





int main()
{
	
	time_t a = time(0);
	
	printf("%ld\n", a);
	
	printf("%d\n", rand());
	printf("%d\n", rand());

return 0;
}
