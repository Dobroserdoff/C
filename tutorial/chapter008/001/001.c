#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>

#define PERMS 0666

void error(char *, ...);

int main(int argc, char *argv[]){
    int f1, f2, n, i = 1;
    char buf[BUFSIZ];

    if (argc < 2)
        error("cat: no source file");

    if (argc > 2)
        if ((f2 = creat(argv[argc-1], PERMS)) == -1)
            error("cat: can't create %s, mode %03o", argv[argc-1], PERMS);
    
    if (argc == 2) {
        f2 = 1;
        argc = 3;
    }

    while (i < (argc - 1)) {
        if ((f1 = open(argv[i], O_RDONLY, 0)) == -1)
            error("cat: can't open %s", argv[i]);
        
        while ((n = read(f1, buf, BUFSIZ)) > 0) {
            if (write(f2, buf, n) != n)
                error("cat: write error on file %s", argv[argc-1]);
        }

        close(argv[i++]);
    }

    close(argv[argc-1]);

    return 0;
}

void error(char *fmt, ...){
    va_list args;
    
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}
