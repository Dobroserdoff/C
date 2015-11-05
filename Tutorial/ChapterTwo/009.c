#include <stdio.h>

main()
{
 unsigned x = 63;
 int b;

 for (b = 0; x != 0; ++b)
    x >>= 1;

 printf ("%d", b);
}
