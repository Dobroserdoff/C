#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h"

int getop() {
    int a, b = 0, c, j, k = 0;
    char *sp, num[MAXNUM];
    extern char buf[];
    extern int n, strp, trmark[];
    
    sp = &str[strmark[strp]];

    for (j = 0; (c = getchar()) != EOF; j++) {  
        if (c == '\n') {
            *sp++ = '\n';
            *sp = '\0';
            return STRING;
        }
        else if (c == 'C' && isupper(b = getchar())) {
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
        }
        else {
            *sp++ = c;
            if (b)
                *sp++ = b;
        }    
    }    
}
