// content if given file is copied to a new file ; on sucess prints no of bytes copied
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char sourcefile[20];
    printf("Enter source filename: ");
    scanf("%s", sourcefile);
    printf("Reading from %s\n", sourcefile);
    int n;
    int bytes_read = 0;
    char buf[1024];

    int fd1 = open(sourcefile, O_RDONLY);
    int fd2 = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while ((n = read(fd1, buf, 1024)) > 0)
    {
        write(fd2, buf, n);
        bytes_read += n;
    }

    printf("%d bytes copied\n", bytes_read);
    close(fd1);
    close(fd2);
}
