#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include<stdlib.h>

#define HASHSIZE 10000
#define MAXWORD 100
#define BUFSIZE 100

struct nlist { 
    struct nlist *prev;
    struct nlist *next;
    char *name; 
    char *defn;
};

int getword(char *, int);
int getch(void);
void ungetch(int);
unsigned hash(char *s);
struct nlist *lookup(char *);
void install(char *, char *);
char *strdupl(char *);
void definition();

struct nlist *hashtab[HASHSIZE];
struct nlist *root;
int bufp = 0, p = 0, h, flag = 0;
char buf[BUFSIZE];

int main() {
    char word[MAXWORD];
    struct nlist *su;

    while (getword(word, MAXWORD) != EOF) {
        if (flag == 1) {
            printf("%s", word);
            definition();
            getword(word, MAXWORD);
        }

        if ((su = lookup(word)) == NULL)
            printf("%s", word);
        else
            printf("%s", su->defn);
    }

    return 0;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    c = getch();

    if (c == '#')
        flag = 1;

    if (isalnum(c)) {
        *w++ = c;

        for (; --lim > 0; w++)
            if (!isalnum(*w = getch())) {
                ungetch(*w);
                break;
            }
        *w = '\0';

        return word[0];
    }

    *w++ = c;
    *w = '\0';
    return word[0];
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

unsigned hash(char *s) {
    unsigned hashval;
    
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    
    return NULL;
}

void install(char *name, char *defn) {
    struct nlist *np;
    
    np = (struct nlist *) malloc(sizeof(*np));
    np->next = NULL;
    np->name = strdupl(name);
    np->defn = strdupl(defn);
    hashtab[h] = np;
    
    if (p > 0) {
        hashtab[p]->next = np;
        np->prev = hashtab[p];
    }
    else {
        np->prev = NULL;
        root = np;
    }

    p = h;
}

char *strdupl(char *s) {
    char *p;
    p = (char *)malloc(strlen(s) + 1);

    if (p != NULL)
        strcpy(p, s);
    return p;
}

void definition() {
    char word[MAXWORD], name[MAXWORD];

    getword(word, MAXWORD);
    printf("%s", word);

    if (strcmp(word, "define") == 0) {
        while (!isalnum(getword(word, MAXWORD)))
            printf("%s", word);

        h = hash(word);
        printf("%s", word);

        while (!isalnum(getword(name, MAXWORD)))
            printf("%s", name);
        printf("%s", name);

        if (lookup(word) == NULL)
            install(word, name);
    }

    flag = 0;
}
