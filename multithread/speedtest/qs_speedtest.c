#include "functions.h"

int main(int argc, char** argv) {
    int i;
    int arsize, sr, bub = 0;
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

    quicksort(stp, bub);

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
