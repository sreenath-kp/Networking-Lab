#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define packetCount 10

int main()
{
    srand(time(0));
    int packets[packetCount], i, rate, bucketSize, filledSize = 0, timeToTransmit, clk, op;

    for (i = 0; i < packetCount; ++i)
        packets[i] = (rand() % 6 + 1) * 10;

    printf("\nEnter the Output rate:");
    scanf("%d", &rate);
    printf("Enter the Bucket Size:");
    scanf("%d", &bucketSize);

    i = 0;
    while (i < packetCount || filledSize > 0)
    {
        if (i < packetCount)
        {
            if ((packets[i] + filledSize) > bucketSize)
                printf("Bucket capacity exceeded! Packet %d overflow\n", packets[i]);
            else
            {
                filledSize += packets[i];
                printf("\n\nIncoming Packet size: %d", packets[i]);
                printf("\nBytes remaining to Transmit: %d", filledSize);
            }
            ++i;
        }

        timeToTransmit = (rand() % 4 + 1) * 10;
        printf("\nTime left for transmission: %d units\n", timeToTransmit);

        for (clk = 10; clk <= timeToTransmit; clk += 10)
        {
            sleep(1);
            if (filledSize)
            {
                if (filledSize <= rate)
                    op = filledSize, filledSize = 0;
                else
                    op = rate, filledSize -= rate;

                printf("\nPacket %d transmitted\n", op);
                printf("Bytes Remaining to Transmit: %d\n", filledSize);
            }
            else
            {
                printf("\nTime left for transmission: %d units", timeToTransmit - clk);
                printf("\nNo packets to transmit!!\n");
            }
        }
    }
}