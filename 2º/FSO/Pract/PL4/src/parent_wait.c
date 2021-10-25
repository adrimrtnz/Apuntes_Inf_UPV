#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 5

int main(int argc, char *argv[])
{
    int val_return;
    
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        val_return = fork();
        if (val_return == 0)
        {
            printf("Hijo creado en interacion: %d\n", i);
            exit(i);
        }
    }
    
    while (wait(NULL) != -1) ;
    sleep(10);
    exit(0);
}
