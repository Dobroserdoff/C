#include <pthread.h>
#include "sync_queue.h"

int counter;

void sync_queue_init(struct sync_queue_t* queue, size_t count) {
    queue_init(&queue->sp, count);
    pthread_mutex_init(&queue->single_mutex, 0);
    pthread_cond_init(&queue->single_condvar, 0);
}

void sync_queue_enqueue(struct sync_queue_t* queue, void* value) {
    pthread_mutex_lock(&queue->single_mutex);
    queue_enqueue(&queue->sp, value);
    pthread_cond_signal(&queue->single_condvar);
    pthread_mutex_unlock(&queue->single_mutex);
}

void* sync_queue_dequeue(struct sync_queue_t* queue) {
    while (1) { 
        void* temp = NULL;

        pthread_mutex_lock(&queue->single_mutex);
        if (!queue_empty(&queue->sp)) {
            temp = queue_dequeue(&queue->sp);
            pthread_mutex_unlock(&queue->single_mutex);
            return temp;
        } else {
            pthread_cond_wait(&queue->single_condvar, &queue->single_mutex);
            pthread_mutex_unlock(&queue->single_mutex);
        }
   }
}
