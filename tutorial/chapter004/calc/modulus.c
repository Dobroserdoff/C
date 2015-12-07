#include <stdio.h>
#include "calc.h"

double modulus(double a, double b)
{
    int i;

    i = (int)(a / b);
    return (a - (b * i));
}

