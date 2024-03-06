#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Failed to fork.\n");
        return 1;
    }

    if (pid > 0) { 
        int num;
        printf("Enter a number: ");
        scanf("%d", &num);

        if (isPrime(num)) {
            printf("Parent process: %d is a prime number.\n", num);
        } else {
            printf("Parent process: %d is not a prime number.\n", num);
        }
    } else if (pid == 0) { 
        
    }

    return 0;
}
