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
    char t[MAXLENGTH];
    char r[MAXLENGTH];
    char *tp, *rp;
    t = pop();
    r = pop();

    *tp = &t[0];
    *rp = &r[0];

    printf("T - %s, R - %s", tp, rp);

   while (*tp++ != '\n')
        ;
    tp--;

    while (n-- > 0) 
        if ((*tp++ = *rp++) == '\n')
            break;
    *tp = '\0';
    push(t);

    printf("%s", str);
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
