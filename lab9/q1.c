#include <stdio.h>
#include <stdlib.h>
#define MAX 25

void bestFit(int b[], int f[], int nb, int nf);
void firstFit(int b[], int f[], int nb, int nf);

int main() {
    int b[MAX], f[MAX], i, nb, nf, choice;
    
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of the blocks:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i+1);
        scanf("%d", &b[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 0; i < nf; i++) {
        printf("File %d: ", i+1);
        scanf("%d", &f[i]);
    }

    printf("\nChoose an allocation method:\n");
    printf("1. Best Fit\n");
    printf("2. First Fit\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            bestFit(b, f, nb, nf);
            break;
        case 2:
            firstFit(b, f, nb, nf);
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}

void bestFit(int b[], int f[], int nb, int nf) {
    int frag[MAX], bf[MAX] = {0}, ff[MAX], i, j, temp, lowest;

    for (i = 0; i < nf; i++) {
        lowest = 10000;
        ff[i] = -1;  // initialize
        for (j = 0; j < nb; j++) {
            if (bf[j] == 0) {
                temp = b[j] - f[i];
                if (temp >= 0 && temp < lowest) {
                    ff[i] = j;
                    lowest = temp;
                }
            }
        }

        frag[i] = (ff[i] != -1) ? (b[ff[i]] - f[i]) : -1;
        if (ff[i] != -1) {
            bf[ff[i]] = 1; // mark block as filled
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");
    for (i = 0; i < nf; i++) {
        if (ff[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, f[i], ff[i]+1, b[ff[i]], frag[i]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, f[i]);
        }
    }
}

void firstFit(int b[], int f[], int nb, int nf) {
    int frag[MAX], bf[MAX] = {0}, ff[MAX], i, j;

    printf("\nFirst Fit Allocation:\n");
    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");

    for (i = 0; i < nf; i++) {
        ff[i] = -1; // initialize
        for (j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= f[i]) {
                ff[i] = j;
                frag[i] = b[j] - f[i];
                bf[j] = 1;
                break;
            }
        }

        if (ff[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, f[i], ff[i]+1, b[ff[i]], frag[i]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, f[i]);
        }
    }
}
