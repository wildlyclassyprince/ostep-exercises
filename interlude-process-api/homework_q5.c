#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// answers questions 5 and 6
int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int child_pid = fork();
    if (child_pid < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (child_pid == 0) {
        // child
        printf("child (pid:%d)\n", (int) getpid());
    } else {
        // parent
        int status;
        waitpid(child_pid, &status, 0);
        printf("parent (pid:%d)\n", (int) getpid());

        if (WIFEXITED(status)) {
            printf("child exited with status: %d\n", WIFEXITED(status));
        } else if (WIFSIGNALED(status)) {
            printf("child killed by signal: %d\n", WTERMSIG(status));
        }
    }
    return 0;
}