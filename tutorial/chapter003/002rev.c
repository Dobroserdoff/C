#include <stdio.h>

#define MAX 100

main()
{
    int c, i = 0;
    char s[MAX];
    void reverse(char s[]);

    while ((c = getchar()) != '\n')
    {
        s[i] = c;
        i++;
    }

    s[i] = '\n';
    s[i + 1] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j = 0;
    char t[MAX];

    for (i = 0; i < MAX; i++)
        switch (s[i])
        {
            case '\\':
                switch (s[i + 1])
                {
                    case 't':
                        t[j] = '\t';
                        j++;
                        i++;
                        break;
                    case 'n':
                        t[j] = '\n';
                        j++;
                        i++;
                        break; 
                }
                break;
            default:
                t[j] = s[i];
                j++;
                break;
        }
    printf("%s", t);    
}
