#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct params {
    int *p;
    int size;
};
int arsize, sr, bub = 0;

void* quicksort(void*);
void bubble(struct params*);
void swap(int* p, int *q);

int main(int argc, char** argv) {
    int i;
    struct params* stp;
    long bms, ems;
    struct timeval begin, end;

    if (argc > 1) {
        for (i = 2; i < argc; i++) {
            if (argv[i - 1][1] == 'a') {
                arsize = atoi(argv[i]);
            } else if (argv[i - 1][1] == 'b'){
                bub = atoi(argv[i]);
            } else if (argv[i - 1][1] == 's'){
                sr = atoi(argv[i]);
            }

        }
    }
    int ar[arsize];

    srand(sr);
    
    //puts("Unsorted array of integers:");
    for (i = 0; i < arsize; i++) {
        ar[i] = rand() % 100;
       // printf("%d ", ar[i]);
    }
    //putchar('\n');

    stp = malloc(sizeof(struct params));
    stp->p = &ar[0];
    stp->size = arsize;

    gettimeofday(&begin, 0);
    bms = begin.tv_sec * 1000000 + begin.tv_usec;

    quicksort(stp);

    gettimeofday(&end, 0);
    ems = end.tv_sec * 1000000 + end.tv_usec;
    
    /*puts("Sorted array of integers");
    for (i = 0; i < ARSIZE; i++) {
        printf("%d ", ar[i]);
    }
    putchar('\n');*/
    //printf("ARSIZE: %d, BUBBLE: %d, TIME: %ldms\n", arsize, bub, ems - bms);

    free(stp);

    return 0;
}

void swap(int* p, int *q) {
    int temp;

    temp = *q;
    *q = *p;
    *p = temp;
}

void* quicksort(void* sp) {
    const struct params* local = sp;
    struct params leftp, rightp;
    int pivot, *l, *g, *start, *end;

    pivot = *local->p;
    start = local->p;
    end = local->p + local->size;
    l = local->p;
    g = end;
        
    if (local->size <= bub) {
        bubble(sp);
    } else {
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

        leftp.size = g - local->p - 1;
        leftp.p = local->p;

        rightp.size = end - g;
        rightp.p = g;

        if (leftp.size > 1) {
            quicksort(&leftp);
        }

        if (rightp.size > 1) {
            quicksort(&rightp);
        }
    }

    return 0;
}

void bubble(struct params* sp) {
    int* end = sp->p + sp->size - 1;
    int found = 1;

    for (int* start = sp->p; start + 1 < end; ++start) {
        int* min_ptr = start;
        int min = *start;
        for (int* ptr = min_ptr + 1; ptr < end; ++ptr) {
            if (*ptr < min) {
                min = *ptr;
                min_ptr = ptr;
            }
        }

        if (min_ptr != start) {
            swap(min_ptr, start);
        }
    }

    /*while (found) {
        found = 0;
        for (int* ptr = sp->p; ptr < end; ++ptr) {
            if (*ptr > *(ptr + 1)) {
                swap(ptr, ptr + 1);
                found = 1;
            }
        }
        --end;
    }*/
}

