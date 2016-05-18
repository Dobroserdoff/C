#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "sync_queue.h"
#include "qsort.h"

#define POOL 4

void* single (void*);

int main () {
    int i;
    pthread_t mythreads[POOL];
    struct sync_queue_t queue;
    struct params st, *stp;
    counter = 0;
    
    puts("Unsorted array of integers:");
    for (i = 0; i < ARSIZE; i++) {
        ar[i] = rand() % 100;
        printf("%d ", ar[i]);
    }
    putchar('\n');

    st.p = &ar[0];
    st.size = ARSIZE;
    stp = malloc(sizeof(void*));
    stp = &st;
    
    counter++;
    sync_queue_init(&queue, ARSIZE + POOL);   
    
    for (i = 0; i < POOL; i++) {
        pthread_create(&mythreads[i], 0, single, &queue);
    }   
    
    sync_queue_enqueue(&queue, stp);
    
    for (i = 0; i < POOL; i++) {
        pthread_mutex_lock(&finish_mutex);
        pthread_cond_wait(&finish_condvar, &finish_mutex);
    }

    counter--;

    for (i = 0; i < POOL; i++) {
        pthread_join(mythreads[i], 0);
    }

    puts("Sorted array of integers:");
    for (i = 0; i < ARSIZE; i++) {
        printf("%d ", ar[i]);
    }
    putchar('\n');
    
    return 0;
}

void* single (void* param) {
    while (counter > 0) {
        struct params* temp = sync_queue_dequeue(param);
        printf("%d ", *(temp->p));
        quicksort(param, &temp); 
    }
    return 0;
}
