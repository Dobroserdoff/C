#include "functions.h"

char* path = { "./speedtest" }; 
int sr = 12;
char* arg = { "-s" };

int gettime(char**);

int main(int argc, char** argv) {
    struct params sp;
    int i, imin, imax;
    int average[sr], sum = 0;
    char** argums;
    char** startarg;

    startarg = malloc(100 * sizeof(void*));
    argums = startarg;
    *argums++ = path;

    for (i = 1; argv[i] != NULL; i++) {
        *argums++ = argv[i];
    }
    
    *argums++ = arg;

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
    
    printf("%d\t", sum / (imax - imin));
    free(startarg);
    return 0;
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
