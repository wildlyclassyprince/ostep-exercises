#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);

    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        close(fd[0]);
        printf("hello\n");
        write(fd[1], "done", 4);                  // signal parent
        close(fd[1]);
    } else {
        // parent (main process)
        close(fd[1]);
        char buffer[10];
        read(fd[0], buffer, sizeof(buffer));     // wait for child signal
        printf("goodbye\n");
        close(fd[0]);
    }
    return 0;
}
