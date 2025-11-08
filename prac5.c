#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processes, resources;
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

void calculateNeed() {
for (int i = 0; i < processes; i++) {
for (int j = 0; j < resources; j++) {
need[i][j] = maximum[i][j] - allocation[i][j];
}
}
}

bool isSafe() {
int work[MAX_RESOURCES];
bool finish[MAX_PROCESSES] = {false};
int safeSequence[MAX_PROCESSES];
int count = 0;

for (int i = 0; i < resources; i++) {
work[i] = available[i];
}

while (count < processes) {
bool found = false;
for (int p = 0; p < processes; p++) {
if (!finish[p]) {
bool canAllocate = true;
for (int r = 0; r < resources; r++) {
if (need[p][r] > work[r]) {
canAllocate = false;
break;
}
}
if (canAllocate) {
for (int r = 0; r < resources; r++) {
work[r] += allocation[p][r];
}
safeSequence[count++] = p;
finish[p] = true;
found = true;
}
}
}
if (!found) {
printf("System is NOT in a safe state.\n");
return false;
}
}
printf("System is in a SAFE state.\nSafe Sequence: ");
for (int i = 0; i < processes; i++) {
printf("P%d ", safeSequence[i]);
}
printf("\n");
return true;
}
bool requestResources(int process_id, int request[]) {
for (int i = 0; i < resources; i++) {
if (request[i] > need[process_id][i]) {
printf("Error: Process has exceeded its maximum claim.\n");
return false;
}
}
for (int i = 0; i < resources; i++) {
if (request[i] > available[i]) {
printf("Resources not available. Process must wait.\n");
return false;
}
}
for (int i = 0; i < resources; i++) {
available[i] -= request[i];
allocation[process_id][i] += request[i];
need[process_id][i] -= request[i];
}
if (isSafe()) {
printf("Request granted.\n");
return true;
} else {
for (int i = 0; i < resources; i++) {
available[i] += request[i];
allocation[process_id][i] -= request[i];
need[process_id][i] += request[i];
}
printf("Request denied to avoid unsafe state.\n");
return false;
}
}
int main() {
printf("Enter number of processes: ");
scanf("%d", &processes);
printf("Enter number of resources: ");
scanf("%d", &resources);

printf("Enter allocation matrix:\n");
for (int i = 0; i < processes; i++) {
for (int j = 0; j < resources; j++) {
scanf("%d", &allocation[i][j]);
}
}
printf("Enter maximum matrix:\n");
for (int i = 0; i < processes; i++) {
for (int j = 0; j < resources; j++) {
scanf("%d", &maximum[i][j]);
}
}
printf("Enter available resources:\n");
for (int i = 0; i < resources; i++) {
scanf("%d", &available[i]);
}
calculateNeed();

isSafe();

char choice;
while (1) {
printf("\nDo you want to make a request? (y/n): ");
scanf(" %c", &choice);
if (choice != 'y' && choice != 'Y') break;

int pid;
printf("Enter process ID making the request (0 to %d): ", processes - 1);
scanf("%d", &pid);

int req[MAX_RESOURCES];
printf("Enter resource request for P%d:\n", pid);
for (int i = 0; i < resources; i++) {
scanf("%d", &req[i]);
}
requestResources(pid, req);
}
return 0;
}





