#include <stdio.h>
#include "calc.h"

extern int sp;
extern double val[];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("push error: stack is full, can't push %g\n", f);
}
 
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("pop error: stack is empty\n");
        return 0.0;
    }
}

