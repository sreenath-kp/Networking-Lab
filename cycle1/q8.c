#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

 	int fd = open("file.txt", O_RDONLY);
    
    char buffer[100];
    int n = read(fd, buffer, 99);
    buffer[n] = '\0';
    printf("File Content: %s\n", buffer);
    printf("Content size : %d\n",n);
    close(fd);

    int fdnew=open("destination.txt", O_CREAT | O_WRONLY, 0777);
    write(fdnew,buffer,n);
    printf("Written to destination.txt\n");

    return 0;
}
