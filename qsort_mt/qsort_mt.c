#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define ARSIZE 1000

struct params {
    int *p;
    int size;
};
int ar[ARSIZE];

void* quicksort(void*);

int main() {
    int i;
    struct params st;

    puts("Unsorted array of integers:");
    for (i = 0; i < ARSIZE; i++) {
        ar[i] = rand() % 100;
        printf("%d ", ar[i]);
    }

    st.p = &ar[0];
    st.size = ARSIZE;

    puts("\nQuicksorted array of integers:");
    quicksort(&st);

    for (i = 0; i < ARSIZE; i++) {
        printf("%d ", ar[i]);
    }
    putchar('\n');

    return 0;
}

void* quicksort(void* arg) {
    struct params *local, left, right;
    int i, j, less, li = 0, *pivot, weight = 0;
    local = arg;
    pivot = local->p;
    pthread_t left_t, right_t;
        
    if (local->size <= 1) {
        return 0;
    }

    else {
        for (i = 0; ar[i] != *pivot; i++, weight++);
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
        
        if (left.size > 1) {
            if (j = pthread_create(&left_t, 0, quicksort, (void*)(&left)) != 0) {
                puts((const char*)strerror(j));
            }
                
        }
        if (right.size > 1) {
            if (j = pthread_create(&right_t, 0, quicksort, (void*)(&right)) != 0) {
                puts((const char*)strerror(j));
            }
        }
        
        if (left.size > 1) {
            pthread_join(left_t, 0);
        }
        if (right.size > 1) {
            pthread_join(right_t, 0);
        }
   }
}
