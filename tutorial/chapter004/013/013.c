#include <stdio.h>

#define MAXLENGTH 100 /* maximum length of a input string */

void reverse (char s[]);

char result[MAXLENGTH];
int resp = 0;

int main() {
    int c, i = 0;
    char s[MAXLENGTH];

    while ((c = getchar()) != EOF) {
        s[i++] = c;
        if (c == '\n') {
            reverse(s);
            printf("\n");
            i = 0;
        }
    }
    /*
    if (c == EOF) {
        s[i] = '\n';
        reverse(s);    
    }*/
}

void reverse (char s[]) {
    int j, k = 0;
    char temp[MAXLENGTH];

    if (s[1] != '\n') {
        for (j = 1; s[j] != '\n'; j++)
            temp[k++] = s[j];
        
        temp[k] = '\n';
        reverse(temp);
    }

    printf("%c", s[0]);
}
