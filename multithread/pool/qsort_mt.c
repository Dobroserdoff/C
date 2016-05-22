#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "sync_queue.h"
#include "qsort.h"

#define NS 1000
#define MS 10

void* quicksort(void *sqp, void* sp, int flag) {
    struct sync_queue_t* queue = sqp;
    const struct params* local = sp;
    struct params *leftp, *rightp;
    int pivot, *l, *g, *end, temp;

    if (local->size > 1) {
        pivot = *local->p;
        l = g = end = local->p;
        end += local->size;
        g = (end - 1);

        leftp = malloc(sizeof(struct params));
        rightp = malloc(sizeof(struct params));

        while (l != g) {
            while (*l <= pivot && l != end) {
                l++;
            }
            if (l == end) {
                l--;
            }

            while (*g > pivot && g != l) {
                g--;
            }
            
            if (l != g) {
                temp = *l;
                *l = *g;
                *g = temp;
            }
        }
        l--;
        *(local->p) = *l;
        *l = pivot;

        leftp->size = g - local->p;
        leftp->p = local->p;

        rightp->size = end - g;
        rightp->p = g;
    
        if (((local->size) <= NS) || (flag == 1)) {
            quicksort(queue, leftp, 1);
            quicksort(queue, rightp, 1);
            
            free(leftp);
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
