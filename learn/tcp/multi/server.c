#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

int clientCount = 0;

typedef struct client
{
    int index;
    int sockID;
    struct sockaddr_in clientAddr;
    int len;
} client;

client Client[1024];
pthread_t thread[1024];

void *clientCommunication(void *ClientDetail)
{
    struct client *clientDetail = (client *)ClientDetail;
    int index = clientDetail->index;
    int clientSocket = clientDetail->sockID;
    printf("Client %d connected.\n", index + 1);

    while (1)
    {
        char data[1024];
        bzero(data, 1024);
        int read = recv(clientSocket, data, 1024, 0);

        if (read <= 0)
        {
            printf("Client %d disconnected.\n", index + 1);
            close(clientSocket);
            break;
        }

        data[read] = '\0';
        char output[1024];

        if (strcmp(data, "SEND") == 0)
        {
            read = recv(clientSocket, data, 1024, 0);
            if (read <= 0)
                break;
            data[read] = '\0';
            int id = atoi(data) - 1;
            read = recv(clientSocket, data, 1024, 0);
            if (read <= 0)
                break;
            data[read] = '\0';

            for (int i = 0; i < clientCount; i++)
            {
                if (i == id)
                    continue;
                else
                    send(Client[i].sockID, data, 1024, 0);
            }
        }
    }
    return NULL;
}

int main()
{
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(34343);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 1024) == -1)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started listening on port 34343...........\n");

    while (1)
    {
        Client[clientCount].len = sizeof(Client[clientCount].clientAddr);
        Client[clientCount].sockID = accept(serverSocket, (struct sockaddr *)&Client[clientCount].clientAddr, &Client[clientCount].len);
        Client[clientCount].index = clientCount;
        pthread_create(&thread[clientCount], NULL, clientCommunication, (void *)&Client[clientCount]);
        clientCount++;
    }

    for (int i = 0; i < clientCount; i++)
        pthread_join(thread[i], NULL);

    close(serverSocket);
    return 0;
}
