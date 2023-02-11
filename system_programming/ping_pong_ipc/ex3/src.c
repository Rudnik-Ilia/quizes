#include <stdio.h>     
#include <sys/types.h>  
#include <sys/stat.h>   
#include <fcntl.h>      
#include <unistd.h>     
#include <stdlib.h>    
#include <errno.h> 

#include "src.h"

int ReadWrite(char* pathname, char *message, int check)
{
    while (1)
    {
        int pipe = 0;
        char buff[5] = {0};
        if (check)
        {
            pipe = open(pathname, O_WRONLY);
            if(pipe < 0)
            {
                fprintf(stderr, "Open pipe failed. errno: %d\n", errno);
                return 1;
            }

            if (0 > write(pipe, message, 5))
            {
               fprintf(stderr, "Write pipe failed. errno: %d\n", errno);
                return 1;
            }
            close(pipe);
        }

        pipe = open(pathname, O_RDONLY);

        if (0 > pipe)
        {
            fprintf(stderr, "Open pipe failed. errno: %d\n", errno);
            return 1;
        }

        if (0 > read(pipe, buff, 5))
        {
            fprintf(stderr, "Read pipe failed. errno: %d\n", errno);
            return 1;
        }
        printf("%s\n", buff);
        close(pipe);
        check = 1;
    }
}