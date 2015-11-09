#include <stdio.h>

#define MAX 100

main()
{
    int c, i = 0;
    char s[MAX];
    void escape(char s[]);

    while ((c = getchar()) != '\n')
    {
        s[i] = c;
        i++;
    }

    s[i] = '\n';
    s[i + 1] = '\0';
    escape(s);
}

void escape (char s[])
{
    int c, i, j = 0;
    char t[MAX];

    for (i = 0; i < MAX; i++)
        switch (s[i])
        {
            case '\t':
                t[j] = '\\';
                t[j + 1] = 't';
                j += 2;
                break;
            case '\n':
                t[j] = '\\';
                t[j + 1] = 'n';
                j += 2;
                break;
            default:
                t[j] = s[i];
                j++;
                break;
        }
    printf("%s", t);    
}
