#include "functions.h"

int asr[5] = { 20000, 40000, 60000, 80000, 100000 };
int br[18] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 16, 19, 22, 25, 28, 31 };
char* path = { "./stat" };
char* arg1 = { "-a" };
char* arg2 = { "-b" };

int main() {
    int i, j;
    pid_t pid;
    long time;
    char** argums;
    char** startarg;

    startarg = malloc(100 * sizeof(void*));
    argums = startarg;
    *argums++ = path;
    *argums++ = arg1;
    
    putchar('\t');
    for (i = 0; i < (sizeof(br) / sizeof(int)); i++) {
        printf("%d\t", br[i]);
    }
    putchar('\n');

    for (i = 0; i < (sizeof(asr) / sizeof(int)); i++) {
        printf("%d\t", asr[i]);
        fflush(stdout);
        itoa(asr[i], argums++);
        *argums++ = arg2;
        
        for (j = 0; j < (sizeof(br) / sizeof(int)); j++) {
            itoa(br[j], argums++);
            *argums-- = NULL;
                    
            pid = fork();
            if (pid == 0) {
                execv(path, startarg);
                puts(strerror(errno));
            }

            if (pid > 0) {
                waitpid(pid, NULL, 0);
            }
        }
        free(*argums);
        putchar('\n');
        argums -= 2;
    }
    free(*argums);
    free(startarg);
    return 0;
}
