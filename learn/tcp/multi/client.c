#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

void *serverCommunication(void *sockID)
{
    int clientSocket = *((int *)sockID);

    while (1)
    {
        char data[1024];
        bzero(data, 1024);
        int read = recv(clientSocket, data, 1024, 0);

        if (read <= 0)
        {
            printf("Disconnected from server\n");
            close(clientSocket);
            exit(0);
        }

        data[read] = '\0';
        printf("%s\n", data);
    }
}

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(34343);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
        exit(0);
    }
    printf("Connection established ............\n");

    pthread_t thread;
    pthread_create(&thread, NULL, serverCommunication, (void *)&clientSocket);

    while (1)
    {
        char input[1024];
        scanf("%s", input);

        if (strcmp(input, "SEND") == 0)
        {
            send(clientSocket, input, strlen(input), 0);
            scanf("%s", input);
            send(clientSocket, input, strlen(input), 0);
            scanf(" %[^\n]", input); // Correctly read until end of line
            send(clientSocket, input, strlen(input), 0);
        }
    }

    close(clientSocket);
    return 0;
}
