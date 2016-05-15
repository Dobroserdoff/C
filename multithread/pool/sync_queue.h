#include "queue.h"

struct sync_queue_t {
    pthread_mutex_t single_mutex;
    pthread_cond_t single_condvar;
    struct queue_t sp;
};

void sync_queue_init(struct sync_queue_t*, size_t count);
void sync_queue_enqueue(struct sync_queue_t*, char*);
char* sync_queue_dequeue(struct sync_queue_t*);
