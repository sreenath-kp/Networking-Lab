#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define port 4346

void main()
{
    // Create socket
    int sockfd;
    char buffer[1024];
    struct sockaddr_in sock_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = port;
    sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
    // Connect
    if (connect(sockfd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1)
    {
        printf("Connection failed\n");
        exit(1);
    }
    printf("Connection success\n");
    // send
    while (1)
    {
        bzero(buffer, 1024);
        printf(":");
        char msg[1024];
        scanf("%s", msg);
        strcpy(buffer, msg);
        send(sockfd, buffer, sizeof(buffer), 0);
        // recieve
        bzero(buffer, 1024);
        recv(sockfd, buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
    }
}