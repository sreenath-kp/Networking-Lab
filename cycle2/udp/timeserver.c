#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	char *ip = "127.0.0.1";
	int port = 5006;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024];
	socklen_t addr_size;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("[-] Socket error");
		exit(1);
	}
	printf("[+] UDP server online.\n");

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);

	int n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (n < 0) {
		perror("[-] Bind error");
		exit(1);
	}
	while (1) {
		bzero(buffer, 1024);
		addr_size = sizeof(client_addr);
		recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);
		if (strcmp(buffer, "time") == 0)
		{
			time_t t;
			time(&t);
			sendto(sockfd, ctime(&t), strlen(ctime(&t)), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
		}
	}
}

