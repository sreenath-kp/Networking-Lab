#include<stdio.h>
int sender();
int recv();
int timer = 0, wait_for_ack = -1, frameQ = 0, cansend = 1, t = 0;
int main()
{
    int i, j;
    int frame[5];

    printf("enter the time when data frame will be ready\n");
    for (i = 0; i < 3; i++)
    {

        sender( i, frame[i]);
        recv(i);
    }
}
int sender(int i, int frame[])
{
    wait_for_ack++;
    if (wait_for_ack == 3)
    {

        if (i == frame[t])
        {
            frameQ++;
            t++;
        }
        if (frameQ == 0)
            printf("NO FRAME TO SEND at time=%d \n", i);

        if (frameQ > 0 && cansend == 1)
        {
            printf("FRAME SEND AT TIME=%d\n", i);
            cansend = -1;
            frameQ--;
            timer++;
            printf("timer in sender=%d\n", timer);
        }
        if (frameQ > 0 && cansend == -1)
            printf("FRAME IN Q FOR TRANSMISSION AT TIME=%d\n", i);
        if (frameQ > 0)
            t++;
    }
    printf("frameQ=%d\n", frameQ);
    printf("i=%d     t=%d\n", i, t);
    printf("value in frame=%d\n", frame[t]);
    return 0;
}





int recv(int i )
{   printf("timer in recvr=%d\n", timer);
    if (timer > 0)
    {
        timer++;
    }
    if (timer == 3)
    {
        printf("FRAME ARRIVED AT TIME= %d\n", i);
        wait_for_ack = 0;
        timer = 0;
    }
    else
        printf("WAITING FOR FRAME AT TIME %d\n", i);
    return 0;

}

