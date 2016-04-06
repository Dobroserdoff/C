#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);
void printstr(char *, char *);
void digit2str(char *s, ...);
void reverse(char *s);

int flag = 0;

int main() {
    minprintf("%-15s", "hello, world");
    minprintf("%10s", "hello, world");
    minprintf("%15.10s\n", "hello, world");
    minprintf("%.3d ", 12345);
    minprintf("%5d ", 0);
    minprintf("%d\n", -318);
    minprintf("%15f ", 12.345);
    minprintf("%f\n", 9.876);

    return 0;
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
            flag = 1;
            ival = va_arg(ap, int);
            digit2str(temp, ival);
            printstr(fmt, temp);
            break;
        
        case 'f':
            flag = 2;
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
    
    if (flag == 1) 
        n = va_arg(digi, int);

    else if (flag == 2) {
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
