#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PROC 4

int main(int argc, char *argv[])
{
    int i, final_state;
    pid_t val_return;
    
    printf("\n");
    
    for (i = 0; i < MAX_PROC; i++)
    {
        val_return = fork();
        if (val_return == 0)
        {
            printf("Son %ld created in iteration: %d\n", (long)getpid(),i);
            //exit(i);
        }
        else
        {
            printf("Father %ld, iteration %d\n", (long)getpid(), i);
            printf("I have created a son %ld\n", (long)val_return);
            break;
        }
    }
    
    
    while (wait(&final_state) > 0)
    {
        printf("\n-------FINAL STATE: %d (%d)-------\n", final_state, final_state/256);
        printf("Father %ld iteration %d\n", (long)getpid(), i);
        printf("\tMy son said %d\n", WEXITSTATUS(final_state));
        //printf("\tMy son said %d\n", final_state/256);
    }
    exit(i);
}
