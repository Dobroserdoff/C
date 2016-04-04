#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int c;
    char *a;
    a = argv[0];
        
    while (!isalpha(*a++))
        ;
    
    if (isupper (*a)) {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    }
    else {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    }

    return 0;
}
