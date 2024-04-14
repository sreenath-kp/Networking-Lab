#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

int main(int argc, char* argv[])
{
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    // printf("%d", atoi(argv[1]));
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    char *filename;
    char message[1024];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created. \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e == -1)
    {
        perror("[-]Error in Connecting");
        exit(1);
    }
    printf("[+]Connected to server.\n");
    printf("Enter filename: \n");
    scanf("%s", filename);
    send(sockfd, filename, sizeof(filename), 0);

    printf("\nReceiving file from server.\n");
    int n;
    while ((n = recv(sockfd, message, sizeof(message), 0)) != 0)
    {
        printf("%s", message);
    }
}