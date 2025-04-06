#include <stdio.h>

struct Task {
    int id;
    int execTime;
    int period;
    int deadline;
    int nextRelease;
    int remainingTime;
    int absDeadline;
};

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int getHyperPeriod(struct Task tasks[], int n) {
    int result = tasks[0].period;
    for (int i = 1; i < n; i++) {
        result = lcm(result, tasks[i].period);
    }
    return result;
}

void RMS(struct Task tasks[], int n) {
    int hyperPeriod = getHyperPeriod(tasks, n);
    for (int i = 0; i < n; i++) {
        tasks[i].nextRelease = 0;
        tasks[i].remainingTime = 0;
    }

    for (int t = 0; t < hyperPeriod; t++) {
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].nextRelease) {
                if (tasks[i].remainingTime > 0) {
                    printf("Missed deadline for Task %d at time %d\n", tasks[i].id, t);
                }
                tasks[i].remainingTime = tasks[i].execTime;
                tasks[i].nextRelease += tasks[i].period;
            }
        }

        int chosen = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remainingTime > 0) {
                if (chosen == -1 || tasks[i].period < tasks[chosen].period) {
                    chosen = i;
                }
            }
        }

        if (chosen != -1) {
            printf("Time %d:  %d \n", t, tasks[chosen].id);
            tasks[chosen].remainingTime--;
        } else {
            printf("Time %d: CPU is idle\n", t);
        }
    }
}

void EDF(struct Task tasks[], int n) {
    int hyperPeriod = getHyperPeriod(tasks, n);
    for (int i = 0; i < n; i++) {
        tasks[i].nextRelease = 0;
        tasks[i].remainingTime = 0;
        tasks[i].absDeadline = 0;
    }

    for (int t = 0; t < hyperPeriod; t++) {
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].nextRelease) {
                if (tasks[i].remainingTime > 0) {
                    printf("Missed deadline for Task %d at time %d\n", tasks[i].id, t);
                }
                tasks[i].remainingTime = tasks[i].execTime;
                tasks[i].absDeadline = t + tasks[i].deadline;
                tasks[i].nextRelease += tasks[i].period;
            }
        }

        int chosen = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remainingTime > 0) {
                if (chosen == -1 || tasks[i].absDeadline < tasks[chosen].absDeadline) {
                    chosen = i;
                }
            }
        }

        if (chosen != -1) {
            printf("Time %d:  %d\n", t, tasks[chosen].id);
            tasks[chosen].remainingTime--;
        } else {
            printf("Time %d: CPU is idle\n", t);
        }
    }
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];
    for (int i = 0; i < n; i++) {
        printf("Enter execTime, period, deadline for Task %d: ", i + 1);
        scanf("%d %d %d", &tasks[i].execTime, &tasks[i].period, &tasks[i].deadline);
        tasks[i].id = i + 1;
    }

    int choice;
    printf("\nSelect scheduling algorithm:\n");
    printf("1. Rate Monotonic (RMS)\n");
    printf("2. Earliest Deadline First (EDF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        RMS(tasks, n);
    } else if (choice == 2) {
        EDF(tasks, n);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
