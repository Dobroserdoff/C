#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

void expand(char s1[]);

main()
{
    int c, i = 0, j = 0;
    char s1[MAX], s2[MAX];

    while ((c = getchar()) != EOF)
    {
        s1[i] = c;
        i++;
        
        if (c == '\n')
        {
            s1[i] = '\0';
            expand(s1);
            i = 0;
        }    
    }
}   

void expand(char s1[])
{
    int i, j;
    char limleft, limright, before[MAX], after[MAX], s2[MAX];

    for(i = 0; i < strlen(s1); i++)
    {
        if (s1[i] == '-' && s1[i - 1] != ' ' && s1[i + 1] != ' ')
        {
            limleft = s1[i - 1];
            limright = s1[i + 1];
            
            if (limleft < limright)
                for (j = 0; j <= (limright - limleft); j++)
                    s2[j] = limleft + j;
            else
                for (j = 0; j <= (limleft - limright); j++)
                    s2[j] = limleft - j;
            
            before[i - 1] = '\0';
            s2[j - 1] = '\0';
            
            for (j = 0; j <= (strlen(s1) - (i + 1)); j++)
                after[j] = s1[(i + 1) + j];

            expand(strcat(strcat(before, s2), after));
        }
            before[i] = s1[i];
    }
    printf("%s", s1);
    exit(0);
}
