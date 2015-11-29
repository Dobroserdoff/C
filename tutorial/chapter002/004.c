#include <stdio.h>

#define MAX 1000

char fixline[MAX];
char source[MAX];

void squeeze(char f[], char s[]);

main()
{
    int a, i, j, k, c;
    a = j = k = 0;

    for (i = 0; i < MAX; i++)
        fixline[i] = 0;
        source[i] = 0;

    while ((c = getchar()) != EOF)
        if (c != '\n' && a == 0)
            fixline[j++] = c;
        else if (c == '\n')
            a = 1;
        else if (c != '\n' && a == 1)
            source[k++] = c;
    squeeze(fixline, source);
    
    printf("\n");
    for (i = 0; fixline[i] != 0; i++)
        printf("%c", fixline[i]);
}

void squeeze(char f[], char s[])
{
    int i, j, k;
    for (k = 0; s[k] != 0; k++)
    {
        for (i = j = 0; f[i] != 0; i++)
            if (f[i] != s[k])
                f[j++] = f[i];
        f[j] = 0;
    }    
}
