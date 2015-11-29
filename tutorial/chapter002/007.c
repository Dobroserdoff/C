#include <stdio.h>

main()
{
    unsigned x, xin, xout, z, result;
    int p, n;

    x =2111;
    p = 6;
    n = 3;
    xin = (x >> p + 1) << (p + 1);
    xout = x & ~(~0 << (p + 1 - n));
    z = (~(x >> (p + 1 - n)) & ~(~0 << n)) << (p + 1 -n);

    result = xin | z | xout;

    printf("For x = %u, p = %d, n = %d, z = %u, xin = %u, xout = %u; result = %u\n", x, p, n, z, xin, xout, result);
}
