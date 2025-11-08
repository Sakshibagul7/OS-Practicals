#include <stdio.h>
#define MAX 100
typedef struct {
int pid;
int arrival_time;
int burst_time;
int remaining_time;
int completion_time;
int waiting_time;
int turnaround_time;
int start_time;
} Process;
void sort_by_arrival(Process p[], int n) {
Process temp;
for (int i = 0; i < n-1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (p[j].arrival_time > p[j+1].arrival_time) {
temp = p[j];
p[j] = p[j+1];
p[j+1] = temp;
}
}
}
}
void sjf_preemptive(Process p[], int n) {
int completed = 0, time = 0, shortest = -1;
int min = 1e9;
int is_completed[MAX] = {0};
float total_waiting = 0, total_turnaround = 0;
printf("\n--- SJF Preemptive Scheduling ---\n");
while (completed != n) {
shortest = -1;
min = 1e9;
for (int i = 0; i < n; i++) {
if (p[i].arrival_time <= time && !is_completed[i] && p[i].remaining_time <
min && p[i].remaining_time > 0) {
min = p[i].remaining_time;
shortest = i;
}
}
if (shortest == -1) {
time++;
continue;
}
if (p[shortest].remaining_time == p[shortest].burst_time) {
p[shortest].start_time = time;
}
p[shortest].remaining_time--;
time++;
if (p[shortest].remaining_time == 0) {
p[shortest].completion_time = time;
p[shortest].turnaround_time = p[shortest].completion_time -
p[shortest].arrival_time;
p[shortest].waiting_time = p[shortest].turnaround_time -
p[shortest].burst_time;
is_completed[shortest] = 1;
completed++;
total_waiting += p[shortest].waiting_time;
total_turnaround += p[shortest].turnaround_time;
}
}
printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time,
p[i].burst_time,
p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
}
printf("Average Turnaround Time = %.2f\n", total_turnaround / n);
printf("Average Waiting Time = %.2f\n", total_waiting / n);
}
void round_robin(Process p[], int n, int quantum) {
int time = 0, completed = 0;
int queue[MAX], front = 0, rear = 0;
int visited[MAX] = {0};
float total_waiting = 0, total_turnaround = 0;
printf("\n--- Round Robin Scheduling (Time Quantum = %d) ---\n", quantum);
queue[rear++] = 0;
visited[0] = 1;
if (p[0].arrival_time > time)
time = p[0].arrival_time;
while (completed != n) {
if (front == rear) {
for (int i = 0; i < n; i++) {
if (p[i].remaining_time > 0) {
queue[rear++] = i;
visited[i] = 1;
if (p[i].arrival_time > time)
time = p[i].arrival_time;
break;
}
}
}
int idx = queue[front++];
if (p[idx].remaining_time == p[idx].burst_time) {
p[idx].start_time = time;
}
if (p[idx].remaining_time <= quantum) {
time += p[idx].remaining_time;
p[idx].remaining_time = 0;
p[idx].completion_time = time;
p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
total_waiting += p[idx].waiting_time;
total_turnaround += p[idx].turnaround_time;
completed++;
} else {
time += quantum;
p[idx].remaining_time -= quantum;
}
for (int i = 0; i < n; i++) {
if (p[i].arrival_time <= time && !visited[i] && p[i].remaining_time > 0) {
queue[rear++] = i;
visited[i] = 1;
}
}
if (p[idx].remaining_time > 0) {
queue[rear++] = idx;
}
}
printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time,
p[i].burst_time,
p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
}
printf("Average Turnaround Time = %.2f\n", total_turnaround / n);
printf("Average Waiting Time = %.2f\n", total_waiting / n);
}
int main() {
int n, choice, quantum;
Process p[MAX];
printf("Enter number of processes: ");
scanf("%d", &n);
for (int i = 0; i < n; i++) {
p[i].pid = i + 1;
printf("Enter arrival time for process P%d: ", p[i].pid);
scanf("%d", &p[i].arrival_time);
printf("Enter burst time for process P%d: ", p[i].pid);
scanf("%d", &p[i].burst_time);
p[i].remaining_time = p[i].burst_time;
p[i].start_time = -1; // initialize start_time
}
sort_by_arrival(p, n);
printf("\nChoose Scheduling Algorithm:\n");
printf("1. Shortest Job First (Preemptive)\n");
printf("2. Round Robin (with arrival time)\n");
printf("Enter choice: ");
scanf("%d", &choice);
if (choice == 1) {
sjf_preemptive(p, n);
} else if (choice == 2) {
printf("Enter Time Quantum: ");
scanf("%d", &quantum);
round_robin(p, n, quantum);
} else {
printf("Invalid Choice!\n");
}
return 0;
}

