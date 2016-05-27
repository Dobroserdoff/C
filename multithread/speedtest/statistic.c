#include "functions.h"

char* path = { "./speedtest" }; 
int sr = 12;
int tsr = 5;
char* arg = { "-s" };

int dozen(char**, char**);
int gettime(char**);

int main(int argc, char** argv) {
    struct params sp;
    int i, medium, sum = 0;
    int dozres[tsr];
    float deviation;
    char** argums;
    char** startarg;

    startarg = malloc(100 * sizeof(void*));
    argums = startarg;
    *argums++ = path;

    for (i = 1; argv[i] != NULL; i++) {
        *argums++ = argv[i];
    }
    
    *argums++ = arg;

    for (i = 0; i < tsr; i++) {
        dozres[i] = dozen(startarg, argums);
        sum += dozres[i];
        printf("%d\n", dozres[i]);
    }
    medium = sum / tsr;

    sp.p = &dozres[0];
    sp.size = tsr;
    quicksort(&sp, 0);

    deviation = 100 * ((dozres[tsr - 1] - medium) / medium);
    printf("%d(%f)\t", medium, deviation);
    free(startarg);
    return 0;
}

int dozen(char** startarg, char** argums) {
    struct params sp;
    int i, imin, imax;
    int average[sr], sum = 0;

    imin = sr / 3;
    imax = (sr / 3) * 2;

    for (i = 0; i < sr; i++) {
        itoa(i, argums++);
        *argums-- = NULL;
        
        average[i] = gettime(startarg);
        free(*argums);
    }
    
    sp.p = &average[0];
    sp.size = sr;
    quicksort(&sp, 0);
    
    for (i = 0; i < sr; i++) {
        if ((i >= imin) && (i < imax)) {
            sum += average[i];
        }
    }
    return (sum / (imax - imin));
}

int gettime(char** arg) {
    pid_t pid;
    long bms, ems;
    struct timeval begin, end;
    
    gettimeofday(&begin, 0);
    bms = begin.tv_sec * 1000000 + begin.tv_usec;

    pid = fork();
    if (pid == 0) {    
        execv(path, arg);
        puts(strerror(errno));
    }

    if (pid > 0) {
        waitpid(pid, NULL, 0);
        gettimeofday(&end, 0);
        ems = end.tv_sec * 1000000 + end.tv_usec;
    }
    return (int)(ems - bms);
}
