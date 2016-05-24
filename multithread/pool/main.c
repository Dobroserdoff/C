#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

int par[3] = { 1, 2, 4 };
int asr[3] = { 100000, 500000, 1000000 };
int rr[3] = { 0, 100, 1000 };
int br[3] = { 0, 10, 100 };
char* path = { "./pool" };
char* arg1 = { "-p" };
char* arg2 = { "-a" };
char* arg3 = { "-r" };
char* arg4 = { "-b" };

void gettime(char* const*);
void itoa(int, char**);

int main() {
    int i, j, k, l;
    int sec, msec;
    pid_t pid;
    char* sep1 = { "========================================" };
    char* sep2 = { "----------------------------------------" };
    char** argums;
    char** startarg;

    startarg = malloc(100 * sizeof(void*));
    argums = startarg;
    *argums++ = path;
    *argums++ = arg1;
    
    for (i = 0; i < (sizeof(par) / sizeof(int)); i++) {
        printf("i - %d, ", i);
        itoa(par[i], argums++);
        *argums++ = arg2;
        
        for (j = 0; j < (sizeof(asr) / sizeof(int)); j++) {
            printf("j - %d, ", j);
            itoa(asr[j], argums++);
            *argums++ = arg3;
            
            for (k = 0; k < (sizeof(rr) / sizeof(int)); k++) {
                printf("k - %d, ", k);
                itoa(rr[k], argums++);
                *argums++ = arg4;
                
                for (l = 0; l <= k; l++) {
                    printf("l - %d\n", l);
                    itoa(br[l], argums++) ;
                    *argums-- = NULL;

                    gettime(startarg);
                    free(*argums);
                }
                argums -= 2;
                free(*argums);
                if (j != (sizeof(asr) / 4) - 1) {
                    //puts(sep2);
                }
            }
            argums -= 2;
            free(*argums);
            //puts(sep1);  
        }   
        argums -= 2;
        free(*argums);
    }
    free(startarg);
        
    return 0;
}

void gettime(char* const* arg) {
    int err;
    pid_t pid;
    struct timeval begin, end;
    
    if (gettimeofday(&begin, 0) == 0) {
        //printf("BSEC - %d, BMSEC - %d\n", (int) begin.tv_sec, (int) begin.tv_usec);
    }

    pid = fork();
    if (pid == 0) {    
        execv(path, arg);
        puts(strerror(errno));
    }

    if (pid > 0) {
        waitpid(pid, NULL, 0);
        if (gettimeofday(&end, 0) == 0) {
            //printf("ESEC - %d, EMSEC - %d\n", (int) end.tv_sec, (int) end.tv_usec);
        }
    }
    
    //printf("Seconds - %ld, microseconds - %ld\n", end.tv_sec - begin.tv_sec, end.tv_usec - begin.tv_usec);

}

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
