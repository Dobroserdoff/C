#include <stdio.h>

main()
{
int c;

while((c = getchar()) != EOF)
    (c >= 'A' && c <= 'Z') ? putchar(c + 'a' - 'A') : putchar(c);
}
