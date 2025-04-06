#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INF 9999999

struct Process {
    int id;
    int BT;
    int priority;
    int AT;
    int remaining_time;
    int CT;
    int WT;
    int turn_around_time;
};

// Function prototypes
void calculateTimes(struct Process processes[], int n);
void printResults(struct Process processes[], int n);
int is_in_queue(int queue[], int process_idx, int rear);

void preemptiveSJF(struct Process p[], int n) {
    int completed = 0, current_time = 0, min_burst_time, shortest = -1;
    int is_completed[MAX] = {0};

    while (completed < n) {
        min_burst_time = INF;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && p[i].AT <= current_time && p[i].remaining_time < min_burst_time) {
                min_burst_time = p[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        p[shortest].remaining_time--;
        current_time++;

        if (p[shortest].remaining_time == 0) {
            p[shortest].CT = current_time;
            p[shortest].turn_around_time = p[shortest].CT - p[shortest].AT;
            p[shortest].WT = p[shortest].turn_around_time - p[shortest].BT;
            is_completed[shortest] = 1;
            completed++;
        }
    }

    calculateTimes(p, n);
    printResults(p, n);
}

void roundRobin(struct Process p[], int n, int time_quantum) {
    int completed = 0, current_time = 0, i;
    int is_completed[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;

    for (i = 0; i < n; i++) {
        if (p[i].AT <= current_time) {
            queue[rear++] = i;
        }
    }

    while (completed < n) {
        if (front == rear) {
            current_time++;
            for (i = 0; i < n; i++) {
                if (p[i].AT == current_time && !is_completed[i]) {
                    queue[rear++] = i;
                }
            }
            continue;
        }

        int p_idx = queue[front++];
        front %= MAX;

        if (is_completed[p_idx]) {
            continue;
        }

        int time_slice = (p[p_idx].remaining_time > time_quantum) ? time_quantum : p[p_idx].remaining_time;
        p[p_idx].remaining_time -= time_slice;
        current_time += time_slice;

        if (p[p_idx].remaining_time == 0) {
            p[p_idx].CT = current_time;
            p[p_idx].turn_around_time = p[p_idx].CT - p[p_idx].AT;
            p[p_idx].WT = p[p_idx].turn_around_time - p[p_idx].BT;
            is_completed[p_idx] = 1;
            completed++;
        }

        if (p[p_idx].remaining_time > 0) {
            for (i = 0; i < n; i++) {
                if (p[i].AT <= current_time && !is_completed[i] && !is_in_queue(queue, i, rear)) {
                    queue[rear++] = i;
                    rear %= MAX;
                }
            }
            queue[rear++] = p_idx;
            rear %= MAX;
        }
    }

    calculateTimes(p, n);
    printResults(p, n);
}

int is_in_queue(int queue[], int process_idx, int rear) {
    for (int i = 0; i < rear; i++) {
        if (queue[i] == process_idx) {
            return 1;
        }
    }
    return 0;
}

void nonPreemptivePriority(struct Process processes[], int n) {
    int completed = 0, current_time = 0, highest_priority, i;
    int is_completed[MAX] = {0};

    while (completed < n) {
        highest_priority = INF;
        int process_idx = -1;

        for (i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].AT <= current_time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                process_idx = i;
            }
        }

        if (process_idx != -1) {
            processes[process_idx].CT = current_time + processes[process_idx].BT;
            processes[process_idx].turn_around_time = processes[process_idx].CT - processes[process_idx].AT;
            processes[process_idx].WT = processes[process_idx].turn_around_time - processes[process_idx].BT;
            is_completed[process_idx] = 1;
            current_time = processes[process_idx].CT;
            completed++;
        } else {
            current_time++;
        }
    }

    calculateTimes(processes, n);
    printResults(processes, n);
}

void calculateTimes(struct Process processes[], int n) {
    float total_WT = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_WT += processes[i].WT;
        total_turnaround_time += processes[i].turn_around_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_WT / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void printResults(struct Process processes[], int n) {
    printf("\nProcess ID\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].BT,
               processes[i].AT,
               processes[i].CT,
               processes[i].WT,
               processes[i].turn_around_time);
    }
}

int main() {
    struct Process processes[MAX];
    int n, choice, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter burst times and arrival times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &processes[i].BT);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].AT);
        processes[i].remaining_time = processes[i].BT; 
        processes[i].priority = rand() % 10 + 1; }
    do {
        printf("\nMenu:\n");
        printf("1. Preemptive SJF\n");
        printf("2. Round Robin\n");
        printf("3. Non-preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                preemptiveSJF(processes, n);
                break;
            case 2:
                printf("Enter time quantum for Round Robin: ");
                scanf("%d", &time_quantum);
                roundRobin(processes, n, time_quantum);
                break;
            case 3:
                nonPreemptivePriority(processes, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");}
    } while (choice != 4);
    return 0;
}
