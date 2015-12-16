#include <stdio.h>

#define MAX 100

void strconcat(char *s, char *t);

char s[MAX];

int main() {
    int c, first = 1;
    char *s, *t;

    while ((c = getchar()) != EOF || c != '\n')
        if (first)
            *s++ = c;
    *s = '\0';
    printf("%s", s - 3);
}
            /* if (c == '\n') {
                *s = '\0';
                first = 1;
                printf("%s", s);
            }
        }
        else
            return 0;
    }
}
        else { 
            *t++ = c;
            if (c == '\n') {
                *t = '\0';
                s[0] = strconcat(*s, *t);
            }
        }
    }
    printf("%s", *s);
}

void strconcat(char *s, char *t) {
    int i = 0;
    
    while (*s++ != '\0')
        i++;

    while (*t != '\0')
        (s[0] + i++) = *t++;
    
    (s[0] + i) = '\0';
}*/
