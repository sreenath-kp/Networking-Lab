#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include<ctype.h>

int main() {
    pid_t childproc ;
    childproc = fork();
    if (childproc == 0)
    {
        printf("Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());


        int fd = open("file.txt", O_RDONLY);

        // Read and print the content
        char buffer[100];
        int n = read(fd, buffer, 99);
        buffer[n] = '\0';
        printf("File Content: %s\n", buffer);

        // Close the file
        close(fd);

    }
}

