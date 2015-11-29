#include <stdio.h>

#define MAX 1000

char fixline[MAX];
char source[MAX];

int position(char f[], char s);

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

    printf("\n");

    for (i = 0; source[i] != 0; i++)
        printf("For %c the first position is %d\n", source[i], position(fixline, source[i]));
}

int position(char f[], char s)
{
    int i, pos;
    pos = -1;

    for (i = 0; f[i] != 0; i++)
        if (f[i] == s)
        {
            pos = i;
            return pos;
        }
    return pos;
}
