#include <stdio.h>



void MoveOne(char from, char to)
{
    printf("Move a disk from %c to %c\n", from, to);
}

void MoveAll(char from, char to, char tmp, int N)
{
    if(N == 0)
    {
        return;
    }
    MoveAll(from, tmp, to ,N - 1);
    MoveOne(from, to);
    MoveAll(tmp, to, from, N- 1);
}

int main ()
{
   
   MoveAll('A', 'B', 'T', 3);
    
    return (0);
}


