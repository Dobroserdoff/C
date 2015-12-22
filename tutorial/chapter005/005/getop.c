#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "str.h"

int getop() {
    int a, b = 0, c, j, k = 0;
    char *sp, num[MAXNUM];
    extern int n, strp, strmark[];
    extern char str[];

    sp = &str[strmark[strp]];

    for (j = 0; (c = getchar()) != EOF; j++) {  
        if (c == 'C' && isupper(b = getchar())) {
            while (isdigit(a = getchar()))
                num[k++] = a;
            num[k++] = '\n';
            num[k] = '\0';
            n = atoi(num);

            if (b == 'P')
                return COPY;
            else if (b == 'M')
                return COMPARE;
            else if (b == 'T')
                return CONCATENATE;
            else if (b == 'D')
                return DELETE;
        }
        
        else {
            *sp++ = c;
            if (b) {
                *sp++ = b;
                b = 0;
            }

            if (c == '\n')
                strmark[strp++] = j + 1;
        }    
    }    
    return STRING;
}
