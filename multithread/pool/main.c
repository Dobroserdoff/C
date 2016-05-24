#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int par[3] = { 1, 2, 4 };
int asr[3] = { 100000, 500000, 1000000 };
int rr[3] = { 0, 100, 1000 };
int br[3] = { 0, 10, 100 };
char buf[120];
char* path = { "./pool" };
char* arg1 = { " -p " };
char* arg2 = { " -a " };
char* arg3 = { " -r " };
char* arg4 = { " -b " };

void gettime(char* const*);
void itoa(int, char*);

int main() {
    int i, j, k, l;
    int sec, msec;
    pid_t pid;
    char* sep1 = { "========================================" };
    char* sep2 = { "----------------------------------------" };
    char** argums;
    char** startarg;
    
    startarg = malloc(sizeof(void*) * 10);
    
    for (i = 0; i < (sizeof(par) / 4); i++) {
        argums = startarg;
        *argums++ = path;
        *argums++ = arg1;
        itoa(par[i], *argums++);
       
        for (j = 0; j < (sizeof(asr) / 4); j++) {
            *argums++ = arg2;
            itoa(asr[j], *argums++);
            
            for (k = 0; k < (sizeof(rr) / 4); k++) {
                *argums++ = arg3;
                itoa(rr[k], *argums++);

                for (l = 0; l <= k; l++) {
                    *argums++ = arg4;
                    itoa(br[l], *argums++) ;
                    
                    gettime(startarg);
                }

                if (j != (sizeof(asr) / 4) - 1) {
                    puts(sep2);
                }
            }

            puts(sep1);  
        }

        free(startarg);
        return 0;
    }
}

void gettime(char* const* arg) {
    pid_t pid;
    struct timeval begin, end;
    
    pid = fork();
    if (pid == 0) {
        if (gettimeofday(&begin, 0) == 0) {
            printf("BSEC - %d, BMSEC - %d/n", (int) begin.tv_sec, (int) begin.tv_usec);
        }

        execv(path, arg);
    
        if (gettimeofday(&end, 0) == 0) {
            printf("ESEC - %d, EMSEC - %d/n", (int) end.tv_sec, (int) end.tv_usec);
        }

    }

    if (pid > 0) {
        waitpid(pid, NULL, 0);
    }
    
    //printf("%10d%10d%10d%10d%10ld\n", p, a, r, b);

}

void itoa(int n, char* buf) {
    int c, j, i, sign;
    char *s;
    s = buf;

    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    }
    while ((n /= 10) > 0);
        
    if (sign < 0)
        *s++ = '-';
    
    *s = '\0';
    
    for (i = 0, j = strlen(buf)-1; i < j; i++, j--) {
        c = buf[i];
        buf[i] = buf[j];
        buf[j] = c;
    }
}
