#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXWORD 100
#define BUFSIZE 100

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
int getch(void);
void ungetch(int c);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *strdupl(char *);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};
int flag = 0;
int bufp = 0;
char buf[BUFSIZE];

int main(int argc, char *argv[]) {
    int maxword = 6;
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;

    if (argc > 1)
        maxword = abs(atoi(argv[1]));

    while (getword(word, maxword) != EOF)
        if (strlen(word) == maxword && isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);

    return 0;
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
        c = getch();
    }

    if ((c == '/') && (flag == 0)) {
        c = getch();
        if (c == '*') {
            flag = 2;
            c = getch();
        }
        else if (c == '/') {
            flag = 3;
            c = getch();
        }
        else
            ungetch(c);
    }

    if ((c == '*') && (flag == 2))
        ((c = getch()) == '/') ? (flag = 0) : (ungetch(c));
    
    if (flag == 0) {
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
    }
    *w = '\0';
    
    while (isalnum(c = getch()))
        ;
    ungetch(c);

    if (flag == 0)
        return word[0];
    else
        return word[0] = '\0';
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

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc(); 
        p->word = strdupl(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    
    else if (cond < 0) 
        p->left = addtree(p->left, w);
    
    else 
        p->right = addtree(p->right, w);
    
    return p;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdupl(char *s) {
    char *p;
    p = (char *)malloc(strlen(s) + 1);
    
    if (p != NULL)
        strcpy(p, s);
    return p;
}
