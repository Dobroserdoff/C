#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[])
{
    int i, c;
    static int a = 0;
    extern int sp, l, k, varletter;

    while ((c = ((a != 0) ? a : getchar())) == ' ' || c == '\t' || c == '\n')
    {   
        if (c == '\n')
        {
            if (sp == 0)
                printf("main error: stack is empty\n");
            else
            {
                if (l == k)
                {
                    printf("%g ", pop());
                    ++sp;
                }
                else
                {
                    printf("main error: undefined variable\n");
                    l = k = 0;
                    comclear();
                }
            }
        }  
        s[0] = c;
        a = 0;
    }

    s[1] = '\0';
    
    if (!isdigit(c) && !isupper(c) && c != '-' && c != '+' && c != 'f' && !('a' <= c && c <= 'e'))
        return c;

    i = 0;

    if (c == '-' || c == '+')
    {
        s[i++] = c;
        while (isdigit(c = getchar()))
           s[i++] = c;
        
        if (i == 1)
        {
            a = c;
            return s[0];
        }
    }
    
    if ('a' <= c && c <= 'e')
    {
        varletter = c;
        while (isdigit(c = getchar()))
            s[i++] = c;
        
        s[i] = '\0';
        a = c;
        return VARIABLE;
    }

    if (isupper(c))
    {
        s[i++] = c;
        while (isdigit(c = getchar()))
            s[i++] = c;

        s[i] = '\0';
        a = c;
        return COMMAND;
    }
    
    if (c == 'f')
    {
        while (!isspace(c = getchar()))
            s[i++] = c;
        a = c;
        s[i] = '\0';
        return FUNCTION;
    }        

    if (isdigit(c))
    {
        s[i++] = c;
        while (isdigit(c = getchar()) || c =='.')
           s[i++] = c;
    }

    s[i] = '\0';
    a = c; 
    return NUMBER;
}
