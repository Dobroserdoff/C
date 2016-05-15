struct queue_t {
    char** start;
    char** end; 
};

void queue_init(struct queue_t*, size_t count);
int queue_empty(struct queue_t*);
void queue_enqueue(struct queue_t*, char*);
char* queue_dequeue(struct queue_t*);
