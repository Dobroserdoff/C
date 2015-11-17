#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 100
 
main()
{
    double sum, val, atof(char []);
    char line[MAXLINE];
    int checkline(char line[], int max);
    sum = 0;

    while (checkline(line, MAXLINE) > 0)
        printf("Value: %f, Summary:%f\n", val, sum += (val = atof(line)));

    return 0;
}

double atof(char s[])
{
    double val, power, result;
    int i, sign, esign = 1;

    for (i = 0; isspace(s[i]); i++)
            ;
    sign = (s[i] == '-') ? -1 : 1;
    
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
    {
        i++;
 
        for (power = 1.0; isdigit(s[i]); i++)
        {
            val = 10.0 * val + (s[i] - '0');
            power *= 10;
        }
        val = val / power;
    }
    
    if (s[i] == 'e' || s[i] == 'E')
    {
        if (isdigit(s[i + 1]))
            i++;

        else if (s[i + 1] == '-')
        {
            esign = -1;
            i += 2;
        }
        else
            i += 2;

        for (power = 0.0; isdigit(s[i]); i++)
            power = 10.0 * power + (s[i] - '0');
        
        val = val * (pow(10, esign * power)); 
    }
    return sign * val;
}

int checkline(char s[],int lim)
{
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[++i] = c;

    s[i] = '\0';
    return i;
}
