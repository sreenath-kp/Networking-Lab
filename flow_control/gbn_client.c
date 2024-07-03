#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#define port 3440

int total_packets = 10;

void send_window_packets(int start, int end, int sockfd, struct sockaddr_in serv_address, int f)
{
    char buffer[512];
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "%d", start);
    sleep(2);
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_address, sizeof(serv_address));
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "%d", end);
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_address, sizeof(serv_address));
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "%d", f);
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_address, sizeof(serv_address));
    if (f == 1)
    {
        for (int i = start; i <= end; i++)
        {
            printf("Packet %d sent\n", i);
        }
    }
    else
    {
        printf("Packet %d sent\n", end);
    }
}

void main()
{
    // Initializing socket parameters
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed\n");
        exit(0);
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;
    int len = sizeof(serv_addr);

    // Inititalizing window parameters
    int window_size = 3;
    int start = 1;
    int end = 3;

    // To avoid infinite waiting and cause timeout
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int sock_status = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    char buffer[512];
    int byteRec;
    int n;
    int f = 1; // At first whole window needs to be send
    while (start <= total_packets)
    {
        // Call send_window_packets to send packets in the current window
        send_window_packets(start, end, sockfd, serv_addr, f);

        // Receive acknowledgment from the server
        bzero(buffer, sizeof(buffer));
        byteRec = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_addr, &len);

        // If a timeout occurs, print a timeout error and resend the window
        if (byteRec < 0)
        {
            printf("Timeout error\nResending the window\n");
            f = 1;
            continue;
        }

        // Convert the received acknowledgment to an integer n
        n = atoi(buffer);
        printf("Acknowledgemnet for packet %d recieved\n", n);

        // If n matches the start packet number(If an acknowledgment is received for the first packet, the window slides forward), update start and end for the next window
        if (n == start)
        {
            // If first packet is successfully reached
            // ie ack of first packet in window is recieved
            // then window is moved right
            // then only end element needs to be send
            f = 0; 
            // If all packets are sent, print a message and exit
            if (start == total_packets)
            {
                printf("All packets sent\n");
                exit(0);
            }
            // window reached the end
            if (end == total_packets)
            {
                start++;
            }
            else
            {
                // window is moved one step right
                start = start + 1;
                end = end + 1;
            }
        }
        else
        {
            // If n does not match, ie ack of first packet is not recieved
            // print a timeout error and resend the window
            f = 1; // to resend the window , set f = 1 and continue;
            printf("Timeout error\n");
            printf("Resending the window\n");
        }
    }
}
