#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int EvenSum(int array[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            result += array[i];
        }
    }
    return result;
}

int OddSum(int array[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 != 0) {
            result += array[i];
        }
    }
    return result;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {

        printf("Child process - Sum of odd numbers: %d\n", OddSum(array, size));
    } else {
 
        wait(NULL);
        printf("Parent process - Sum of even numbers: %d\n", EvenSum(array, size));
    }

    return 0;
}
