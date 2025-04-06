#include <stdio.h>
#include <stdlib.h>
#define MAX 25

void bestFit(int b[], int f[], int nb, int nf);
void firstFit(int b[], int f[], int nb, int nf);

void main() {
    int b[MAX], f[MAX], i, nb, nf, choice;
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of the blocks:\n");
    for (i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 1; i <= nf; i++) {
        printf("File %d: ", i);
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
}
void bestFit(int b[], int f[], int nb, int nf) {
    int frag[MAX], bf[MAX] = {0}, ff[MAX], i, j, temp, lowest;

    for (i = 1; i <= nf; i++) {
        lowest = 10000; 
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {  
                temp = b[j] - f[i]; 
                if (temp >= 0 && temp < lowest) {  
                    ff[i] = j;  
                    lowest = temp;
                }
            }
        }

        frag[i] = lowest; 
        if (ff[i] != 0) { 
            bf[ff[i]] = 1;  
        }
    }
    printf("\nBest Fit Allocation:\n");
    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");
    for (i = 1; i <= nf && ff[i] != 0; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, f[i], ff[i], b[ff[i]], frag[i]);
    }
}
void firstFit(int b[], int f[], int nb, int nf) {
    int frag[MAX], bf[MAX] = {0}, ff[MAX], i, j;
    printf("\nFirst Fit Allocation:\n");
    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment\n");
    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1 && b[j] >= f[i]) {  
                ff[i] = j;
                frag[i] = b[j] - f[i];  
                bf[j] = 1;  
                break;  
            }
        }
        if (bf[ff[i]] != 1) {
            frag[i] = -1;  
        }
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, f[i], ff[i], b[ff[i]], frag[i]);
    }
}
