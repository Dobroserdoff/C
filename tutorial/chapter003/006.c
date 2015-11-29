#include <stdio.h>
#include <string.h>

void reverse(char st[]);

main()
{
    int i, l, sign = 0;
    char s[100];
    signed short sn = -32768;
    unsigned short un;
    l = 3;

    if (sn < 0)
        un = -sn;
    else
    {
        sign = 1;
        un = sn;
    }
    i = 0;

    do
        s[i++] = un % 10 + '0';
    while ((un /= 10) > 0);
     
    if (sign == 0)
        s[i++] = '-';
    
    s[i] = '\0';

    if (strlen(s) > l)
        printf("Error: Field overflow");
    else
    {
        while (strlen(s) <= l)
            s[i++] = ' ';
        s[i] = '\0';
        reverse(s);
    }
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
