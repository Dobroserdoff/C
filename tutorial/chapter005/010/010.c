#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXVAL 100
#define MAXLEN 100

int first_check(int argc, char *argv[]);
void push(int f);
int pop(void);
int expr(char C);
void string(int pivot, int argc, char *argv[]);
void itoa(int i);

int val[MAXVAL], sp = 0;
char text[MAXLEN], buf[MAXLEN];

int main(int argc, char *argv[]) {    
    int pivot = 1, j;
    
    if ((first_check(argc, argv) == 0)) {
        while ((*argv[argc - pivot] == 'x') || (*argv[argc - pivot] == '/') || (*argv[argc - pivot] == '-') || (*argv[argc - pivot] == '+'))
             pivot++;

        for (j = 2; j <= (argc - pivot); j++)
            push(atoi(argv[j]));

        string(pivot, argc, argv);
        
        while (sp > 1)
            push(expr(*argv[argc - (--pivot)]));

        printf("%s %d\n", text, val[0]);
    }
    else
        printf("main error\n");
    
    return 0;
}

int first_check(int argc, char *argv[]) {
    if ((argc >= 5) && (strcmp(argv[1], "expr") == 0) && (isdigit(*argv[2])) &&
        (((*argv[argc - 1] == 'x') || (*argv[argc - 1] == '/')) || ((*argv[argc - 1] == '-') || (*argv[argc - 1] == '+'))))
        return 0;

    else {
        printf("input error: try once again\n");
        return 1;
    }
}

void push(int f) {
    if (sp < MAXVAL) 
        val[sp++] = f;
    
    else
        printf("push error: stack is full, can't push %d\n", f);
}
 
int pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("pop error: stack is empty\n");
        return 0;
    }
}

void string(int pivot, int argc, char *argv[]) {
    int i;
    char *result, *temp;
    result = &text[0];

    i = sp;
    while (i-- > 2)
        *result++ = '(';

    i = sp;
    while (i) {
        itoa(val[--i]);
        temp = &buf[0];
        while ((*result++ = *temp++) != '\0')
            ;
        result--;

        if (((sp - i) >= 2) && (i != 0))
            *result++ = ')'; 
        
        if (i)
            *result++ = *argv[argc - (--pivot)];
        else
            *result = '=';
    }
}

int expr(char C) {  
    switch (C) { 
        case '+':
            return (pop() + pop());
            break;
        case '-':
            return (pop() - pop());
            break;
        case 'x':
            return (pop() * pop());
            break;
        case '/':
            return (pop() / pop());
            break;
        default:
            printf("expression error");
            break;
    }
    return 0;
}

void itoa(int n) {
    int c, j, i, sign;
    char *s;
    s = &buf[0];

    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    }
    while ((n /= 10) > 0);
        
    if (sign < 0)
        *s++ = '-';
    
    *s = '\0';
    
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
