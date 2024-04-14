#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE];
    bzero(data, SIZE);

    while (fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
    }
}

int main(int argc, char *argv)
{
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE] = {0};

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

    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0)
    {
        perror("[-]Error in Binding");
        exit(1);
    }
    printf("[+]Binding Successfull.\n");

    e = listen(sockfd, 10);
    if (e == 0)
    {
        printf("[+]Listening...\n");
    }
    else
    {
        perror("[-]Error in Binding");
        exit(1);
    }
    addr_size = sizeof(new_addr);
    sockfd = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);

    int n = recv(sockfd, buffer, SIZE, 0);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    FILE *fp = fopen(buffer, "r");
    if (fp == NULL)
    {
        printf("failed to open file\n");
        return 0;
    }
    send_file(fp, sockfd);
    printf("[+]Data written in the text file \n");
}