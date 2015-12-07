#include <stdio.h>
#include "calc.h"

extern int sp;
extern double val[];

void command(char s[])
{
    int k, i = 0, n = 0;
    char a[MAXOP];

    if (isdigit(s[1]))
        while(s[++i] != '\0')
               a[n++] = s[i];

    a[n] = '\0';
    k = atoi(a);

    if (s[0] == 'P')
        comprint(k);
    else if (s[0] == 'D')
        comduplicate(k);
    else if (s[0] == 'S')
        comswap();
    else if (s[0] == 'C')
        comclear();  
}

void comprint(int k)
{
    int i;
    i = sp - k;

    if (k < 1)
        printf("print error: incorrect amount of elements to print\n");
    else if (k > sp)
    {
        if (sp == 0)
            printf ("print error: stack is empty\n");
        else if (sp == 1)
            printf("print error: there is only one element in stack\n");
        else
            printf("print error: stack is only %d elements deep\n", sp);
    }
    else
    {
        printf("The top %d elements of the stack:", k);
        while (i < sp)
            printf(" %f", val[i++]);
        printf("\n");
    }
}

void comduplicate(int k)
{
    int i, j = sp - 1;
    i = sp - k;

    if (k < 1)
        printf("duplicate error: incorrect amount of elements to duplicate");
    else if (k > sp)
        printf("duplicate error: stack is only %d elements deep", sp);
    else
        while (i <= j)
            push(val[i++]); 
}   

void comswap()
{
    double i;

    i = val[sp - 1];
    val[sp - 1] = val[sp - 2];
    val[sp - 2] = i;
}

void comclear()
{
    sp = 0;
}
