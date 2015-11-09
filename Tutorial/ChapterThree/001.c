#include <stdio.h>

#define MAX 100

main()
{
    int i, res;
    int v[MAX];
    int x = 51;
    
    for (i = 0; i < MAX; i++)
        v[i] = i;

    res = binsearch(x, v);

    if (res == x)
        printf("x = %d\n", res);
    else
        printf("Cannot find x in array\n");
}        
int binsearch(int x, int v[])
{
    int low, high, mid;
    low = 0;
    high = MAX;

    while (high - low > 1)
        {
        mid = (low+high)/2;
        printf("%d, %d, %d\n", low, mid, high);
        if (x < v[mid])
            high = mid;
        else
            low = mid;
        }
    printf("%d, %d, %d\n", low, high, (low + high)/2);
    return (high + low)/2;
}
