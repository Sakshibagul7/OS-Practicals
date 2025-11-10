#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter array size: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubble_sort(arr, n);

    printf("Parent sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char *args[n + 2];     
    char str_arr[n][10];     

    args[0] = "./child";    

    for (int i = 0; i < n; i++) {
        sprintf(str_arr[i], "%d", arr[i]); 
        args[i + 1] = str_arr[i];
    }
    args[n + 1] = NULL; 

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        if (execve(args[0], args, NULL) == -1) {
            perror("Execve failed");
            exit(1);
        }
    } 
    else {
        wait(NULL);
        printf("Parent: Child process completed.\n");
    }

    return 0;
}
