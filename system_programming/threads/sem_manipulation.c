#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <errno.h> 
#include <string.h>

#define LINE (50)

void Cancel(int counter, sem_t *sem);
int IsFlag(char *str);

int main(int args, char *argv[])
{
    sem_t *sem = NULL;
    size_t i = 0;
    int sem_val = 0;
    char command[LINE] = {0};
    int number = 0;
    int flag = 0;
    int counter = 0;

    (void)args;
    
    if(argv[1] == NULL)
    {
        fprintf(stderr, "name failed. errno: %d\n", errno);
        return 1;
    }

    sem = sem_open(argv[1], O_CREAT, 0644, 1);

    if(sem == SEM_FAILED) 
    {
        fprintf(stderr, "sem_open() failed. errno: %d\n", errno);
        return 1;
    }
    
    
    while (1)
    {
        fputs("$ ", stdout);
        fgets(command, LINE, stdin);
    
        number = atoi(command + 1);
        number = (number) ? number : 1;
        flag = IsFlag(command + 1) ? 1 : 0;

        if('d' == *command)
        {
            counter = flag ? counter - number: 0;
            for (i = 0; (int)i < number; ++i)
            {
                sem_wait(sem);
            }
            
        }

        if('i' == *command)
        {
            counter = flag ? counter + number: 0;
            for (i = 0; (int)i < number; ++i)
            {
                sem_post(sem);
            }
    
           
        }

        if('v' == *command)
        {
            sem_getvalue(sem, &sem_val);
            printf("THE VALUE IS: %d\n", sem_val);
        }

        if('x' == *command)
        {
            Cancel(counter, sem);
            break;
        }

    }
   
    sem_close(sem);
    return 0;
}

void Cancel(int counter, sem_t *sem)
{
    while (counter > 0)
    {
        sem_wait(sem);
        --counter;
    }
    while (counter < 0)
    {
        sem_post(sem);
        ++counter;
    }
}

int IsFlag(char *str)
{   
    while(*str != 'u' && *str != '\0')
    {
        str++;
    }
    return (strncmp("undo", str, 4) == 0);
}