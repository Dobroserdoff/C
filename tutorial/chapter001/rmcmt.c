#include <stdio.h>

#define MAXLENGTH 1000

void fixline (char s[], int p[]);

main ()
{
    int i, j, k, c;
    char line[MAXLENGTH];
    int slash[MAXLENGTH];
    j = k = 0;
    slash[0] = -1;

    while ((c = getchar()) != EOF)
    {
        line[i] = c;
        ++i;

        if (c == '/')
        {
            slash[j] = i - 1;
            ++j;
            slash[j]= -1;
        }
        else if (c == '\n')
        {
            if (k == 0)
            {
                printf ("%c", '\n');
                k = 1;
            }
            line[i] = '\0';
            fixline (line, slash);
            i = j = 0;
            slash[0] = -1;
         }
    }
}

void fixline (char line[], int slash[])
{
    int i, j, k, l;
    int direct[MAXLENGTH];
    j = k = l = 0;

    for (i = 0; i < MAXLENGTH; ++i)
        direct[i] = 0;

    while (slash[j] != -1)
    {
        if (slash[j] != 0 && line[slash[j] - 1] == '*')
        {
            direct[k] = -1;
            direct[k + 1] = slash[j];
            k = k + 2;
        }
        
        else if (line[slash[j] + 1] == '*')
        {
            direct[k] = 1;
            direct[k + 1] = slash[j];
            k = k + 2;
        }
        ++j;
    }
    
    while (direct[l] != 0)
    {
        if (direct[l] == 1 && direct[l + 2] == -1)
        {
            for (i = direct[l + 1]; i <= direct[l + 3]; ++i)
                line[i] = ' ';
            l = l + 4;
        }
        
        else if (direct[l] == 1)
        {
            for (i = direct[l + 1]; i < MAXLENGTH; ++i)
                while (line[i] != '\0')
                    line[i] = ' ';
            l = l + 2;
        }

        else if (direct[l] == -1)
        {
            for (i = direct[l + 1]; i >= 0; --i)
                line[i] = ' ';
            l = l + 2;
        }
    }
    printf("%s", line);
}
