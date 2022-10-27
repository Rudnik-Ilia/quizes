
#include <stdio.h>

typedef enum state
{
    START,
    MIDDLE,
    FINAL,
    ERROR_START,
    ERROR_FINAL
} st_t;

static int STEPS[][2] =
    {
        {MIDDLE, ERROR_START},
        {FINAL, MIDDLE},
        {FINAL, ERROR_FINAL},
        {ERROR_START, ERROR_START},
        {FINAL, ERROR_FINAL}
        };


int GetString(char *arr)
{
	st_t status = START;
	
	int cur = 0;
	
	while(*arr)
	{
		cur = (char)*arr++ - 48;
		status = STEPS[status][cur];
	}
	return status;
}

void ShowResult(int st)
{

	switch (st){
	case 0  :
		printf("START\n");
		break;
	case 1:
		printf("MIDDLE\n");
		break;
	case 2:
		printf("FINAL\n");
		break;
	case 3:
		printf("ERROR START\n");
		break;
	case 4:
		printf("ERROR_FINAL\n");

	}

}


int main()
{
	ShowResult(GetString("11000"));
	
return 0;
}





