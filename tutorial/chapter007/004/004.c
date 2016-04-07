#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define BUFSIZE 100

int sc(char *);
int getch(void);
void ungetch(int c);
void minprintf(char *fmt, ...);
void printstr(char *, char *);
void digit2str(char *s, ...);
void reverse(char *s);

int flag = 0; /* 1  for string, 2 for int, 3 for double */
int bufp = 0;
char buf[BUFSIZE];

int main() {
    int c;
    char unit[BUFSIZE];

    while ((c = sc(unit)) != EOF) {
        if (flag == 1)
            minprintf("%s", unit);

        else if (flag == 2) 
            minprintf("%d", atoi(unit));
        
        else if (flag == 3) 
            minprintf("%f", atof(unit));

        else
            putchar(c);
        
        flag = 0;
    }

    return 0;
}

int sc(char *unit) {
    int c;
    char *up;
    up = unit;

    if (isalpha(c = getch())) {
        flag = 1;
        *up++ = c;
        
        while (isalpha(c = getch()))
            *up++ = c;
        
        *up = '\0';
        ungetch(c);
    }
    
    else if (isdigit(c)) {
        flag = 2;
        *up++ = c;

        while (isdigit(c = getch()))
            *up++ = c;

        if (c == '.') {
            flag = 3;
            *up++ = c;
            while (isdigit(c = getch()))
                *up++ = c;
        }

        *up = '\0';
        ungetch(c);
    }

    else
        return c;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval, temp[100];
    int ival;
    double dval;
    
    va_start(ap, fmt);

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        
        while (!islower(*p))
            *p++;

        switch (*p) {
        case 'd':
            flag = 2;
            ival = va_arg(ap, int);
            digit2str(temp, ival);
            printstr(fmt, temp);
            break;
        
        case 'f':
            flag = 3;
            dval = va_arg(ap, double);
            digit2str(temp, dval);
            printstr(fmt, temp);
            break;
        
        case 's':
            sval = va_arg(ap, char *);
            printstr(fmt, sval);
            break;
        
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}

void printstr(char *fmt, char *sval) {
    char *d, temp[100], *t;
    int left = 0, df = 0,  pc = 0, gap = 0;
    d = fmt;

    while (!islower(*d)) {
        if (*++d == '-') {
            left = 1;
            *++d;
        }

        if (isdigit(*d)) {
            t = temp;
            while (isdigit(*d))
                *t++ = *d++;
            *t = '\0';
            df = atoi(temp);
        }

        if (*d == '.') {
            t = temp;
            while (isdigit(*++d))
                *t++ = *d;
            *t = '\0';
            pc = atoi(temp);
        }
    }

    
    if (pc == 0 || pc > strlen(sval))
        pc = strlen(sval);

    if (df > pc)
        gap = df - pc;

    if (gap > 0 && left == 0)
        while (gap-- > 0)
            putchar(' ');

    while (pc-- > 0)
        putchar(*sval++);

    if (gap > 0 && left == 1)
        while (gap-- > 0)
            putchar(' ');
}

void digit2str(char *s, ...) {
    va_list digi;
    int i, j = 0, sign, n;
    double d = 0;

    va_start(digi, s);
    
    if (flag == 2) 
        n = va_arg(digi, int);

    else if (flag == 3) {
        d = va_arg(digi, double);
    
        while (((n = d) - d) < 0) {
            d *= 10;
            j++;
        }
    }

    if ((sign = n) < 0)
        n = -n;
    i = 0;

    s[i++] = n % 10 + '0';
    j--;

    while ((n /= 10) > 0) {
        s[i++] = n % 10 + '0';
        j--;
        if (j == 0)
            s[i++] = '.';
    }


    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

void reverse(char *s){
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
