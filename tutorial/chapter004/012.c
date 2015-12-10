#include <stdio.h>

#define MAX 10 /* maximum length of an integer */

void itoa(int i);
int j = 0;

char s[MAX];

int main() {
    int i = -987654321;
    
    if (i < 0) {
        s[j++] = '-';
        i = -i;
    }
    
    itoa(i);
    
    printf ("%s\n", s);

return 0;
}

void itoa(int i) { 
    if (i / 10)
        itoa(i / 10);
    
    s[j++] = i % 10 + '0';
    s[j] = '\0';
}
