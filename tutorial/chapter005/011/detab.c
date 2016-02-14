#include <stdio.h>
#include <stdlib.h>

#define LENGTH 4

void indent(void);

int main(int argc, char *argv[]) {
    int c, i = 0, k;
    int clm = 0, start = 0;

    for (k = 1; k < argc; k++)
        if (*argv[k]++ == '+')
            clm = atoi(argv[k]);

    for (k = 1; k < argc; k++)
        if (*--argv[k] == '-') {
            start = atoi(++argv[k]);
        }
    k = 1;

    while((c = getchar()) != EOF) {
        if (clm) {
            if (i++ == (start * clm)) {
                indent();
                start++;
            }    
        }
        else 
            if (k < argc && i++ == (atoi(argv[k]))) {
                indent();
                k++;
            }

        if (c == '\t')
            indent();
        else
            putchar(c);
   }
}

void indent(void) {
    for (int j = 0; j<LENGTH; ++j)
        putchar(' ');
}
