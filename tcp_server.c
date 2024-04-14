#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define port 4346
void main()
{
    // Define variables
    char *ip = "127.0.0.1";
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
    char buffer[1024];
    // server create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-] Socket error\n");
        exit(1);
    }
    printf("[+]TCP server socket created\n");

    // clear server adderess buffer
    bzero(&server_addr, sizeof(server_addr));
    // initialize server address stucture
    server_addr.sin_family = AF_INET;            // address family to IPv4
    server_addr.sin_port = port;                 // port number
    server_addr.sin_addr.s_addr = inet_addr(ip); // ip address

    // bind socket to server address
    int n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        printf("[-] Bind error, port already in use\n");
        exit(1);
    }
    printf("Bound to port-%d\n", port);
    // Put server socket in listen mode
    listen(server_sock, 1);
    size = sizeof(client_addr);
    // Accept connection from client
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &size);
    printf("[+] Clientconnected .\n");

    // recieve from client
    while (1)
    {
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
        bzero(buffer, 1024);
        char msg[1024];
        scanf("%[^\n]", msg);
        strcpy(buffer, msg);
        send(client_sock, buffer, sizeof(buffer), 0);
    }
}
