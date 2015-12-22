#include <stdio.h>
#include "str.h"

extern int n, strp, strmark[];
extern char str[];

void strncp() {
    char *t = &str[strmark[--strp]];
    char *r = &str[strmark[--strp]];

    while (n-- > 0) 
        if ((*r++ = *t++) == '\n')
            break;

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
    char *t = &str[strmark[--strp]];
    char *r = &str[strmark[--strp]];

    while (*r++ != '\n')
        ;

    while (n-- > 0) 
        if ((*r++ = *t++) == '\n')
            break;

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
