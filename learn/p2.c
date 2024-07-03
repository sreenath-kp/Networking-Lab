// print hello 5 times sleep for 1s in intervel
#include <stdio.h>
#include<unistd.h>
void main() {
    for (int i = 0; i < 5; i++)
    {
        printf("hello\n");
        // fflush(stdout);
        sleep(1);
    }

}