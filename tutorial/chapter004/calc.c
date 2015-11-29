#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1' /* signal that a command was found*/
#define BUFSIZE 100 /* max buffer size for ungetch */ 
#define MAXVAL 100 /* max depth of value stack */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
double modulus(double a, double b);
void command (char []);
void comprint(int);
void comduplicate(int);
void comswap(void);
void comclear(void);

int sp = 0, bufp = 0;
double val[MAXVAL];
char buf[BUFSIZE];

main()
{
    int type, sign = 1;
    double op2;
    char s[MAXOP];
       
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
                printf("%g", pop());
                ++sp; 
                break;
            default:
                printf("main error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

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

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    if (!isdigit(c) && !isupper(c) && c != '.' && c != '-' && c != '+')
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
    
    if (isupper(c))
    {
        s[i] = c;
        while (isdigit(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        return COMMAND;
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

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch error: too many characters\n");
    else
        buf[bufp++] = c;
}

double modulus(double a, double b)
{
    int i;

    i = (int)(a / b);
    return (a - (b * i));
}

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
    /*else if (s[0] == 'S')
        comswap;
    else if (s[0] == 'C')
        comclear;*/  
}

void comprint(int k)
{
    int i;
    i = sp - k;

    if (k < 1)
        printf("print error: incorrect amount of elements to print");
    else if ((k - 1) > sp)
        printf("print error: stack is only %d elements deep", sp + 1);
    else
    {
        printf("\nThe top %d elements of the stack:", k);
        while (i < sp)
            printf(" %f", val[i++]);
    }
    printf("\n"); 
}

void comduplicate(int k)
{
    int i, j = sp;
    i = sp - k;

    if (k < 1)
        printf("duplicate error: incorrect amount of elements to duplicate");
    else if ((k - 1) > sp)
        printf("duplicate error: stack is only %d elements deep", sp + 1);
    else
/bin/bash: :gcc: command not found
            push(val[i++]); 
}   
 
