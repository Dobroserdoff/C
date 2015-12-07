#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int varletter, sp = 0, bufp = 0, k = 0, l = 0;
double val[MAXVAL];
char buf[BUFSIZE];

int main()
{
    int type;
    char s[MAXOP];
    double op2;
       
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case COMMAND:
                command(s);
                break;
            case FUNCTION:
                function(s);
                break;
            case VARIABLE:
                variable(s);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("main error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(modulus(pop(), op2));
                else
                    printf("main error: zero divisor\n"); 
                break;
            case '\n':
                if (sp == 0)
                    printf("main error: stack is empty\n");
                else
                {
                    if (l == k)
                    {
                        printf("%g\n", pop());
                        ++sp;
                    }
                    else
                    {
                        printf("main error: undefined variable\n");
                        l = k = 0;
                        comclear();
                    }
                }
                break;
            default:
                printf("main error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

