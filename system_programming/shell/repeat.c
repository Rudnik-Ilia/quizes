#include <stdio.h>
#include <time.h>



int main(int argc, char *argv[])
{
	time_t begin = time(NULL) + 5;
	(void)argc;
	
	while(begin > time(NULL))
	{
		printf("%s\n", argv[1]);
	}
	


return 0;
}
