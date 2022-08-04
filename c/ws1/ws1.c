#include <stdio.h>

void ChangeString(char *word, int len_of_word)/* takes word and its len. ti convert to hex-format*/

{
    int i = 0;
       
    for(i = 0; i<len_of_word; i++)
    {
        printf("0x%x\n",*(word+i));
    }   
}

float PowNumber(int n)/*exponent to by n*/
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

int SwapNumber(int x)/*reverse a given number*/
{
	
	int result = 0;
	while(x)
	{
    		result = result*10+x%10;
    		x /= 10;
	}
	return result;
}

void Swap(int *x,int *y)/* swaping two variable in memory*/
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}


int main()
{
	int a = 10;
	int b = 20;

	
	char word[] = "\"Hello word!\"";	
        ChangeString(word,17);
    	printf("\n%f\n",PowNumber(5));
    	printf("\n%f\n",PowNumber(-3));
    	printf("%d\n",SwapNumber(12340));
       
    
    	Swap(&a,&b);
    
    
    
    return 0;
}























