#include <stdio.h>
#include "str.h"

extern int n, strp, strmark[];
extern char str[];

void strncp() {
    char *t = &str[strmark[--strp]];
    char *r = &str[strmark[--strp]];

    while (n-- > 0 && *t != '\n') 
        *r++ = *t++;

    printf("%s", str);
}

void strncm() {
    char *t = &str[strmark[--strp]];
    char *r = &str[strmark[--strp]];

    for (n; *r++ == *t++, n > 0; n--)
        if (*t == '\n')
            break;
            
    if (*t == *r || *t == '\n')    
        printf("Compare result: 0");
    else     
        printf("Compare result: %d", *t - *r);
}

void strnct() {
    if (n > 2) {
        char *t, *r, *q;
        t = pop();
        r = pop();
        q = r;

        while (*r++ != '\n')
            ;
        *r--;

        while (n-- >= 0) 
            if((*r++ = *t++) == '\n')
                break;

        *r = '\0';
        printf("Q - %s", q);
        push(q);

        printf("%s", str);
    }
    else
        printf("concatenation error: insufficient data to operate");
}

void strncd() {
    if (n != 0) {
        str[-1 - n] = '\0';
        str[-2] = '\n';
    }
    else
        str[strmark[--strp] + 1] = '\0';

    printf("%s", str);
}
