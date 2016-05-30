#include "functions.h"

char* path = { "./speedtest" }; 
int sr = 12;
int tsr = 5;
int flag = 0;
char* arg = { "-d" };
int fd, size, bub;

int dozen(char**);

int main(int argc, char** argv) {
    struct params sp;
    int i, medium, sum = 0;
    int dozres[tsr];
    float deviation;
    char** argums, **str;
    char** startarg;

    startarg = malloc(100 * sizeof(void*));
    argums = startarg;
    *argums++ = path;
    *argums++ = arg;
    
    str = argv;
    while (*str != NULL){
        printf("%s ", *str++);
    }
    putchar('\n');

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
    itoa(fd, argums++);
    *argums-- = NULL;

    for (i = 0; i < tsr; i++) {
        dozres[i] = dozen(startarg);
        sum += dozres[i];
    }
    medium = sum / tsr;

    sp.p = &dozres[0];
    sp.size = tsr;
    quicksort(&sp, 0);
    
    deviation = 100 * ((float)(dozres[tsr - 1] - medium) / medium);
    printf("%d %f\n", medium, deviation);
    write(fd, &medium, sizeof(int));
    write(fd, &deviation, sizeof(float));
    
    close(fd);
    free(startarg);
    return 0;
}

int dozen(char** startarg) {
    struct params sp;
    pid_t pid;
    int i, imin, imax, pipeto[2], pipefrom[2], fd2;
    int average[sr], sum = 0;
    char** string;
    
    string = startarg;
    while (*string != NULL){
        printf("%s ", *string++);
    }
    putchar('\n');
    fd2 = (fd + 1);
    
    for (i = 0; i < sr; i++) {
        pipe(pipeto);
        pipe(pipefrom);
        close(pipefrom[1]);
    
        pid = fork();       
        if (pid == 0) {    
            close(pipeto[0]);
            
            write(fd, &size, sizeof(int));
            write(fd, &bub, sizeof(int));
            write(fd, &i, sizeof(int));
            
            execv(path, startarg);
            puts(strerror(errno));
        }

        if (pid > 0) {
            if (read(pipefrom[0], &average[i], sizeof(int)) == -1) {
                puts(strerror(errno));
            }    
            waitpid(pid, NULL, 0);
        }
        close(fd2);

    }
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


