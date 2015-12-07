#include <stdio.h>
#include <string.h>
#include <math.h>
#include "calc.h"

void function(char s[])
{
    double op2;
    
    if (strcmp(s, "sin") == 0)
    {
        push(sin(pop()));
    }
    else if (strcmp(s, "cos") == 0)
        push(cos(pop()));
    else if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(s, "pow") == 0)
    {   
        op2 = pop();
        push(pow(op2, pop()));
    }
    else if (strcmp(s, "sqrt") == 0)
        push(sqrt(pop()));
}

