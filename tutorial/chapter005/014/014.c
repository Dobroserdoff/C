#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINES 1000
#define MAX 120

char *strings[MAX];
int sp = 0;
int numeric = 0;
int reverse = 0;
int fold = 0;
int direct = 0;

int argcheck(char *);
void readinput(void);
void quicksort(void *strings[], int, int, int(*)(const void *, const void *));
int numcmp(const char *, const char *);
void swap(void *strings[], int, int);
char* strclone(const char *);

int main(int argc, char *argv[]) {
    int i;
    extern int sp;
    
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') && (argcheck(argv[i] + 1) == 0))
            ;
        else
            printf("invalid arguments: try once again\n");
    }
    readinput();

    if ((sp > 1) && (sp < MAXLINES))
        quicksort((void**)strings, 0, sp - 1, (int(*)(const void*, const void*))(numeric ? numcmp : strcmp));
    else {
        printf("input error\n");
        return 1;
    }

    printf("list of strings sorted with %s algorithm\n", numeric ? ("numeric") : ("string comparison"));

    for (i = 0; i < sp; i++) {
        printf("%s", strings[i]);
        free(strings[i]);
    }

    i = getchar();
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

void readinput(void) {
    int c;
    char *s, string[MAX];
    s = string;

    while ((c = getchar()) != EOF) {
        *s++ = c;
        if (c == '\n') {
            *s = '\0';
            strings[sp++] = strclone(string);
            s = string;
        }
    }
}

void quicksort(void *strings[], int left, int right, int(*comp)(const void *, const void *)) {
    int i, last;
    
    if (left >= right) 
        return; 

    swap(strings, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(strings[i], strings[left]) < 0)
            swap(strings, ++last, i);

    swap(strings, left, last);
    quicksort(strings, left, last - 1, comp);
    quicksort(strings, last + 1, right, comp);
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

void swap(void *strings[], int i, int j) {
    void *temp;
    
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
