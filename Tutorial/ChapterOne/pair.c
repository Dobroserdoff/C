#include <stdio.h>

#define MAXLENGTH 10000

int oparent, obracket, obrace, osingle, odouble, ocmt;
int cparent, cbracket, cbrace, csingle, cdouble, ccmt;
int singleflag, doubleflag;
int wholetext[MAXLENGTH];

main()
{
    int c, i;
    oparent = obracket = obrace = osingle = odouble = ocmt = 0;
    cparent = cbracket = cbrace = csingle = cdouble = ccmt = 0;
    i = singleflag = doubleflag = 0;

    while ((c = getchar()) != EOF)
    {
        wholetext[i] = c;
        ++i;

        if (c == '(')
            ++oparent;
        else if (c == '[')
            ++obracket;
        else if (c == '{')
            ++obrace;
        else if (c == 39 && singleflag == 0)
        {
            ++osingle;
            singleflag = 1;
        }
        else if (c == 34 && doubleflag == 0)
        {
            ++odouble;
            doubleflag = 1;
        }
        else if (i != 1 && c == '*' && wholetext[i - 2] == '/')
            ++ocmt;
        else if (c == ')' )
            ++cparent;
        else if (c == ']')
            ++cbracket;
        else if (c == '}')
            ++cbrace;
        else if (c == 39 && singleflag == 1)
        {
            ++csingle;
            singleflag = 0;
        }
        else if (c == 34 && doubleflag == 1)
        {
            ++cdouble;
            doubleflag = 0;
        }
        else if (i != 1 && c == '/' && wholetext[i - 2] == '*')
            ++ccmt;
    }
    printf("%c", '\n');

    if (oparent == cparent)
        printf("Parentheses OK: open %d, close %d\n", oparent, cparent);
    else
        printf("Parentheses unmatch: open %d, close %d\n", oparent, cparent);
    
    if (obracket == cbracket)
        printf("Brackets OK: open %d, close %d\n", obracket, cbracket);
    else
        printf("Brackets unmatch: open %d, close %d\n", obracket, cbracket);
    
    if (obrace == cbrace)
        printf("Braces OK: open %d, close %d\n", obrace, cbrace);
    else
        printf("Braces unmatch: open %d, close %d\n", obrace, cbrace);

    if (osingle == csingle)
        printf("Single quotes OK: open %d, close %d\n", osingle, csingle);
    else
        printf ("Single quotes unmatch: open %d, close %d\n", osingle, csingle);

    if (odouble == cdouble)
        printf("Double quotes OK: open %d, close %d\n", odouble, cdouble);
    else
        printf ("Double quotes unmatch: open %d, close %d\n", odouble, cdouble);

    if (ocmt == ccmt)
        printf("Comments OK: open %d, close %d\n", ocmt, ccmt);
    else
        printf("Comments unmatch: open %d, close %d\n", ocmt, ccmt);
}
