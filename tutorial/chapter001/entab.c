#include <stdio.h>

#define LENGHT 4

 main() {
    int i, c, b, cur;
    cur = 1;

    while ((c = getchar()) != EOF)
        if (c != ' ') {
            if (cur > 1 && cur < LENGHT)
                for (i = 0; i < cur; ++i)
                    putchar(' ');
            
            else if (cur > LENGHT)
                for (i = cur/LENGHT; i > 0; --i)
                    putchar('\t');
                
                for (i = cur%LENGHT; i > 0; --i)
                    putchar(' ');
            
            putchar(c);;
            b = 0;
            cur = 1;
         }
        else
            if (b == 0)
                b = 1;
            else
                ++cur;
 }
