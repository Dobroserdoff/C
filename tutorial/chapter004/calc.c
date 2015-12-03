#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1' /* signal that a command was found */
#define FUNCTION '2' /* signal that function was found */
#define VARIABLE '3' /* signal that variable was found */
#define BUFSIZE 100 /* max buffer size for ungetch */ 
#define MAXVAL 100 /* max depth of value stack */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
double modulus(double a, double b);
void function (char []);
void command (char []);
void variable(char []);
void comprint(int);
void comduplicate(int);
void comswap(void);
void comclear(void);

int varletter, sp = 0, bufp = 0, k = 0, l = 0;
signed int varp[MAXVAL];
double val[MAXVAL];
double op2;
char buf[BUFSIZE];

int main()
{
    int type;
    char s[MAXOP];
    varp[0] = -1;
       
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
                    ;
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

void function(char s[])
{
    if (strcmp(s, "sin") == 0)
    {
        printf("%f\n", sin(1));
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

void variable(char s[])
{
    int i;
    double varval;

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
        printf("print error: incorrect amount of elements to print");
    else if (k > sp)
    {
        if (sp == 0)
            printf ("print error: stack is empty");
        else if (sp == 1)
            printf("print error: there is only one element in stack");
        else
            printf("print error: stack is only %d elements deep", sp);
    }
    else
    {
        printf("The top %d elements of the stack:", k);
        while (i < sp)
            printf(" %f", val[i++]);
    }
    printf("\n"); 
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
