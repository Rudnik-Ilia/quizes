#include <stdio.h>



int Recur(int x)
{	
	
	static int res = 0; 
	
	if(0 == x)
	{
		return 0;
	}
	else
	{	
		res = res*10 + x % 10;
		Recur(x/10);
	}

return res;
}




int main()
{
	int x = 12345;
	int y;
	
	printf("%d\n", Recur(1234));

return 0;
}
