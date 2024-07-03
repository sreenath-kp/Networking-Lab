#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    char *ip = "127.0.0.1";
    int port = 123456;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr,client_addr;
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    memset(&client_addr, '\0', sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = port;
    client_addr.sin_addr.s_addr = inet_addr(ip);
    socklen_t addrlen = sizeof(client_addr);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Bind error\n");
        exit(1);
    }
    printf("Bind successful\n");


    char buffer[1024];
    while (1)
    {
        bzero(buffer,1024);
        recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&client_addr,&addrlen);
        printf("Client : %s\n",buffer);

        bzero(buffer,1024);
        printf("msg: ");
        scanf("%s",buffer);
        sendto(sockfd,buffer,1024,0,(struct sockaddr*)&client_addr,addrlen);
    }
    printf("Closing connection");
    close(sockfd);
    
}