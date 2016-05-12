#include <stdio.h>
#include <pthread.h>

#define ARSIZE 20

struct params{
    int *p;
    int size;
};
int buffer[ARSIZE], *buf;

int quicksort (struct params);
void* threadsort(void* local);

int main() {
    int i, *k, ar[ARSIZE];
    struct params st;
    buf = &buffer[0];

    puts("Unsorted array of integers:");
    for (i = 0; i < ARSIZE; i++) {
        ar[i] = rand() % 100;
        printf("%d ", ar[i]);
    }

    st.p = &ar[0]; 
    st.size = ARSIZE;
    
    puts("\nQuicksorted array of integers:");
    quicksort(st);
    
    for (i = 0; i < ARSIZE; i++) {
        printf("%d ", buffer[i]);
    }
    
    putchar('\n');

    return 0;
}

int quicksort(struct params st) {
    struct params local, left, right;
    int i, *pivot, *l, *r, li = 0, ri = 0, *res, lefty[ARSIZE], righty[ARSIZE], equal, ei = 0;
    l = left.p = &lefty[0];
    r = right.p = &righty[0];
    pivot = st.p;
    res = &buffer[0];
    //pthread_t threads[ARSIZE];

    if (st.size <= 1) {
        if (st.size == 1) {
            *buf++ = *st.p;
        }
        return 0;
    }
    /*
    else {
        for (i = 0; i <= ARSIZE/st.size; i++) {
            ((i % 2) == 0) ? (local.p = st.p) : (local.p = &st.p[ARSIZE/2]);
            local.size = ARSIZE/2;
            pthread_create(&threads[i], 0, threadsort, (void *)local);
        }
    }*/

    else {
        for (i = 0; i < st.size; i++) {
            if (*st.p < *pivot) {
                (*l++ = *st.p, li++);
            } else if (*st.p > *pivot) {
                (*r++ = *st.p, ri++);
            } else {
                equal = *st.p;
                ei++;
            }
            *st.p++;
        }
    left.size = li;
    right.size = ri;
    quicksort(left);
    while (ei-- > 0) {
        *buf++ = equal;
    }
    quicksort(right);
    }
}
/*
void* threadsort(void* local) {
    int i;
    struct params *stp;

    puts("\nThreadsort:");
    
    for (i = 0; i < stp.size; i++) {
        printf("%d ", *stp.p++);
    }

    return 0;
}*/
