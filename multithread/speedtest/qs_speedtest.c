#include "functions.h"

int main(int argc, char** argv) {
    int i, fdfrom, fdto;
    int time, arsize, sr, bub = 0;
    struct params* stp;
    long bms, ems;
    struct timeval begin, end;
    
    if (argc > 1) {
        for (i = 0; i < argc; i++) {
            if (argv[i][1] == 'l') {
                fdfrom = atoi(argv[i + 1]);
            } else if (argv[i][1] == 'r') {
                fdto = atoi(argv[i + 1]);
            }
        }
    }
    
    if (read(fdfrom, &arsize, sizeof(int)) == -1) {
        puts(strerror(errno));
    }
    
    if (read(fdfrom, &bub, sizeof(int)) == -1) {
        puts(strerror(errno));
    }
    
    if (read(fdfrom, &sr, sizeof(int)) == -1) {
        puts(strerror(errno));
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
    time = (int) ems - bms;

    /*puts("Sorted array of integers");
    for (i = 0; i < ARSIZE; i++) {
        printf("%d ", ar[i]);
    }
    putchar('\n');*/
    //printf("ARSIZE: %d, BUBBLE: %d, TIME: %ldms\n", arsize, bub, ems - bms);
    
    write(fdto, &time, sizeof(int));
    free(stp);

    return 0;
}
