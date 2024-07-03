#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int OddSum(int arr[10]) {
    int sum = 0;
    for(int i = 0; i < 10;i++)
    {
        if(arr[i]%2 != 0) {
            sum = sum + arr[i];
        }

    }
    return sum;
}
int EvenSum(int arr[10]) {
    int sum = 0;
    for(int i = 0; i < 10;i++)
    {
        if(arr[i]%2 == 0) {
            sum = sum + arr[i];
        }

    }
    return sum;
}
void main(){
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int pid = fork();
    if(pid<0) {
        printf("fork failed\n");
    }
    else if(pid == 0) {
        printf("%d\n",OddSum(arr));
    }
    else {
        wait(NULL);
        printf("%d\n",EvenSum(arr));
    }
}