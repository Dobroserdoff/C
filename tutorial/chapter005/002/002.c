#include <stdio.h>
#include <ctype.h>
 
#define SIZE 100

double getch(void);
void ungetch(double);
double getdouble(double *pn);

int n, bufp = 0;
char buf[SIZE];
double array[SIZE];

int main() {
    for (n = 0; n < SIZE && (getdouble(&array[n])) != EOF; n++)
        printf("%F ", array[n]);
    
    return 0;
}

double getdouble(double *pn) {
    int i = 0, e = 0;
    double b, c, sign;
    
    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '\n' && c != '.')
       c = getdouble(&array[++n]);

    sign = (c == '-') ? -1 : 1;
    
    if (c == '+' || c == '-') {
        if (isdigit(b = getch()))
            c = b;
        else
            c = getdouble(&array[++n]);
    }

    if (c == '\n') {
        printf("\n");
        c = getdouble(&array[++n]);    
    }

    if (c != EOF) {
        *pn = 0;
        i = 10 * i + (c - '0');
        
        while (isdigit(c = getch()))
            i = 10 * i + (c - '0');
        
        if (c == '.') {
            while(isdigit(c = getch())) {
                *pn = 10.0 * *pn + (c - '0');
                e--;
            }
        }
        
        while (e < 0) {
            *pn *= 0.1;
            e++;
        }
        
        *pn += i;
        *pn *= sign;
        ungetch(c);
    }
        
    return c;
}

double getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(double c) {
    if (bufp >= SIZE)
        printf("ungetch error: too many characters\n");
    else
        buf[bufp++] = c;
}
