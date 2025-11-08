#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SSTF();
int SCAN();
int CLOOK();

int main() {
    int ch, YN = 1;

    do {
        printf("\n\n\t*********** MENU ***********");
        printf("\n\n\t1: SSTF");
        printf("\n\t2: SCAN");
        printf("\n\t3: C-LOOK");
        printf("\n\t4: EXIT");
        printf("\n\n\tEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                SSTF();
                break;
            case 2:
                SCAN();
                break;
            case 3:
                CLOOK();
                break;
            case 4:
                exit(0);
            default:
                printf("\nInvalid choice! Try again.\n");
        }

        printf("\n\n\tDo you want to continue? (1 = Yes, 0 = No): ");
        scanf("%d", &YN);

    } while (YN == 1);

    return 0;
}

//////////////////////////////////////////////
// SSTF Algorithm
//////////////////////////////////////////////
int SSTF() {
    int RQ[100], n, TotalHeadMovement = 0, initial, count = 0;

    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initial);

    while (count != n) {
        int min = 1000, d, index = -1;
        for (int i = 0; i < n; i++) {
            if (RQ[i] != 1000) {  // skip processed requests
                d = abs(RQ[i] - initial);
                if (min > d) {
                    min = d;
                    index = i;
                }
            }
        }
        TotalHeadMovement += min;
        initial = RQ[index];
        RQ[index] = 1000; // mark as processed
        count++;
    }

    printf("\nTotal head movement is %d\n", TotalHeadMovement);
    return 0;
}

//////////////////////////////////////////////
// SCAN Algorithm
//////////////////////////////////////////////
int SCAN() {
    int RQ[100], n, TotalHeadMovement = 0, initial, size, move;

    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter the head movement direction (1 = high, 0 = low): ");
    scanf("%d", &move);

    // Sort the request queue
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) {  // move towards high
        for (int i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs((size - 1) - initial);
        initial = size - 1;
        for (int i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else {  // move towards low
        for (int i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(initial - 0);
        initial = 0;
        for (int i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("\nTotal head movement is %d\n", TotalHeadMovement);
    return 0;
}

//////////////////////////////////////////////
// C-LOOK Algorithm
//////////////////////////////////////////////
int CLOOK() {
    int RQ[100], n, TotalHeadMovement = 0, initial, size, move;

    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter the head movement direction (1 = high, 0 = low): ");
    scanf("%d", &move);

    // Sort the request queue
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) {  // move towards high
        for (int i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (int i = 0; i < index; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else {  // move towards low
        for (int i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (int i = n - 1; i >= index; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("\nTotal head movement is %d\n", TotalHeadMovement);
    return 0;
}

