#include <stdlib.h>
#include "queue.h"

void queue_init(struct queue_t* sp, size_t count) {
    sp->start = malloc(sizeof(void*) * (count)); 
    sp->end = sp->start;
    sp->first = sp->start;
}

int queue_empty(struct queue_t* sp) {
    return (sp->start == sp->end);
}

void queue_collapse(struct queue_t* sp) {
    
    do {
        void* ptr = *--sp->start;
        if (ptr != 0) {
            free(ptr);
        }
    } while (sp->start != sp->first);
    free(sp->start);
}

void queue_enqueue(struct queue_t* sp, void* value) {
    *sp->end++ = value;
}

void* queue_dequeue(struct queue_t* sp) {
    return *sp->start++;
}
