#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINES 1000
#define MAX 120

char *strings[MAX];
char *propers[MAX];
int sp = 0;
int numeric = 0;
int reverse = 0;
int fold = 0;
int direct = 0;

int argcheck(char *);
int readinput(void);
void quicksort(int, int, int(*)(const void *, const void *));
int numcmp(const char *, const char *);
void swap(int, int);
char* strclone(const char *);

int main(int argc, char *argv[]) {
    int i;
    
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') && (argcheck(argv[i] + 1) == 0))
            ;
        else
            printf("invalid arguments: try once again\n");
    }

    if (numeric == 1)
        fold = 0;

    if ((readinput() == 0) && ((sp > 1) && (sp < MAXLINES)))
        quicksort(0, sp - 1, (int(*)(const void*, const void*))((numeric) ? (numcmp) : (strcmp)));
    else {
        printf("input error\n");
        return 1;
    }

    printf("list of strings sorted with %s %s %s %s algorithm\n", direct ? "direct" : "",
        reverse ? "reverse" : "straight", numeric ? "numeric" : "string comparison", fold ? "folded" : "");
    
    for (i = 0; i < sp; i++) {
        printf("%s", strings[i]);
        free(strings[i]);
    }
   
    return 0;
}

int argcheck(char *s) {
    while (*s)
        switch (*s++) {
        case 'n':
            numeric = 1;
            break;
        case 'r':
            reverse = 1;
            break;
        case 'f':
            fold = 1;
            break;
        case 'd':
            direct = 1;
            break;
        default:
            return 1;
        }
    return 0;
}

int readinput(void) {
    int c;
    char *s, *p, string[MAX], proper[MAX];
    s = string;
    p = proper;

    while ((c = getchar()) != EOF) {
        *s++ = c;
        if ((direct == 1 && ispunct(c) == 0) || (direct == 0))
            *p++ = (fold == 1) ? (tolower(c)) : c;

        if (c == '\n') {
            *s = '\0';
            *p = '\0';
            strings[sp] = strclone(string);
            
            if (proper[0] != '\n')
                propers[sp++] = strclone(proper);
            else
                return 1;
            
            s = string;
            p = proper;
        }
    }
    return 0;
}

void quicksort(int left, int right, int(*comp)(const void *, const void *)) {
    int i, last;
    
    if (left >= right) 
        return; 

    swap(left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((reverse) ? ((*comp)(propers[i], propers[left]) > 0) : ((*comp)(propers[i], propers[left]) < 0))
            swap(++last, i);

    swap(left, last);
    quicksort(left, last - 1, comp);
    quicksort(last + 1, right, comp);
}

int numcmp(const char *s1, const char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(int i, int j) {
    void *temp;
    
    temp = propers[i];
    propers[i] = propers[j];
    propers[j] = temp;

    temp = strings[i];
    strings[i] = strings[j];
    strings[j] = temp;
}

char* strclone(const char *s) {
    char *out, *buf = malloc(strlen(s) + 1);
    out = buf;

    while ((*buf++ = *s++) != '\0')
        ;

    return out;
}
