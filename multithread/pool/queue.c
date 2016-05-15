#include <stdlib.h>

#include "queue.h"

void queue_init(struct queue_t* sqp, size_t count) {
    int i;

    sqp->start = malloc(sizeof(char*) * (count)); 
    sqp->end = sqp->start;
}

int queue_empty(struct queue_t* sp) {
    return (sp->start == sp->end);
}

void queue_enqueue(struct queue_t* sp, char* value) {
    *sp->end++ = value;
}

char* queue_dequeue(struct queue_t* sp) {
    return *sp->start++;
}
