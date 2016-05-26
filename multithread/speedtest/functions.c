#include "functions.h"

void itoa(int n, char** buf) {
    int c, j, i, sign;
    char *s;

    s = (char*)malloc(11*(sizeof(char)));
    *buf = s;

    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    }
    while ((n /= 10) > 0);
        
    *s = '\0';
    s = *buf;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void swap(int* p, int *q) {
    int temp;

    temp = *q;
    *q = *p;
    *p = temp;
}

void* quicksort(void* sp, int bub) {
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
            quicksort(&leftp, bub);
        }

        if (rightp.size > 1) {
            quicksort(&rightp, bub);
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
