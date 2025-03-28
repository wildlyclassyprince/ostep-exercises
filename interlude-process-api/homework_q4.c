#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child
        printf("child (pid:%d)\n", (int) getpid());
        execl("/bin/ls", "ls", "-la", NULL);
    } else {
        // parent
        int rc_wait = wait(NULL);
        printf("parent (pid:%d)\n", (int) getpid());
    }
    return 0;
}