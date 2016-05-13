#include <stdio.h>
#include <pthread.h>

#define ARSIZE 20

struct params {
    int *p;
    int size;
};
int ar[ARSIZE];

int quicksort(struct params);

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
    quicksort(st);

    for (i = 0; i < ARSIZE; i++) {
        printf("%d ", ar[i]);
    }
    putchar('\n');

    return 0;
}

int quicksort(struct params st) {
    struct params local, left, right;
    int i, j, less, li = 0, *pivot, weight = 0;
    //pthread_t threads[ARSIZE];
    pivot = st.p;

    if (st.size <= 1) {
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
        for (i = 0; ar[i] != *pivot; i++, weight++);
            ;
        while (i < (st.size + weight)) {
            if (ar[i] < *pivot) {
                less = ar[i];
                for (j = i; j > weight; j--) {
                    ar[j] = ar[j - 1];
                }
                *st.p = less;
                *pivot++;
                li++;
            }
            i++;
        }

        if (li == 0) {
            li++;
        }

        left.size = li;
        left.p = st.p;

        right.size = st.size - li;
        right.p = st.p;
        for (i = 0; i < li; i++) {
            *right.p++;
        }

        quicksort(left);
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
