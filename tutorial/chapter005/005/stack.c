#include <stdio.h>
#include "calc.h"

extern int strp, strmark[];
extern char str[];

void push(char *s) {
    int i;
    char *t = &str[0];

    if (sp < MAXVAL) {
        for (i = 0; *t++ = *s++; i++)
            ;
        strmark[++strp] = i;
    }
    else
        printf("push error: stack is full\n");
}
 
char pop(void) {
    char *t = &str[strmark[strp--]];
    
    if (sp > 0)
        return *t;
    else {
        printf("pop error: stack is empty\n");
        return "\n\0";
    }
}

