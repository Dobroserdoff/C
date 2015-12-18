#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int n = 0, i, strp = 0; strmark[MAXVAL];
char buf[MAXLENGTH], str[MAXLENGTH];

strmark[0] = 0;
strmark[1] = '\r';

int main()
{
    int type;
       
    while ((type = getop()) != EOF)
    {
        switch (type)
        {
            case STRING:
                push(buf);
                break; 
            case COPY:
                strncp(str, strmark, n);
                break;
            case COMPARE:
                strncm(str, strmark, n);
                break;
            case CONCATENATE:
                strnct(str, strmark, n);
                break;
            default:
                printf("main error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

