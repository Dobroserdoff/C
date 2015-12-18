#include <stdio.h>

#define MAX 100

void strconcat(char s[], char t[]);
char s[MAX], t[MAX];


int main() {
    int c, first = 1;
    char *sp, *tp; 

    sp = &s[0];
    tp = &t[0];

    while ((c = getchar()) != EOF) {
        if (first == 1) {
            *sp++ = c;
            if (c == '\n') {
                *sp = '\0';
                first = 0;
            }
        }
        else {
            *tp++ = c;
            if (c == '\n') {
                *tp = '\0';
                strconcat(s, t); 
                tp = &t[0];
            }
        }
    }
    printf("%s\n", s);
    return 0;
}

void strconcat(char s[], char t[]) {
    char *sp, *tp;
    
    sp = &s[0];
    tp = &t[0];

    while (*sp++ != '\n')
        ;
    *sp--;

    while ((*sp++ = *tp++) != '\0')
        ;
    
    *sp = '\0';
}
