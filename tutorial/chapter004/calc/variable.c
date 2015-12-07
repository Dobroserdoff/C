#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"

extern int varletter, sp, l, k;
extern int val[];

void variable(char s[])
{    
    int i;
    double varval;
    signed int varp[MAXVAL];

    if (strlen(s) == 0)
    { 
        varp[k++] = sp;
        varp[k] = -1;
        push(varletter);
    }
    
    else
    {
        varval = atof(s);
        for (i = 0; varp[i] != -1; i++)
            if (val[varp[i]] == varletter)
                val[varp[i]] = varval;
        l++;
    }
}

