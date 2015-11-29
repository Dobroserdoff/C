#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define MAXLENGTH 100

int hexline[MAXLENGTH];

main()
{
    int i, j, c;
    i = 0;

    for (j = 0; j < MAXLENGTH; ++j)
        hexline[j] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == 'x' || c == 'X')
            i = i - 1;
        else if (c == ' ')
            ;
        else
        { 
            hexline[i] = toupper(c);
            ++i;
        }
    }

    printf("\n");

    for (j = 0; hexline[j] != 0; ++j)
    {
        if (0 <= (hexline[j] - 'A') && (hexline[j] - 'A') < 6)
            printf("%d ", hexline[j] - 55);
        else
            printf("%d ", hexline[j] - 48);
    }
}
