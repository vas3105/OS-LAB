#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

sem_t x, y; 
pthread_t writerthreads[100], readerthreads[100]; 
int readercount = 0;
typedef struct {
    int reader_id;
} reader_data;

void *reader(void *param) {
    reader_data *data = (reader_data *)param;
    sem_wait(&x);
    readercount++;
    if (readercount == 1) {
        sem_wait(&y);
    }
    sem_post(&x); 
    printf("\nReader %d is inside", data->reader_id);
    sem_wait(&x); 
    readercount--;
    if (readercount == 0) {
        sem_post(&y); 
    }
    sem_post(&x); 
    printf("\nReader %d is leaving", data->reader_id);
    return NULL;
}

void *writer(void *param) {
    printf("\nWriter is trying to enter");
    sem_wait(&y); 
    printf("\nWriter has entered");
    printf("\nWriter is leaving");
    sem_post(&y); 
    return NULL;
}

int main() {
    int n2, i;
    printf("Enter the number of threads ");
    scanf("%d", &n2);
    sem_init(&x, 0, 1); 
    sem_init(&y, 0, 1); 
    for (i = 0; i < n2; i++) {
        reader_data *data = (reader_data *)malloc(sizeof(reader_data));
        data->reader_id = i + 1;
        pthread_create(&readerthreads[i], NULL, reader, data);
        pthread_create(&writerthreads[i], NULL, writer, NULL);
    }
    for (i = 0; i < n2; i++) {
        pthread_join(readerthreads[i], NULL);
        pthread_join(writerthreads[i], NULL);
    }
    sem_destroy(&x);
    sem_destroy(&y);
    return 0;
}
