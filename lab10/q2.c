#include <stdio.h>
#include <stdlib.h>

void lru(int numF, int numP, int *pages) {
    int *frames = (int *)malloc(numF * sizeof(int));
    int *lastUsed = (int *)malloc(numF * sizeof(int));
    int pageFaults = 0,hits=0;
    int time = 0;

    
    for (int i = 0; i < numF; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < numP; i++) {
        int pageFound = 0;

        
        for (int j = 0; j < numF; j++) {
            if (frames[j] == pages[i]) {
                pageFound = 1;
                lastUsed[j] = time++; 
                hits++;
                break;
            }
        }

        if (!pageFound) {
            int lruIndex = 0;
            for (int j = 1; j < numF; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j; 
                }
            }

            frames[lruIndex] = pages[i]; 
            lastUsed[lruIndex] = time++; 
            pageFaults++;
            
        }
        hits=pageFaults-hits;
    }

    printf("LRU Page Replacement: Number of page faults = %d\n", pageFaults);
    printf("hits %d\n",hits);
    free(frames);
    free(lastUsed);
}

int main() {
    int numF, numP;

    printf("Enter the number of frames: ");
    scanf("%d", &numF);
    printf("Enter the number of pages: ");
    scanf("%d", &numP);
    int *pages = (int *)malloc(numP * sizeof(int));
    printf("Enter the page numbers: ");
    for (int i = 0; i < numP; i++)
    {
        scanf("%d", &pages[i]);
    }
    lru(numF, numP, pages);
    free(pages);
    return 0;
}
