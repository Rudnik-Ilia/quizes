#include <stdio.h>

# define RETURN return 0

int Mystrcmp(char *s, char *t)
{ 
	for (; *s == *t; s++, t++) {
		
    		if (*s == '\0')
    		{
    	 		return (*s - *t);
    		}
  	} 
  	printf("%c\n - %c\n", *s, *t);
  	return(*s - *t);
}

int StrCmp (const char *p1, const char *p2)
{
	const unsigned char *s1 = (const unsigned char *) p1;
  	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;
  	do
    	{
      		c1 = (unsigned char) *s1++;
      		c2 = (unsigned char) *s2++;
      		printf("%c",c1);
      	if (c1 == '\0')
        	return c1 - c2;
    	}
  	while (c1 == c2);
  	return c1 - c2;
}


int main()
{
	//printf("%d",StrCmp("ilia","ilia"));
	printf("%d",Mystrcmp("ilia","ilia"));

	char a = "a";
	char b = "d";
	
	//printf("%d", a);

}

