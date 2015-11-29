#include <stdio.h>

#define LIM 100
const char example[] = "for (i=0; i < lim-1 && (c=getchar()) != '\\n' && c != EOF; ++i)";

main()
{
    int i, j, c;
    int line[LIM];

    printf("%s\n", example);
    for (i = 0; i < LIM; ++i)
        if ((c = getchar()) != '\n')
            if (c != EOF)
                line[i] = c;
    for (j = 0; line[j] != 0; ++j)
        printf("%c", line[j]);

}
