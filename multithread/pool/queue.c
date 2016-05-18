#include <stdlib.h>
#include "queue.h"

void queue_init(struct queue_t* sqp, size_t count) {
    sqp->start = malloc(sizeof(void*) * (count)); 
    sqp->end = sqp->start;
}

int queue_empty(struct queue_t* sp) {
    return (sp->start == sp->end);
}

void queue_enqueue(struct queue_t* sp, void* value) {
    *sp->end++ = value;
}

void* queue_dequeue(struct queue_t* sp) {
    return *sp->start++;
}
