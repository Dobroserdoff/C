#include <stdio.h>
#include <stdlib.h>

#define LENGTH 4

void indent(void);

int main(int argc, char *argv[]) {
    int c, i = 0, k = 1, l = 1;

    while((c = getchar()) != EOF) {
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
