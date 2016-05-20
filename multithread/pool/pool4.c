#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "sync_queue.h"
#include "qsort.h"

#define POOL 8

pthread_mutex_t finish_mutex;
pthread_cond_t finish_condvar;

void* single (void*);

int main () {
    int i, sum1, sum2;
    pthread_t mythreads[POOL];
    struct sync_queue_t queue;
    struct params *stp;
    counter = 0;
    
    puts("Unsorted array of integers:");
    for (i = 0; i < ARSIZE; i++) {
        ar[i] = rand() % 100;
        printf("%d ", ar[i]);
    }
    putchar('\n');

    sum1 = ar[0];
    for (i = 1; i < ARSIZE; i++) {
        sum1 += ar[i];
    }

    stp = malloc(sizeof(struct params));
    stp->p = &ar[0];
    stp->size = ARSIZE;

    sync_queue_init(&queue, 10*(ARSIZE + POOL));   
    
    for (i = 0; i < POOL; i++) {
        pthread_create(&mythreads[i], 0, single, &queue);
    }   
   
    pthread_mutex_lock(&finish_mutex);
    counter++;
    pthread_mutex_unlock(&finish_mutex);
    sync_queue_enqueue(&queue, stp);
    
    pthread_mutex_lock(&finish_mutex);
    if (counter != 0) {
        pthread_cond_wait(&finish_condvar, &finish_mutex);
    }
    pthread_mutex_unlock(&finish_mutex);

    for (i = 0; i < POOL; i++) {
        sync_queue_enqueue(&queue, 0);
    }
    
    for (i = 0; i < POOL; i++) {
        pthread_join(mythreads[i], 0);
    }

    queue_collapse(&queue.sp);
    
    sum2 = ar[0];
    for (i = 1; i < ARSIZE; i++) {
        sum2 += ar[i];
    }

    for (i = 1; i < ARSIZE; i++) {
        if ((ar[i] < ar[i - 1]) || (sum1 != sum2)) {
        }
    }

    puts("\nSorted array of integers:");
    for (i = 0; i < ARSIZE; i++) {
        printf("%d ", ar[i]);
    }
    putchar('\n');
    
    return 0;
}

void* single (void* param) {
    while (1) {
        struct params* temp = sync_queue_dequeue(param);
        if (!temp) {
            break;
        }
        quicksort(param, temp, 0); 
    }
    return 0;
}
