#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

struct params {
    int *p;
    int size;
};

void itoa(int, char**);
void* quicksort(void*, int);
void bubble(struct params*);
void swap(int* p, int *q);
