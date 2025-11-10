#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-1-i; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        int min_idx = i;
        for(int j=i+1; j<n; j++) {
            if(arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void printArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    if(!arr) {
        perror("malloc failed");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork failed");
        free(arr);
        return 1;
    }
    else if(pid == 0) {
        // Child process
        printf("\n[Child] PID: %d, Parent PID: %d\n", getpid(), getppid());

        int *childArr = malloc(n * sizeof(int));
        for(int i=0; i<n; i++)
            childArr[i] = arr[i];

        selectionSort(childArr, n);

        printf("[Child] Sorted array (Selection Sort): ");
        printArray(childArr, n);

        free(childArr);

        printf("[Child] Exiting now.\n");
        exit(0);
    }
    else {
        // Parent process
        printf("\n[Parent] PID: %d, Child PID: %d\n", getpid(), pid);

        bubbleSort(arr, n);

        // Uncomment below wait() to avoid zombie; comment out to see zombie process
        int status;
        wait(&status);

        printf("[Parent] Child terminated. Parent sorting result:\n");
        printf("[Parent] Sorted array (Bubble Sort): ");
        printArray(arr, n);

        // Sleep to observe orphan if child sleeps longer than parent
        printf("[Parent] Sleeping for 10 seconds...\n");
        sleep(10);

        printf("[Parent] Parent exiting.\n");
        free(arr);
        return 0;
    }
}
