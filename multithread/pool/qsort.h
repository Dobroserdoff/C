#define ARSIZE 10

pthread_mutex_t finish_mutex;
pthread_cond_t finish_condvar;

struct params {
    int *p;
    int size;
};
int ar[ARSIZE];

void* quicksort(void*, void*);
