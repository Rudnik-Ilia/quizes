#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	char command[50];
	pid_t pid = 0; 
	while(1)
	{
		printf("Choose mode: system or fork: ");
		fgets(command, sizeof(command), stdin);

		if(strncmp(command, "exit", (strlen(command)-1)) == 0)
		{
			break;
		}
		if(strncmp(command, "fork", (strlen(command)-1)) == 0)
		{	
			while (1)
			{	
				fputs("$ ", stdout);
				fgets(command, sizeof(command), stdin);
				
				if(strncmp(command, "back", (strlen(command) - 1)) == 0)
				{
					break;
				}
				pid = fork();

				if (pid == 0)
				{
					size_t len = strlen(command);
					size_t i = 0;
					size_t count = 1;
					char **argv;

					for (i = 0; i < len; ++i)
					{
						count += (command[i] == ' ');
					}
					++count;

					argv = (char **) malloc(count * sizeof(char *));

					i = 0;
					argv[i] = strtok(command, " \n");

					while (argv[i] != NULL)
					{
						++i;
						argv[i] = strtok(NULL, " \n");
					}

					if (execvp(argv[0], argv) == -1)
					{ 
						return 1;
					}

					free(argv);
					return 0;

				}
				else
				{
					wait(NULL);

				}
				
			}			
		}
		if(strncmp(command, "system", (strlen(command) - 1)) == 0)
		{
			while(1)
			{
				fputs("$ ", stdout);
				fgets(command, sizeof(command), stdin);
				
				if(strncmp(command, "back", (strlen(command)-1)) == 0)
				{
					break;
				}
				system(command);
			}
		}

	}
	return 0;
}
