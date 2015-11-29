#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

main()
{
    printf("Range of char from standart library:\n");
    printf("Char min: %d, max: %d\n", CHAR_MIN, CHAR_MAX);
    printf("Signed char min: %d, max: %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned char min: %d, max: %d\n", 0, UCHAR_MAX);

    printf("\nRange of char by direct computing:\n");
    printf("Char min: %G, max: %G\n", (0 - (pow(2, 8) / 2)), (pow(2, 8) / 2 - 1));
    printf("Signed char min: %G, max: %G\n", (0 - (pow(2, 8) / 2)), (pow(2, 8) / 2 - 1));
    printf("Unsigned char min: %d, max: %G\n", 0, (pow(2, 8) - 1));

    printf("\nRange of short from standart library:\n");
    printf("Signed short min: %d, max: %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short min: %d, max: %d\n", 0, USHRT_MAX);

    printf("\nRange of short by direct computing:\n");
    printf("Signed short min: %G, max: %G\n", (0 - (pow(2, 16) / 2)), (pow(2, 16) / 2 - 1));
    printf("Unsigned short min: %d, max: %G\n", 0, (pow(2, 16) - 1));

    printf("\nRange of int from standart library:\n");
    printf("Signed int min: %u, max: %u\n", INT_MIN, INT_MAX);
    printf("Unsigned int min: %d, max: %u\n", 0, UINT_MAX);

    printf("\nRange of int by direct computing:\n");
    printf("Signed int min: %.0lf, max: %.0lf\n", (0 - (pow(2, 32) / 2)), (pow(2, 32) / 2 - 1));
    printf("Unsigned int min: %d, max: %.0lf\n", 0, (pow(2, 32) - 1));

    printf("\nRange of long from standart library:\n");
    printf("Signed long min: %ld, max: %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long min: %d, max: %lu\n", 0, ULONG_MAX);

    printf("\nRange of long by direct computing:\n");
    printf("Signed long min: %.0Lf, max: %.0Lf\n", (0 - (powl(2, 64) / 2)), (powl(2, 64) / 2) - 1);
    printf("Unsigned long min: %d, max: %.0Lf\n", 0, (powl(2, 64) - 1));
}
