#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define STRING 10

int main(int argc, char *argv[]) {
    char *sp, s[STRING];
    int i, c;
    sp = &s[0];

    for (i = 0; (c = getchar()) != EOF; i++) {
        if (isspace(c) && i >= STRING) {
            c = '\n';
            i = 0;
        }

        else if (isdigit(c) && argc > 1) {
            *sp++ = c;
            while (isdigit(c = getchar()))
                *sp++ = c;
            *sp = '\0';
            
            if (strcmp(argv[1], "-o") == 0)
                printf("%o", atoi(s));
            
            else if (strcmp(argv[1], "-h") == 0)
                printf("%x", atoi(s));

            sp = &s[0];
        }
        putchar(c);
    }
    return 0;
}
