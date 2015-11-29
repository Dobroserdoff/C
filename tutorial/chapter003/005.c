#include <stdio.h>
#include <string.h>

void reverse (char s[]);

main()
{
    int i, c, x, y;
    char s[100];
    x = 438;
    y = 2;
    i = 0;

    while(x != 0)
    {
       c = (x%y);
       x = (x/y);
       
       if (c == 10)
           s[i++] = 'A';
       else if (c == 11)
           s[i++] = 'B'; 
       else if (c == 12)
           s[i++] = 'C'; 
       else if (c == 13)
           s[i++] = 'D';
       else if (c == 14)
           s[i++] = 'E';
       else if (c == 15)
           s[i++] = 'F';
       else
           s[i++] = c + '0';
    }

    s[i] = '\0';
    reverse(s);
}   

void reverse (char s[])
{
    int c, i, j;
 
    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

    printf("%s", s);
}
