#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "sync_queue.h"
#include "qsort.h"

pthread_mutex_t finish_mutex;
pthread_cond_t finish_condvar;
int pool = 1;
int arsize = 10000;
void* single (void*);
int rs = 0;
int bs = 0;
 
int main (int argc, char** argv) {
    int i, sum1, sum2;
    struct sync_queue_t queue;
    struct params *stp;
    counter = 0;
    
    if (argc > 1) {
        for (i = 2; i < argc; i++) {
            if (argv[i - 1][1] == 'p') {
                pool = atoi(argv[i]);
            } else if (argv[i - 1][1] == 'a') {
                arsize = atoi(argv[i]);
            } else if (argv[i - 1][1] == 'r') {
                rs = atoi(argv[i]);
            } else if (argv[i -1][1] == 'b'){
                bs = atoi(argv[i]);
            }
        }
    }
  
    pthread_t mythreads[pool];
    int ar[arsize];

    //printf("POOL - %d, ARSIZE - %d, RECURSION - %d, BUBBLE - %d\n", pool, arsize, rs, bs);
    //puts("Unsorted array of integers:");
    for (i = 0; i < arsize; i++) {
        ar[i] = rand() % 100;
        //printf("%d ", ar[i]);
    }
    //putchar('\n');

    sum1 = ar[0];
    for (i = 1; i < arsize; i++) {
        sum1 += ar[i];
    }

    stp = malloc(sizeof(struct params));
    stp->p = &ar[0];
    stp->size = arsize;

    sync_queue_init(&queue, 10*(arsize + pool));   
    
    for (i = 0; i < pool; i++) {
        pthread_create(&mythreads[i], 0, single, &queue);
    }   
   
    pthread_mutex_lock(&finish_mutex);
    counter++;
    pthread_mutex_unlock(&finish_mutex);
    sync_queue_enqueue(&queue, stp);
    
    pthread_mutex_lock(&finish_mutex);
    if (counter != 0) {
        pthread_cond_wait(&finish_condvar, &finish_mutex);
    }
    pthread_mutex_unlock(&finish_mutex);

    for (i = 0; i < pool; i++) {
        sync_queue_enqueue(&queue, 0);
    }
    
    for (i = 0; i < pool; i++) {
        pthread_join(mythreads[i], 0);
    }

    queue_collapse(&queue.sp);
    
    sum2 = ar[0];
    for (i = 1; i < arsize; i++) {
        sum2 += ar[i];
    }

    for (i = 1; i < arsize; i++) {
        if ((ar[i] < ar[i - 1]) || (sum1 != sum2)) {
        }
    }
    /*
    puts("\nSorted array of integers:");
    for (i = 0; i < arsize; i++) {
        printf("%d ", ar[i]);
    }
    putchar('\n');
    */
    return 0;
}

void* single (void* param) {
    while (1) {
        struct params* temp = sync_queue_dequeue(param);
        if (!temp) {
            break;
        }
        quicksort(param, temp, 0); 
    }
    return 0;
}
