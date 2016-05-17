#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "sync_queue.h"
#include "qsort.h"

void* quicksort(void* arg) {
    struct sync_queue_t* sqp = (void*)arg;
    struct params *local, left, right;
    int i, j, less, li = 0, *pivot, weight = 0;
    local = (struct params*) sqp->sp.start;
    pivot = local->p;
        
    if (local->size <= 1) {
        return 0;
    }

    else {
        for (i = 0; ar[i] != *pivot; i++, weight++)
            ;
        while (i < (local->size + weight)) {
            if (ar[i] < *pivot) {
                less = ar[i];
                for (j = i; j > weight; j--) {
                    ar[j] = ar[j - 1];
                }
                *local->p = less;
                *pivot++;
                li++;
            }
            i++;
        }

        if (li == 0) {
            li++;
        }

        left.size = li;
        left.p = local->p;

        right.size = local->size - li;
        right.p = local->p;
        for (i = 0; i < li; i++) {
            *right.p++;
        }
        
        sync_queue_enqueue(sqp, &left);

        sync_queue_enqueue(sqp, &right);
    }
    return 0;
}
