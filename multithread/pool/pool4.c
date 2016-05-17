#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "sync_queue.h"
#include "qsort.h"

#define POOL 4

struct counter_t counter;

void* single (void*);

int main () {
    int i;
    pthread_t mythreads[POOL];
    struct sync_queue_t queue;
    struct params st, *stp;
    counter.counter = 0;
    
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

    sync_queue_init(&queue, ARSIZE + POOL);   
    counter_plus(&counter);
    sync_queue_enqueue(&queue, stp);
    
    for (i = 0; i < POOL; i++) {
        pthread_create(&mythreads[i], 0, single, &queue);
    }   

    for (i = 0; i < POOL; i++) {
        pthread_join(mythreads[i], 0);
    }

    return 0;
}

void* single (void* param) {
    struct sync_queue_t* temp = (void*) param;
    
    while (counter.counter > 0 && queue_empty(&temp->sp) != 1) {
        quicksort(&temp);
    }
    return 0;
}
