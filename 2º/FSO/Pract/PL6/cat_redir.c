// redir_output.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc,char *argv[]) {
    int fd;
    char *arch = "ls_salida.txt";
    mode_t fd_mode = S_IRWXU;// file premissions

    fd = open(arch,O_RDONLY,fd_mode);
    if (dup2(fd,STDIN_FILENO) == -1) { 
        printf("Error calling dup2\n");
        exit(-1);
    }
    close(fd);
    execl("/bin/cat", "cat", NULL);

    //fprintf(stdout,"out: Output redirected\n");
    //fprintf(stderr,"error: not redirected\n");
    //fprintf(stderr,"Check file %s\n",arch);
    return(0);
}
