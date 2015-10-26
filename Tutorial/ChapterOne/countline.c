#include <stdio.h>

 /* count lines, spaces and tabs in input */

 main()
 {
 int c, nl, space, tab;
 nl = 0;
 space = 0;
 tab = 0;

 while ((c = getchar()) != EOF) {
  if (c == '\n')
   ++nl;
  if (c == ' ')
   ++space;
  if (c == '\t')
   ++tab;
  }
 printf("%d lines, %d spaces, %d tabs\n", nl, space, tab);
 }
