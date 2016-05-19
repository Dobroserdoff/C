#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "sync_queue.h"
#include "qsort.h"

#define POOL 4

void* single (void*);

int main () {
    int i, sum1, sum2;
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

    sum1 = ar[0];
    for (i = 1; i < ARSIZE; i++) {
        sum1 += ar[i];
    }

    st.p = &ar[0];
    st.size = ARSIZE;
    stp = malloc(sizeof(void*));
    stp = &st;
    
    sync_queue_init(&queue, 2*(ARSIZE + POOL));   
    
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
    } else {    
        pthread_mutex_unlock(&finish_mutex);
    }
    
    queue_collapse(&queue.sp);

    for (i = 0; i < POOL; i++) {
        pthread_join(mythreads[i], 0);
    }
    
    sum2 = ar[0];
    for (i = 1; i < ARSIZE; i++) {
        sum2 += ar[i];
    }

    for (i = 1; i < ARSIZE; i++) {
        if ((ar[i] < ar[i - 1]) || (sum1 != sum2)) {
            puts("Array was sorted incorrectly");
        }
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
        quicksort(param, temp); 
    }
    return 0;
}
