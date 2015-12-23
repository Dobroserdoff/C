#include <stdio.h>
#include "str.h"

extern int n, strp, strmark[];
extern char str[];

void push(char *s) {
    int i;
    char *t;
    t = &str[0];

    if (strp > 1) {
        t = &str[strmark[strp - 2]];
        while (*t++ != '\0')
            ;
        *t--;
    }

    if (strp < MAXVAL) {
        for (i = 0; *t++ = *s++; i++)
            ;
        *t = '\0';
        strmark[strp] = strmark[strp - 1] + (i - 1);
        strp++;
        printf("STR - %s, MARK - %d, POS - %d\n", str, strmark[strp - 1], strp);
    }    
    else
        printf("push error: stack is full");
}
 
/*char pop(void) {
    char *t = &str[strmark[strp - 2]]; 
    static char *zero = NULL;
 

    if (strp > 1) {
        strp--;
        printf("POP - %s", t);
    }
    else
    {
        printf("pop error: stack is empty\n");
        return *zero;
    }
}*/
