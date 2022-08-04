#include <stdio.h>

void ChangeString(char *word, int len_of_word)
{
    int i = 0;
       
    for(i = 0; i<len_of_word; i++)
    {
        printf("0x%x",*(word+i));
    }   
}

float PowNumber(int n)
{
	float result = 1;
	float number = 10;
	if (n < 0)
	 {
	     n*=-1;
	     number = 0.1;
	 }
	 
	while(n){
	    result *= number;
	    n--;	
	}
	return result;
}

int SwapNumber(int x)
{
	
	int result = 0;
	while(x)
	{
    		result = result*10+x%10;
    		x /= 10;
	}
	return result;
}

void Swap(int *x,int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

long l = 8;
long *foo(){ return &l; }

int main()
{

	*(foo()) = 5;
	printf("%ld\n", l);
    char word[] = "\"Hello word!\"";	
    // ChangeString(word,17);
    //printf("\n%f",PowNumber(5));
    //printf("\n%f",PowNumber(-3));
    //printf("%d",SwapNumber(12340));
    int a = 10;
    int b = 20;
    
    //Swap(&a,&b);
    
    //printf("%d - %d", a,b);
    
    int x = 20;
    int y = 35;
    
    x = x++ + y++;
    
    //printf("%d - %d\n", x,y);
    y = ++x + ++y;
    
    //printf("%d - %d", x,y);
    
    int i = 2;
    //int d;int c;
    
    //d = i++;
    //printf("%d\n", d);
    //i = 0;
    //c = ++i; 
    //printf("%d", c);
    
    //int arr[] = {0};
    //arr[i] = i++;
    //printf("%d", arr[i]);
    
    return 0;
}























