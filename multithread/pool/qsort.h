#define ARSIZE 200000

extern pthread_mutex_t finish_mutex;
extern pthread_cond_t finish_condvar;

struct params {
    int *p;
    int size;
};
int ar[ARSIZE];

void* quicksort(void*, void*, int);
void partition(struct params*, struct params*, struct params*);
void bubble(struct params*);
void swap(int*, int*);
