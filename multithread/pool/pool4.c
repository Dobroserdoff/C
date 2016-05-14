#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define POOL 4
#define QLENGTH 10

struct queue_t {
    pthread_mutex_t single_mutex;
    pthread_cond_t single_condvar;
    char** sp;
};

void* single (void*);
void enqueue (struct queue_t*, char*);
char* dequeue (struct queue_t*);

int main () {
    int i;
    char* string = { "Single string" };
    pthread_t mythreads[POOL];
    struct queue_t queue;
    
    queue.sp = malloc(sizeof(char*) * QLENGTH); 
   
    *queue.sp++ = NULL;
    pthread_mutex_init(&queue.single_mutex, 0);
    pthread_cond_init(&queue.single_condvar, 0);
    
    for (i = 0; i < POOL; i++) {
        pthread_create(&mythreads[i], 0, single, &queue);
    }   
    
    for (i = 0; i < QLENGTH; i++) {
        enqueue(&queue, string);
    }

    for (i = 0; i < POOL; i++) {
        pthread_join(mythreads[i], 0);
    }

    return 0;
}

void* single (void* param) {
    struct queue_t* queue = (struct queue_t*)param;
    char* temp;

    while ((temp = dequeue(queue)) != NULL) {
        puts(temp);
        fflush(stdout);
    }
    
}

void enqueue (struct queue_t* queue, char* value) {
    pthread_mutex_lock(&queue->single_mutex);
    *queue->sp++ = value;
    pthread_cond_signal(&queue->single_condvar);
    pthread_mutex_unlock(&queue->single_mutex);
}

char* dequeue (struct queue_t* queue) {
    while (1) { 
        char *temp = NULL;

        pthread_mutex_lock(&queue->single_mutex);
        if (*queue->sp != NULL) {
            temp = *queue->sp--;
            pthread_mutex_unlock(&queue->single_mutex);
            return temp;
        } else {
            pthread_cond_wait(&queue->single_condvar, &queue->single_mutex);
        }
   }
}
