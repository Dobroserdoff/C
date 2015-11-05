#include <stdio.h>
#include <limits.h>

main()
{
    unsigned x, y, z;
    int n;

    x = 215;
    n = 3;
    y = (x & ~(~0 << n)) << UINT_MAX - n + 1;
    z = y ^ (x >> n);

    printf("For x = %u, n = %d, result = %u\n", x, n, z);
}
