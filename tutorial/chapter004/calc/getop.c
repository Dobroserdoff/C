#include <stdio.h>
#include <ctype.h>
#include "calc.h"



int getop(char s[])
{
    int i, c;
    extern int varletter;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    if (!isdigit(c) && !isupper(c) && c != '.' && c != '-' && c != '+' && c != 'f' && !('a' <= c && c <= 'e'))
        return c;
    
    i = 0;

    if (c == '-' || c == '+')
    {
        s[0] = c;
        while (isdigit(s[++i] = c = getch()))
            ;

        if (i == 1)
        {
            ungetch(c);
            return s[0];
        }
    }
    
    if ('a' <= c && c <= 'e')
    {
        varletter = c;
        while (isdigit(c = getch()))
            s[i++] = c;
        
        s[i] = '\0';
        ungetch(c);
        return VARIABLE;

    }

    if (isupper(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;

        s[i] = '\0';
        ungetch(c);
        return COMMAND;
    }
    
    if (c == 'f')
    {
        while (!isspace(c = getch()))
            s[i++] = c;

        s[i] = '\0';
        ungetch(c);
        return FUNCTION;
    }        

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
 
    if (c != EOF)
        ungetch(c);
        
    return NUMBER;
}

