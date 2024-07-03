#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = 12345;

    // Bind the socket to the address and port
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running and waiting for requests...\n");

    while (1)
    {
        // Receive a message from a client
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';
        printf("Received request from client: %s\n", buffer);

        // Get the current system time
        time_t t = time(NULL);
        char *time = ctime(&t);w

        // Send the current system time back to the client
        sendto(sockfd, time, strlen(time), 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Sent time to client: %s", time); // ctime() includes a newline
    }

    close(sockfd);
    return 0;
}
