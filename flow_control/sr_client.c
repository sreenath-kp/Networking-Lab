#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define timeoutValue 5
#define packetCount 6
#define windowSize 3

typedef struct Packet
{
    int id;
    int sent;
} Packet;

Packet packets[packetCount];
pthread_t thread[packetCount], receiveThread;
int sockfd;
struct sockaddr_in addr;
int windowStart, windowEnd;
int nextToSend;

void *sendPacket(void *sendPacket)
{
    Packet packet = *(Packet *)sendPacket;
    char buffer[1024];

    // Continuously send the packet until it is acknowledged
    while (packet.sent == 0)
    {
        printf("Client: Sending packet %d\n", packet.id);
        bzero(buffer, 1024);
        sprintf(buffer, "%d", packet.id);

        sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
        sleep(timeoutValue);
        if (packet.sent == 0)
            printf("Client: Timeout for packet %d\n", packet.id);
    }
}

void *receivePacket()
{
    socklen_t addr_size = sizeof(addr);
    char buffer[1024];

    while (1)
    {
        bzero(buffer, 1024);
        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);

        char msg[20];
        int packetID;

        sscanf(buffer, "%s%d", msg, &packetID);

        // If the message is a negative acknowledgment (NACK), restart the thread for the corresponding packet.
        if (strcmp(msg, "NACK") == 0)
        {
            printf("Client: Received negative acknowledgment for packet %d\nSending again\n", packetID);
            pthread_cancel(thread[packetID]);
            pthread_create(&thread[packetID], NULL, sendPacket, (void *)&packets[packetID]);

            // If the message is an acknowledgment (ACK), mark the packet as sent.
        }
        else if (strcmp(msg, "ACK") == 0)
        {
            printf("Client: Received acknowledgement for packet %d\n", packetID);
            packets[packetID].sent = 1;
            if (windowStart == packetID)
            {
                while (packets[windowStart].sent == 1)
                {
                    windowStart++;
                    if (windowEnd < packetCount)
                        windowEnd++;
                }
            }
        }
        else
            printf("Client: Invalid message\n");
    }
}

void main()
{
    for (int i = 0; i < packetCount; ++i)
    {
        packets[i].id = i;
        packets[i].sent = 0;
    }

    char *ip = "127.0.0.105";
    int port = 5500;

    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("[-] Socket error ");
        exit(1);
    }

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Create a thread for receiving acknowledgments
    pthread_create(&receiveThread, NULL, receivePacket, NULL);

    windowStart = 0;
    windowEnd = windowStart + windowSize - 1;

    // Create threads to send packets within the window.
    for (int i = windowStart; i <= windowEnd; ++i)
        pthread_create(&thread[i], NULL, sendPacket, (void *)&packets[i]);

    // Continuously send packets as long as the window is not empty
    nextToSend = windowEnd + 1;
    while (windowStart != windowEnd)
    {
        if (nextToSend <= windowEnd && nextToSend < packetCount)
        {
            pthread_create(&thread[nextToSend], NULL, sendPacket, (void *)&packets[nextToSend]);
            nextToSend++;
        }
    }

    close(sockfd);
}