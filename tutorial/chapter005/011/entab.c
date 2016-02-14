#include <stdio.h>
#include <stdlib.h>

#define LENGTH 4

int main(int argc, char *argv[]) {
    int n = 0, i, c, b = 0, cur, k = 1;
    int clm = 0, start = 0;
    cur = 1;

    for (k = 1; k < argc; k++)
        if (*argv[k]++ == '+')
            clm = atoi(argv[k]);

    for (k = 1; k < argc; k++)
        if (*--argv[k] == '-') {
            start = atoi(++argv[k]);
        }
    k = 1;

    while ((c = getchar()) != EOF) {
        if (clm) {
            if (i++ == (start * clm)) {
                putchar('\t');
                start++;
            }    
        }
        else
            if (k < argc && n++ == (atoi(argv[k]))) {
                putchar('\t');
                k++;
            }
        
        if (c != ' ') {
            if (cur > 1 && cur < LENGTH)
                for (i = 0; i < cur; i++)
                    putchar(' ');
            
            else if (cur >= LENGTH) {
                for (i = cur/LENGTH; i > 0; i--)
                    putchar('\t');
                
                for (i = cur%LENGTH; i > 0; i--)
                    putchar(' ');
            }
            putchar(c);;
            b = 0;
            cur = 1;
        }
        
        else
            if (b == 0)
                b = 1;
            else
                cur++;
    }
    return 0;
}
