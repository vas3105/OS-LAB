#include <stdlib.h>
#include <stdio.h>

void main() {
    int k = 0, a = 0, b = 0, instance[5], availability[5], allocated[10][5], need[10][5], MAX[10][5];
    int process, P[10], no_of_resources, cnt = 0, op[10], i, j;
    
    // Input the number of resources
    printf("\n Enter the number of resources: ");
    scanf("%d", &no_of_resources);

    // Input max instances of each resource
    printf("\n Enter the max instances of each resource:\n");
    for (i = 0; i < no_of_resources; i++) {
        availability[i] = 0;
        printf("%c= ", (i + 97));  // 'a' corresponds to the first resource type
        scanf("%d", &instance[i]);
    }

    // Input the number of processes
    printf("\n Enter the number of processes: ");
    scanf("%d", &process);

    // Input the allocation matrix
    printf("\n Enter the allocation matrix:\n     ");
    for (i = 0; i < no_of_resources; i++)
        printf(" %c", (i + 97));  // Display resource names
    printf("\n");

    for (i = 0; i < process; i++) {
        P[i] = i;
        printf("P[%d]  ", P[i]);
        for (j = 0; j < no_of_resources; j++) {
            scanf("%d", &allocated[i][j]);
            availability[j] += allocated[i][j];
        }
    }

    // Calculate the available instances of each resource
    printf("\n Enter the MAX matrix:\n     ");
    for (i = 0; i < no_of_resources; i++) {
        printf(" %c", (i + 97));  // Display resource names
        availability[i] = instance[i] - availability[i];
    }
    printf("\n");

    for (i = 0; i < process; i++) {
        printf("P[%d]  ", i);
        for (j = 0; j < no_of_resources; j++)
            scanf("%d", &MAX[i][j]);
    }

    // Banker's Algorithm to find the safe sequence
    while (1) {
        int safe = 0;
        for (i = 0; i < process; i++) {
            cnt = 0;
            b = P[i];
            for (j = 0; j < no_of_resources; j++) {
                need[b][j] = MAX[b][j] - allocated[b][j];
                if (need[b][j] <= availability[j]) {
                    cnt++;
                }
            }

            if (cnt == no_of_resources) {
                // If process P[i] can be completed
                op[k++] = P[i];
                for (j = 0; j < no_of_resources; j++) {
                    availability[j] += allocated[b][j];  // Release allocated resources
                }
                P[i] = -1;  // Mark process P[i] as completed
                safe = 1;
            }
        }

        // If no process could be completed, exit the loop
        if (!safe) {
            break;
        }
    }

    // Output the safe sequence
    printf("\nSafe sequence: <");
    for (i = 0; i < k; i++) {
        printf(" P[%d] ", op[i]);
    }
    printf(">\n");
}
