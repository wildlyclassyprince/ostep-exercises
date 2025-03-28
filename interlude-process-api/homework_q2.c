#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    // open a file and redirect standard output to a file
    close(STDOUT_FILENO);
    int fd = open("./test.txt", O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
    int rc = fork();
    int n = 5;
    char buffer[50];
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child: write to file
        for (int i = 0; i < n; i++) {
            int values = snprintf(buffer, sizeof(buffer), "child-%d\n", i+1);   // snprintf ensures no buffer overflow, safer than sprintf
            write(fd, buffer, values);
            usleep(1000);
        }
    } else {
        // parent: writes to file
        for (int i = 0; i < n; i++) {
            int values = snprintf(buffer, sizeof(buffer), "parent-%d\n", i+1);  // snprintf ensures no buffer overflow, safer than sprintf
            write(fd, buffer, values);
            usleep(1000);
        }
    }
    return 0;
}
