#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    char *ip = "127.0.0.1";
    int port = 12345;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sockaddr;
    char buffer[1024];

    if (sockfd < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = port; // Note: htons() is used for network byte order
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
        perror("Connection error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    while (1) {
        // Send message to the server
        memset(buffer, 0, sizeof(buffer));
        printf("msg: ");
        scanf("%s", buffer);
        if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
            perror("Send error");
            close(sockfd);
            return 1;
        }

        // Receive message from the server
        memset(buffer, 0, sizeof(buffer));
        if (recv(sockfd, buffer, sizeof(buffer), 0) < 0) {
            perror("Receive error");
            close(sockfd);
            return 1;
        }
        printf("Server: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
}
