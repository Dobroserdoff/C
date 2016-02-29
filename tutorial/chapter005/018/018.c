#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum {NAME, PARENS, BRACKETS, POINTERS, ARGUMENTS};

void dcl(void);
void dirdcl(void);
void undcl(void);
int gettoken(void);
int getch(void);
void ungetch(int);
char* strclone(const char *s);

int tokentype;
int bufp = 0;
int flag = 0;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char buf[BUFSIZE];

int main(int argc, char *argv[]) {
    while (gettoken() != EOF) {
        out[0] = '\0';

        if ((argc > 1) && (strcmp(argv[1], "-u") == 0)) {
            flag = 1;
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
    int i = 0, c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }

        else if ((flag == 1) && (c == '*')) {
            while ((c = getch()) != ')')
                ;
            return tokentype = POINTERS;
        }

        else if (islower(c) != 0) {
            *p++ = c;
            while ((c = getch()) != ')')
                *p++ = c;
            *p = '\0';
            return tokentype = ARGUMENTS;
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
    int i = 0, type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    }

    else if (tokentype == NAME)
        strcpy(name, token);
    
    else
        printf("error: expected name or (dcl)\n");
    
    while ((type = gettoken()) == ARGUMENTS || type == PARENS || type == BRACKETS) {
        if (type == ARGUMENTS) {
            strcat(out, " function accepting ");
            strcat(out, token);
            strcat(out, " and returning");
        }
        else if (type == PARENS)
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
        if (type == POINTERS) {
            sprintf(temp, "(*%s)", out);
            strcpy(out, temp);
        }

        else if ((type == PARENS) || (type == BRACKETS))
            strcat(out, token);

        else if (type == '*') {
            sprintf(temp, "*%s", out);
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

char* strclone(const char *s) {
    char *result, *buf = malloc(strlen(s) + 1);
    result = buf;

    while ((*buf++ = *s++) != '\0')
        ;

    return result;
}
