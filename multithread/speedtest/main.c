#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

int asr[5] = { 20000, 40000, 60000, 80000, 100000 };
int br[18] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 16, 19, 22, 25, 28, 31 };
char* path = { "./speedtest" };
char* arg1 = { "-s" };
char* arg2 = { "-a" };
char* arg3 = { "-b" };

long gettime(char* const*);
void itoa(int, char**);

int main() {
    int i, j, x = 0, sr = 10;
    long time;
    char** argums;
    char** startarg;
    int sum = (sizeof(asr)/sizeof(int))*(sizeof(br)/sizeof(int));
    long average[sum];

    for (i = 0; i < sum; i++) {
        average[i] = 0;
    }

    startarg = malloc(100 * sizeof(void*));
    argums = startarg;
    *argums++ = path;
    *argums++ = arg1;
    
    putchar('\t');
    for (i = 0; i < (sizeof(br) / sizeof(int)); i++) {
        printf("%d\t", br[i]);
    }
    putchar('\n');

    while (sr-- > 0) {
        itoa(sr, argums++);
        *argums++ = arg2;

        for (i = 0; i < (sizeof(asr) / sizeof(int)); i++) {
            itoa(asr[i], argums++);
            *argums++ = arg3;
        
            for (j = 0; j < (sizeof(br) / sizeof(int)); j++) {
                itoa(br[j], argums++);
                *argums-- = NULL;
                    
                time = gettime(startarg);
                average[x] = (average[x] + time) / 2;
                x++; 
                free(*argums);
            }
            argums -= 2;
            free(*argums);
        }
        argums -= 2;
        free(*argums);
        x = 0;
    }   
    free(startarg);
    
    for (i = 0; i < (sizeof(asr) / sizeof(int)); i++) {
        printf("%d\t", asr[i]);
        for (j = 0; j < (sizeof(br) / sizeof(int)); j++) {
            printf("%ld\t", average[j + ((sizeof(br) / sizeof(int))*i)]);
            fflush(stdout);
        }
        putchar('\n');
    } 
    
    return 0;
}

long gettime(char* const* arg) {
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
    return (ems - bms);
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
