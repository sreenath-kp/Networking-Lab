#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int port = 12345;
    char *ip = "127.0.0.1";

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddr, clientaddr;
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = port;
    serveraddr.sin_addr.s_addr = inet_addr(ip);
    socklen_t addrlen = sizeof(serveraddr);
    memset(&clientaddr, '\0', sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = port;
    clientaddr.sin_addr.s_addr = inet_addr(ip);

    if (bind(server_fd, (struct sockaddr *)&serveraddr, addrlen) < 0)
    {
        printf("Bind error\n");
        exit(1);
    }
    printf("Bind successful\n");

    listen(server_fd, 5);
    printf("Server listening on %d\n", port);

    int client_fd = accept(server_fd, (struct sockaddr *)&clientaddr, &addrlen);
    printf("Client connected\n");

    char buffer[1024];
    int fd;
    while (1)
    {
        bzero(buffer, 1024);
        recv(client_fd, buffer, 1024, 0);
        fd = open(buffer, O_RDONLY);
        bzero(buffer, 1024);

        if (fd < 0)
        {
            strcpy(buffer, "File not found");
            send(client_fd, buffer, strlen(buffer), 0);
        }
        else
        {
            int n_read = 0;
            while ((n_read = read(fd,buffer,1024))>0)
            {
                send(client_fd, buffer, strlen(buffer), 0);
            }
            
        }
    }
}