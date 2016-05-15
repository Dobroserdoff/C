#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "sync_queue.h"

#define POOL 4
#define QLENGTH 20

void* single (void*);

int main () {
    int i;
    pthread_t mythreads[POOL];
    char* string = { "Single string" };
    struct sync_queue_t queue;
    
    sync_queue_init(&queue, QLENGTH + POOL);
   
    for (i = 0; i < POOL; i++) {
        pthread_create(&mythreads[i], 0, single, &queue);
    }   
    
    for (i = 0; i < QLENGTH; i++) {
        sync_queue_enqueue(&queue, string);
    }

    for (i = 0; i < POOL; i++) {
        sync_queue_enqueue(&queue, NULL);
    }

    for (i = 0; i < POOL; i++) {
        pthread_join(mythreads[i], 0);
    }

    return 0;
}

void* single (void* param) {
    struct sync_queue_t* queue = (struct sync_queue_t*)param;
    char* temp;

    while ((temp = sync_queue_dequeue(queue)) != NULL) {
        puts(temp);
        fflush(stdout);
    }
}
