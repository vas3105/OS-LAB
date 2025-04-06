#include <stdio.h>
#include <stdlib.h>

void fifo(int numFrames, int numPages, int *pages) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    int pageFaults = 0, index = 0;

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        int pageFound = 0;

        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            frames[index] = pages[i];
            index = (index + 1) % numFrames; 
            
            pageFaults++;
        }
    }

    printf("FIFO Page Replacement: Number of page faults = %d\n", pageFaults);
    
    free(frames);
}

void optimal(int numFrames, int numPages, int *pages) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        int pageFound = 0;

        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            int replaceIndex = -1;
            int farthest = -1;

            for (int j = 0; j < numFrames; j++) {
                int k;
                for (k = i + 1; k < numPages; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                if (k == numPages) {
                    replaceIndex = j;
                    break;
                }
            }

            frames[replaceIndex] = pages[i];
            pageFaults++;
        }
    }

    printf("Optimal Page Replacement: Number of page faults = %d\n", pageFaults);
    free(frames);
}

int main() {
    int numFrames, numPages;

    
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int *pages = (int *)malloc(numPages * sizeof(int));

    printf("Enter the page numbers: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    fifo(numFrames, numPages, pages);

    optimal(numFrames, numPages, pages);
    free(pages);

    return 0;
}
