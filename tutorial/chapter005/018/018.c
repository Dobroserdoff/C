#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
void undcl(void);
int gettoken(void);
int getch(void);
void ungetch(int);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char buf[BUFSIZE];
int bufp = 0;

int main(int argc, char* argv[]) {
    while (gettoken() != EOF) {
        out[0] = '\0';

        if ((argc > 1) && (strcmp(argv[1], "-u") == 0)) {
            undcl();
            printf("%s\n", out);
        }

        else {
            strcpy(datatype, token);
            dcl();
            if (tokentype != '\n')
                printf("syntax error\n");

            printf("%s: %s %s\n", name, out, datatype);
        }
    }
    return 0;
}

int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }

        else {
            ungetch(c);
            return tokentype = '(';
        }
    }

    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }

    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }

    else
        return tokentype = c;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; )
        ns++;
    
    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    }

    else if (tokentype == NAME)
        strcpy(name, token);
    
    else
        printf("error: expected name or (dcl)\n");
    
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

void undcl(void) {
    int type;
    char temp[MAXTOKEN];

    strcpy(out, token);

    while ((type = gettoken()) != '\n') {
        if (type == PARENS || type == BRACKETS)
            strcat(out, token);

        else if (type == '*') {
            sprintf(temp, "(*%s)", out);
            strcpy(out, temp);
        }

        else if (type == NAME) {
            sprintf(temp, "%s %s", token, out);
            strcpy(out, temp);
        }

        else
            printf("invalid input at %s\n", token);
    }
}
