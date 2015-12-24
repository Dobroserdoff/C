#include <stdio.h>
#include "str.h"

extern int n, strp;
extern char *str[];

void push(char *s) {
    char *t;
    (str[strp]) ? : (str[strp] = NULL);
    t = &str[strp][0];
    printf("%c", *t);
}
/*    
    if (strp < MAXVAL) {
     while (*t++ = *s++)
            printf("%s ", t - 1);
        *t = '\0';
    }
    else
        printf("push error: stack is full");
}
 
char pop(void) {
    char *r, *zero = NULL;
    r = &str[strmark[strp - 2]];

    if (strp > 1) {
        strp--;
        return r;
    }
    else
    {
        printf("pop error: stack is empty\n");
        return *zero;
    }
}*/
