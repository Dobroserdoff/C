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
void int2char(int, char *);
unsigned hash(char *s);
struct nlist *lookup(char *);
void install(char *, char *);
char *strdupl(char *);
void uninstall(struct nlist*);
void tableprint();

struct nlist *hashtab[HASHSIZE];
struct nlist *root;
int bufp = 0, p = 0, h;
char buf[BUFSIZE];

int main(int argc, char *argv[]) {
    char word[MAXWORD], name[MAXWORD];
    struct nlist *su;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0])) {
            h = hash(word);
            int2char(h, name);

            if (lookup(word) == NULL)
                install(word, name);
        }

    if ((argc > 1) && (strcmp(argv[1], "-u") == 0) && ((su = lookup(argv[2])) != NULL))
        uninstall(su);
    
    tableprint();

    return 0;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
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

void int2char(int n, char *p) {
    int i = 0;
    char s[MAXWORD];

    s[i++] = n % 10 + '0';
    while ((n /= 10) > 0)
        s[i++] = n % 10 + '0'; 
    
    while (i > 0)
        *p++ = s[--i];
    *p = '\0';
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

void uninstall(struct nlist *su) {
    su->prev->next = su->next;
    su->next->prev = su->prev;
    free(su);
}

void tableprint() {
    while (root->next != NULL) {
        printf("%15s %5s\n", root->name, root->defn);
        root = root->next;
    }
    printf("%15s %5s\n", root->name, root->defn);
}
