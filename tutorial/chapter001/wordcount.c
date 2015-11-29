#include <stdio.h>

 #define IN 1 /* inside a word */
 #define OUT 0 /* outside a word */

 /* count lines, words, and characters in input */

 main()
 {
 int c, nl, nw, nc, state;
 state = OUT;
 nl = nw = nc = 0;
 
 while ((c = getchar()) != EOF) {
  ++nc;
  if (c == '\n')
  ++nl;
  if (c == ' ' || c == '\n' || c == '\t') {
  state = OUT;
  putchar(12);
  }
  else if (state == OUT) {
   state = IN;
   ++nw;
   }
  putchar(c);
  }
 printf("\n%d lines, %d words, %d characters\n", nl, nw, nc);
 }
