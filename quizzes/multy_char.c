#include <stdio.h>
#include <alloca.h>
#include <string.h>
#include <stdlib.h>

char *Memory(char* old, size_t size, size_t factor, size_t shift)
{   
    char* new = (char*)alloca(size + factor);
    printf("%ld - %ld\n", size, factor);
    memmove(new + shift, old, size);
    return new;
}

char *Multy(char *num1, char *num2, size_t l1)
{
	char sum;
    char *output = NULL;
	int memo = 0;
	int len1 = l1;
	int len2 = 1;
    int len3 = 0;
    size_t fac = 1;
	output = Memory(output, len3, fac, 1);
	while((len1) != 0)
	{	
		sum = (num1[len1 - 1] - 48 ) * (num2[len2 - 1] - 48) + memo;
		*(output) = (sum % 10 + 48);
		--len1;
        ++len3;
		if(sum > 9)
		{
			memo = sum / 10;
		}
		else
		{
			memo = 0;
		}
        output = Memory(output, len3, fac, 1);
	}
    *output = memo + 48;
	return output;	
}

char *Add(char *num1, char *num2, size_t l1, size_t l2)
{
	char sum;
    char *output = NULL;
	int memo = 0;
	int len1 = l1;
	int len2 = l2;
    int len3 = 0;
    size_t fac = 1;
	output = Memory(output, len3, fac, 1);
	while((len1) != 0)
	{	
		sum = (num1[len1 - 1] - 48 ) + (num2[len2 - 1] - 48) + memo;
		*(output) = (sum % 10 + 48);
		--len1;
        --len2;
        ++len3;
		if(sum > 9)
		{
			memo = sum / 10;
		}
		else
		{
			memo = 0;
		}
        output = Memory(output, len3, fac, 1);
	}
    *output = memo + 48;
	return output;	
}

char *BigMulty(char *num1, char *num2, size_t l1, size_t l2)
{
    size_t i = 0;

    if(l2 > 1)
    {
        char **arr = alloca(l2);

        for(i = 0; num2[i] != '\0'; ++i)
        {
            *(arr+i) = Multy(num1, &num2[i], l1);
        }

        return Add(*(arr), *(arr+1), l1, l2);
    }
    else
    {
        return Multy(num1, num2 , l1);
    }
}

char* multiply(char* num1, char* num2)
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len = len1+len2;

    int *arr = (int*)malloc(sizeof(int) * len); 

    memset(arr, 0, sizeof(int)*len); 
    
    for(int i = len1 - 1; i > -1; i--)
    {
        for(int j = len2 - 1; j > -1; j--)
        {
            arr[i+j+1] += (num1[i] - 48) * (num2[j] - 48);
        }
    }
    for(int i = len-1; i > 0; i--) 
    {
        arr[i-1] += arr[i]/10;
        arr[i] %= 10;
    }

    char *s = (char*)malloc(sizeof(char) * (len+1)); 
    int index = 0;
    int i = 0;
    if(arr[i] == 0) 
    {
        i++; 
    }
    while(i < len)
    {
        s[index++] = arr[i++] + 48;
    }
    s[index] = '\0';

    return s;
}

int main()
{	
	printf("%s\n", multiply("685", "32"));
	return 0;
}