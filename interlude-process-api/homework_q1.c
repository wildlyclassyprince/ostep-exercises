#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process); changes value of x
        x = 25;
        printf("child (pid:%d)\tx = %d\n", (int) getpid(), x);
    } else {
        // parent (main process); also changes value of x
        x = 73;
        printf("parent (pid:%d)\tx = %d\n", (int) getpid(), x);
    }
    return 0;
}
