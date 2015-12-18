#include <stdio.h>
#include <string.h>
#define MAX 100

int strtail(char s[], char t[]);
char s[MAX], t[MAX];

main() {
    int c, first = 1;
    char *sp, *tp; 

    sp = &s[0];
    tp = &t[0];

    while ((c = getchar()) != EOF) {
        if (first) {
            *sp++ = c;
            if (c == '\n') {
                *sp = '\0';
                first = 0;
                printf("Original string: %s", s);
            }
        }
        else {
            *tp++ = c;
            if (c == '\n') {
                *tp = '\0';
                printf(("Result: %d for %s"), strtail(s, t), t); 
                tp = &t[0];
            }
        }
    }   
    return 0;
}

int strtail(char s[], char t[]) {
    char *sp, *tp, *tempp;
    char temp[MAX];

    sp = &s[0];
    tp = &t[0];
    tempp = &temp[0];

    while(*sp++) {
        if (*sp == *tp)
            *tempp++ = *tp++; 
        else {
            tempp = &temp[0];
            tp = &t[0];
        }
    } 
    *tempp = '\0';

    if (strcmp(temp, t) == 0)
        return 1;
    else
        return 0;
        
}
