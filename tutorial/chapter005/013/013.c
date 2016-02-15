#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 120

int argcheck(char *s);
char* strclone(const char* s);

int main(int argc, char *argv[]) {
    int i = 0, c, k, l = 0;
    int tail = 10;
    char *s, string[MAX], *strings[MAX];

    for (k = 1; k < argc; k++)
        if (*argv[k] == '-') {
            if (argcheck(++argv[k]) == 0)
                tail = atoi(argv[k]);
            else
                printf("input error: number of strings to print set to default\n");
        }
    s = &string[0];

    while ((c = getchar()) != EOF) {
        *s++ = c;
        if (c == '\n') {
            *s = '\0';
            strings[l++] = strclone(string);
            s = &string[0];
        }
    }

    if (l <= tail)
        tail = l;

    printf("list of %d last strings:\n", tail);
    while (tail--) {
        printf("%s", strings[((l - 1) - tail)]);
        free(strings[((l - 1) - tail)]);
    }
    return 0;
}

int argcheck(char *s) {
    unsigned int i;
    char *out;
    out = s;

    for (i = 0; i < strlen(out); i++)
        if (!isdigit(*s++))
            return 1;
    return 0;
}

char* strclone(const char *s) {
    char *out, *buf = malloc(strlen(s) + 1);
    out = buf;

    while ((*buf++ = *s++) != '\0')
        ;
    *buf = '\0';

    return out;
}  
