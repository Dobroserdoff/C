#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "sync_queue.h"
#include "qsort.h"

void* quicksort(void *sqp, void* sp) {
    struct sync_queue_t* queue = sqp;
    struct params *local = sp, temp, *leftp, *rightp;
    int i, j, less, li = 0, *pivot, weight = 0;
    pivot = local->p;

   if (local->size <= 1) {
        pthread_mutex_lock(&finish_mutex); 
        counter--;
        
        if (counter == 0) {
            pthread_cond_signal(&finish_condvar);
        }    

        pthread_mutex_unlock(&finish_mutex);    
        return 0;

    } else {
        leftp = (struct params*) malloc(sizeof(temp));
        rightp = (struct params*) malloc(sizeof(temp));
         
        for (i = 0; ar[i] != *pivot; i++, weight++)
            ;
        while (i < (local->size + weight)) {
            if (ar[i] < *pivot) {
                less = ar[i];
                for (j = i; j > weight; j--) {
                    ar[j] = ar[j - 1];
                }
                *local->p = less;
                pivot++;
                li++;
            }
            i++;
        }

        if (li == 0) {
            li++;
        }

        leftp->size = li;
        leftp->p = local->p;

        rightp->size = local->size - li;
        rightp->p = local->p;
        for (i = 0; i < li; i++) {
            rightp->p++;
        }
        
        pthread_mutex_lock(&finish_mutex); 
        counter++;
        pthread_mutex_unlock(&finish_mutex); 
        sync_queue_enqueue(queue, leftp);
        
        pthread_mutex_lock(&finish_mutex); 
        counter++;
        pthread_mutex_unlock(&finish_mutex); 
        sync_queue_enqueue(queue, rightp);
    }

    pthread_mutex_lock(&finish_mutex); 
    counter--;
    pthread_mutex_unlock(&finish_mutex); 
    
    return 0;
}
