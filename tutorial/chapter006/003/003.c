#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
int getch(void);
void ungetch(int);
int wordcheck(char *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *strdupl(char *);

struct tnode {
    char *word;
    int pline;
    int lines[BUFSIZE];
    struct tnode *left;
    struct tnode *right;
};
int nline = 1;
int bufp = 0;
char buf[BUFSIZE];

int main() {
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && wordcheck(word) == 0)
            root = addtree(root, word);
    treeprint(root);

    return 0;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n')
            nline++;

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

int wordcheck(char *word) {
    char *list[] = { "A", "The", "This", "a", "also", "and", "any", "are", "as", "at", "be", "been", "by", "can", 
    "do", "done", "for", "have", "if", "in", "into", "is", "isn", "it", "its", "of", "or", "s", "so", "t", "than",
    "that", "the", "their", "to", "too", "with", "would", "0" };
    int i = 0;
    
    while (strcmp(list[i], "0") != 0)
       if (strcmp(word, list[i++]) == 0)
           return 1;

    return 0;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdupl(w);
        p->pline = 0;
        p->lines[p->pline++] = nline;
        p->lines[p->pline] = 0;
        p->left = p->right = NULL;
    }

    else if ((cond = strcmp(w, p->word)) == 0) {
        if (p->lines[(p->pline) - 1] != nline) {
            p->lines[(p->pline)++] = nline;
            p->lines[p->pline] = 0;
        }
    }

    else if (cond < 0)
        p->left = addtree(p->left, w);

    else
        p->right = addtree(p->right, w);

    return p;
}

void treeprint(struct tnode *p) {
    int i;
    
    if (p != NULL) {
        treeprint(p->left);

        printf(" %15s: ", p->word);
        for (i = 0; (p->lines[i]) != 0; i++)
            printf(" %3d ", p->lines[i]);
        printf("%c", '\n');

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
