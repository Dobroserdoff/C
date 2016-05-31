#include "functions.h"

char* path = { "./speedtest" }; 
int sr = 12;
int tsr = 5;
int flag = 0;
char* arg1 = { "-l" };
char* arg2 = { "-r" };
int fd, size, bub;

int dozen(char**);

int main(int argc, char** argv) {
    struct params sp;
    int i, medium, sum = 0;
    int dozres[tsr];
    float deviation;
    char** startarg;

    startarg = malloc(100 * sizeof(void*));
    *startarg = path;
    
    for (i = 1; argv[i] != NULL; i++) {
        if (argv[i][1] == 'f') {
            flag = atoi(argv[i + 1]);
        } else if (argv[i][1] == 'd') {
            fd = atoi(argv[i + 1]);
        } else if (argv[i][1] == 'a') {
            size = atoi(argv[i + 1]);
        } else if (argv[i][1] == 'b') {
            bub = atoi(argv[i + 1]);
        }
    }

    for (i = 0; i < tsr; i++) {
        dozres[i] = dozen(startarg);
        sum += dozres[i];
    }
    medium = sum / tsr;

    sp.p = &dozres[0];
    sp.size = tsr;
    quicksort(&sp, 0);
    
    deviation = 100 * ((float)(dozres[tsr - 1] - medium) / medium);
    //printf("%d(%f)\n", medium, deviation);
    write(fd, &medium, sizeof(int));
    write(fd, &deviation, sizeof(float));
    
    free(startarg);
    return 0;
}

int dozen(char** startarg) {
    struct params sp;
    pid_t pid;
    int i, imin, imax, pipeto[2], pipefrom[2];
    int average[sr], sum = 0;
    char** argums;

    argums = startarg;
    argums++;

    pipe(pipeto);
    *argums++ = arg1;
    itoa(pipeto[0], argums++);

    pipe(pipefrom);
    *argums++ = arg2;
    itoa(pipefrom[1], argums++);
    *argums-- = NULL;

    for (i = 0; i < sr; i++) {
        pid = fork();       
        
        if (pid == 0) {    
            write(pipeto[1], &size, sizeof(int));
            write(pipeto[1], &bub, sizeof(int));
            write(pipeto[1], &i, sizeof(int));
            
            execv(path, startarg);
            puts(strerror(errno));
        }

        if (pid > 0) {
            waitpid(pid, NULL, 0);
            
            if (read(pipefrom[0], &average[i], sizeof(int)) == -1) {
                puts(strerror(errno));
            }    
        }

    }
    close(pipeto[0]);
    close(pipeto[1]);
    close(pipeto[0]);
    close(pipeto[1]);

    sp.p = &average[0];
    sp.size = sr;
    quicksort(&sp, 0);
    
    if (flag == 0) {
        imin = sr / 3;
        imax = (sr / 3) * 2;
    } else if (flag == 1) {
        imin = 0;
        imax = sr / 2;
    } else {
        imin = 0;
        imax = 1;
    }
    
    for (i = imin; i < imax; i++) {
        sum += average[i];
    }
    return (sum / (imax - imin));
}
