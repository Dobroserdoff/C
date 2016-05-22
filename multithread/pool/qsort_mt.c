#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "sync_queue.h"
#include "qsort.h"

#define NS 100
#define MS 5

void* quicksort(void *sqp, void* sp, int flag) {
    struct sync_queue_t* queue = sqp;
    struct params* local = sp;
    struct params *leftp, *rightp;

    if (local->size > 1) {
        leftp = malloc(sizeof(struct params));
        rightp = malloc(sizeof(struct params));
        partition(local, leftp, rightp);        

        if (((local->size) <= NS) || (flag == 1)) {
            if (leftp->size > 1) {
                quicksort(queue, leftp, 1);
            }
            free(leftp);
            
            if (rightp->size > 1) {
                quicksort(queue, rightp, 1);
            }    
            free(rightp);
            
        } else {
            pthread_mutex_lock(&finish_mutex); 
            counter++;
            pthread_mutex_unlock(&finish_mutex); 
            sync_queue_enqueue(queue, leftp);
        
            pthread_mutex_lock(&finish_mutex); 
            counter++;
            pthread_mutex_unlock(&finish_mutex); 
            sync_queue_enqueue(queue, rightp);
        }
    }
    
    if (flag == 0) {
        pthread_mutex_lock(&finish_mutex); 
        counter--;
        if (counter == 0) {
            pthread_cond_signal(&finish_condvar);
        }    

        pthread_mutex_unlock(&finish_mutex);    
    }
    
    return 0;
}

void partition(struct params* local, struct params* leftp, struct params* rightp) {
    int pivot, *l, *g, *start, *end, temp;
    
    pivot = *local->p;
    start = local->p;
    end = local->p + local->size;
    l = local->p;
    g = end;

    while (l != g) {
        while (l != end && *l <= pivot) {
            l++;
        }
            
        while (*(g - 1) > pivot) {
            g--;
        }
            
        if (l != g) {
            swap(l, g - 1);
        }
    }

    swap(start, l - 1);

    leftp->size = g - local->p - 1;
    leftp->p = local->p;

    rightp->size = end - g;
    rightp->p = g;
}

void swap(int* p, int *q) {
    int temp;

    temp = *q;
    *q = *p;
    *p = temp;
}
