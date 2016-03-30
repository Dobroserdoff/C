#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NKEYS 100
#define MAXWORD 100
#define BUFSIZE 100

int flag = 0;
int bufp = 0;
char buf[BUFSIZE];

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

