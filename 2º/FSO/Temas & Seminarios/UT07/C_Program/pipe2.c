#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int i, fd[2];
    pipe(fd);

    for (i = 0; i < 2; i++) {
        if (fork() == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);

            execlp("/bin/cat", "cat", NULL);
            exit(1);
        }
    }

    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);

    execlp("/bin/ls", "ls", "-l", NULL);
    exit(1);
}
