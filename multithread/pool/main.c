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
    char* sep1 = { "===================================================" };
    char* sep2 = { "---------------------------------------------------" };
    char** argums;
    char** startarg;

    startarg = malloc(100 * sizeof(void*));
    argums = startarg;
    *argums++ = path;
    *argums++ = arg1;
    
    puts(" POOL    ARSIZE RECURSION    BUBBLE            TIME");
    puts(sep1);

    for (i = 0; i < (sizeof(par) / sizeof(int)); i++) {
        itoa(par[i], argums++);
        *argums++ = arg2;
        
        for (j = 0; j < (sizeof(asr) / sizeof(int)); j++) {
            itoa(asr[j], argums++);
            *argums++ = arg3;
            
            for (k = 0; k < (sizeof(rr) / sizeof(int)); k++) {
                itoa(rr[k], argums++);
                *argums++ = arg4;
                
                for (l = 0; l <= k; l++) {
                    itoa(br[l], argums++) ;
                    *argums-- = NULL;
                    
                    printf("%5d%10d%10d%10d", par[i], asr[j], rr[k], br[l]);
                        
                    gettime(startarg);
                    free(*argums);
                }
                argums -= 2;
                free(*argums);
            }
            if (j != (sizeof(asr) / 4) - 1) {
                puts(sep2);
            }

            argums -= 2;
            free(*argums);
        }   
        argums -= 2;
        free(*argums);
        puts(sep1);  
    }
    free(startarg);
        
    return 0;
}

void gettime(char* const* arg) {
    int err;
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
    
    printf("\t%lds %ldms\n", (ems - bms) / 1000000, (ems - bms) % 1000000);

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
