#include <stdio.h>

#define LENGHT 4
#define MAXLINE 1000

 main() {
    int c, j;

    while((c = getchar()) != EOF)
        if (c == '\t')
            for (j = 0; j<LENGHT; ++j)
                putchar(' ');
        else
            putchar(c); 
 }

