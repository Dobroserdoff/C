#include <stdio.h>

main()
{
    unsigned x;
    int n;

    x =211;
    n = 3;

    printf("For x = %u, n = %d, result = %u\n", x, n, x >> n);
}
