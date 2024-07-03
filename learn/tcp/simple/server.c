#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int PORT = 123456;
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }
    printf("TCP server socket created.\n");

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT); // Note: htons() is used for network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the server address
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind error");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Bind to port number: %d\n", PORT);

    // Listen for incoming connections
    if (listen(server_sock, 10) < 0) {
        perror("Listen error");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Listening...\n");

    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("Accept error");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");
    printf("Client IP: %s\n", inet_ntoa(client_addr.sin_addr));

    while (1) {
        // Clear the buffer and receive data from the client
        memset(buffer, 0, sizeof(buffer));
        if (recv(client_sock, buffer, sizeof(buffer), 0) < 0) {
            perror("Receive error");
            close(client_sock);
            close(server_sock);
            return 1;
        }
        printf("Client: %s\n", buffer);

        // Send a response to the client
        memset(buffer, 0, sizeof(buffer));
        printf("msg: ");
        scanf("%s", buffer);
        if (send(client_sock, buffer, strlen(buffer), 0) < 0) {
            perror("Send error");
            close(client_sock);
            close(server_sock);
            return 1;
        }
    }

    // Close the server socket
    printf("Closing server\n");
    close(server_sock);

    return 0;
}
