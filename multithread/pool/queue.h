struct queue_t {
    void** first;
    void** start;
    void** end; 
};

void queue_init(struct queue_t*, size_t count);
int queue_empty(struct queue_t*);
void queue_collapse(struct queue_t*);
void queue_enqueue(struct queue_t*, void*);
void* queue_dequeue(struct queue_t*);
