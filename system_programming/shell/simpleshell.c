#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

	char input[20];
	char *command[] = {"", NULL};
	int id = 0;
	int len = 0;


	while(1)
	{
		printf("Insert: ");
		fgets(input, sizeof(input), stdin);

		if(strncmp(input, "exit", (strlen(input)-1)) == 0)
		{
			break;
		}
		if(strncmp(input, "fork", (strlen(input)-1)) == 0)
		{	
			printf("Insert command: ");
			getline(&command[0], &len, stdin);
			id = fork();
			if(0 == id)
			{
				if(execvp(command[0], command) == -1)
				{	
					printf("%s\n", command[0]);
					puts("Erorr");
				}
			}
			else
			{
				wait(NULL);
			}
		}
		if(strncmp(input, "system", (strlen(input)-1)) == 0)
		{
			while(1)
			{
				printf("Insert command: ");
				fgets(input, sizeof(input), stdin);
				
				if(strncmp(input, "back", (strlen(input)-1)) == 0)
				{
					break;
				}
				system(input);
			}
		}
	
		


	}

	
	return 0;
}
