#include <stdio.h>
#include <ctype.h>
 
#define SIZE 50

int getch(void);
void ungetch(int);
int getint(int *pn);

int n, bufp = 0;
char buf[SIZE];
int array[SIZE];

int main() {
    int getint(int *);

    for (n = 0; n < SIZE && (getint(&array[n])) != EOF; n++)
        printf("%d ", array[n]);
    
    return 0;
}

int getint(int *pn) {
    int b, c, sign;
    
    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '\n')
       c = getint(&array[++n]);

    sign = (c == '-') ? -1 : 1;
    
    if (c == '+' || c == '-') {
        if (isdigit(b = getch()))
            c = b;
        else
            c = getint(&array[++n]);
    }

    if (c == '\n') {
        printf("\n");
        c = getint(&array[++n]);    
    }

    if (c != EOF) {
        for (*pn = 0; isdigit(c); c = getch())
            *pn = 10 * *pn + (c - '0');
    
        *pn *= sign;
        ungetch(c);
    }
        
    return c;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= SIZE)
        printf("ungetch error: too many characters\n");
    else
        buf[bufp++] = c;
}
