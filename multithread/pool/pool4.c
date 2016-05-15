#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define POOL 4
#define QLENGTH 20

struct simple_queue {
    char** start;
    char** end; 
};
struct queue_t {
    pthread_mutex_t single_mutex;
    pthread_cond_t single_condvar;
    struct simple_queue sp;
};

void simple_queue_init (struct simple_queue*);
void queue_init(struct queue_t*);
void* single (void*);
void enqueue (struct queue_t*, char*);
void simple_enqueue (struct simple_queue*, char*);
char* dequeue (struct queue_t*);
char* simple_dequeue (struct simple_queue*);

int main () {
    int i;
    pthread_t mythreads[POOL];
    char* string = { "Single string" };
    struct queue_t queue;
    
    queue_init(&queue);
   
    for (i = 0; i < POOL; i++) {
        pthread_create(&mythreads[i], 0, single, &queue);
    }   
    
    for (i = 0; i < QLENGTH; i++) {
        enqueue(&queue, string);
    }

    for (i = 0; i < POOL; i++) {
        enqueue(&queue, NULL);
    }

    for (i = 0; i < POOL; i++) {
        pthread_join(mythreads[i], 0);
    }

    return 0;
}

void queue_init (struct queue_t* queue) {
    simple_queue_init(&queue->sp);
    pthread_mutex_init(&queue->single_mutex, 0);
    pthread_cond_init(&queue->single_condvar, 0);
}

void simple_queue_init (struct simple_queue* sqp) {
    int i;

    sqp->start = malloc(sizeof(char*) * (QLENGTH + POOL)); 
    sqp->end = sqp->start;
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
    simple_enqueue(&queue->sp, value);
    pthread_cond_signal(&queue->single_condvar);
    pthread_mutex_unlock(&queue->single_mutex);
}

void simple_enqueue (struct simple_queue* sp, char* value) {
    *sp->end++ = value;
}

char* dequeue (struct queue_t* queue) {
    while (1) { 
        char *temp = NULL;

        pthread_mutex_lock(&queue->single_mutex);
        if (queue->sp.start != queue->sp.end) {
            temp = simple_dequeue(&queue->sp);
            pthread_mutex_unlock(&queue->single_mutex);
            return temp;
        } else {
            pthread_cond_wait(&queue->single_condvar, &queue->single_mutex);
        }
   }
}

char* simple_dequeue (struct simple_queue* sp) {
    return *sp->start++;
}
