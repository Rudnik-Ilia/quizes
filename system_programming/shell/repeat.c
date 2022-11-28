#include <stdio.h>
#include <time.h>



int main()
{
	time_t begin = time(NULL) + 5;
	
	while(begin > time(NULL))
	{
		puts("INFINITY");
		puts("--------");
	}
	


return 0;
}
