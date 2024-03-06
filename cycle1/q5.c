#include <stdio.h>
#include<unistd.h>

int main() {
    int i;
    for(i=0; i<5; i++) 
    {
       printf("hello\n");
       // fflush(stdout);
       sleep(1);
    }       
}