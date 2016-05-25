#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ARSIZE 1000000
#define BUBBLE 1000

struct params {
    int *p;
    int size;
};
int ar[ARSIZE];

void* quicksort(void*);
void bubble(struct params*);
void swap(int* p, int *q);

int main() {
    int i;
    struct params* stp;
    long bms, ems;
    struct timeval begin, end;

    //puts("Unsorted array of integers:");
    for (i = 0; i < ARSIZE; i++) {
        ar[i] = rand() % 100;
       // printf("%d ", ar[i]);
    }
    //putchar('\n');

    stp = malloc(sizeof(struct params));
    stp->p = &ar[0];
    stp->size = ARSIZE;

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
    printf("ARSIZE: %d, BUBBLE: %d, TIME: %lds %ldms\n", ARSIZE, BUBBLE, (ems - bms) / 1000000, (ems - bms) % 1000000);

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
    struct params *leftp, *rightp;
    int pivot, *l, *g, *start, *end;

    pivot = *local->p;
    start = local->p;
    end = local->p + local->size;
    l = local->p;
    g = end;
        
    if ((BUBBLE != 0) && (local->size <= BUBBLE)) {
        bubble(sp);
    } else {
        leftp = malloc(sizeof(struct params));
        rightp = malloc(sizeof(struct params));

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

        if (leftp->size > 1) {
            quicksort(leftp);
            free(leftp);
        }

        if (rightp->size > 1) {
            quicksort(rightp);
            free(rightp);
        }
    }

    return 0;
}

void bubble(struct params* sp) {
    int i, length, *left, *right;

    left = sp->p;
    right = left + 1;
    length = sp->size;

    while (length > 1) {
        for (i = 1; i < length; i++) {
            if (*left > * right) {
                swap(left, right);
            }
            left++;
            right++;
        }
        left = sp->p;
        right = left + 1;
        length--;
    }
}

