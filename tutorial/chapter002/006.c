#include <stdio.h>

main()
{
    unsigned x, xin, xout, y, z, result;
    int p, n;

    x = 101;
    y = 179;
    p = 4;
    n = 3;
    z = ((y >> (p + 1 - n)) & ~(~0 << n)) << (p + 1 - n);
    xin = (x >> p + 1) << (p + 1);
    xout = x & ~(~0 << (p + 1 - n));
    result = xin | z | xout;

    printf("For x = %u, y = %u, p = %d, n = %d, z = %u, xin = %u, xout = %u; result = %u\n", x, y, p, n, z, xin, xout, result);

    
}
