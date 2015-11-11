#include <stdio.h>
#include <math.h>

#define MAXNUM 10
#define MAXSTR 100

main()
{
    int i, j, k, c, a, num[MAXNUM], sort[MAXSTR];
    i = j = 0;

    for (k = 0; k <= MAXSTR; k++)
    {
        sort[k] = 0;
        num[k] = 0;
    }

    while((c = getchar()) != '\n')
    {
        if (c != ' ')
        {
            num[i] = c - '0';
            i++;
        }
        else if (num[0])
        {
            for (k = 0; k <= MAXNUM; k++)
            {
                if (i)
                {
                    i--;
                    sort[j] += ((int) (pow(10, k))) * num[i];
                }
            }
            j++;
            num[0] = 0;
        }
    }
        if (num[0])
            for (k = 0; k <= MAXNUM; k++)
                if (i)
                {
                    i--;
                    sort[j] += tens[k] * num[i];
                }

    for (i = 1; sort[i]; i++)
    {
        a = sort[i];
        j = i;
        
        while (j > 0 && sort[j - 1] > a)
        {
            sort[j] = sort[j-1];
            j = j - 1;
        }
        sort[j] = a;
    }

    for (i = 0; sort[i]; i++)
        printf("%d ", sort[i]); 
}
