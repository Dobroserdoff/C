#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct key {
    char *word;
    int count;
} keytab[] = {
    "#include", 0,
    "_char", 0,
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "else", 0,
    "if", 0,
    "include", 0,
    "int", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};
int flag = 0;
int bufp = 0;
char buf[BUFSIZE];

int getch(void);
void ungetch(int c);
int getword(char *, int);
int bsearch(char *, struct key *, int);

int main() {
    int n;
    char word[MAXWORD];
    int NKEYS = sizeof(keytab) / sizeof(struct key);

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || (word[0] == '_') || (word[0] == '#'))
            if ((n = bsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    
    return 0;
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

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))
        if ((c == '\n') && (flag == 3)) 
            flag = 0;
       
    if (c == '"') {
        if (flag == 0)
            flag = 1;
        else if (flag == 1)
            flag = 0;
    }

    if ((c == '/') && (flag == 0)) {
        c = getch();
        if (c == '*')
            flag = 2;
        else if (c == '/')
            flag = 3;
        else
            ungetch(c);
    }

    if ((c == '*') && (flag == 2))
        ((c = getch()) == '/') ? (flag = 0) : (ungetch(c));


    if (c != EOF)
        *w++ = c;
    
    if ((!isalpha(c)) && (c != '_') && (c != '#')) {
        *w = '\0';
        return c;
    }
    
    for (; --lim > 0; w++)
        if ((!isalnum(*w = getch())) && (*w != '_') && (*w != '#')) {
            ungetch(*w);
            break;
        }
    
    *w = '\0';
    if (flag == 0)
        return word[0];
    else
        return word[0] = '\0';
}

int bsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;

        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;

        else if (cond > 0)
            low = mid + 1;

        else
            return mid;
    }
    return -1;
}
 
