#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "str.h"

int getop() {
    int a, b = 0, c, k = 0;
    char *sp, num[MAXNUM];
    extern int n;
    extern char buf[];

    sp = &buf[0];

    while ((c = getchar()) != EOF) {  
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

            if (c == '\n') {
                *sp = '\0';
                return STRING;
            }
        }    
    }    
    return c;
}
