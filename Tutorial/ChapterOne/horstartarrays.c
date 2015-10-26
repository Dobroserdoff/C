#include <stdio.h>

 #define IN 1 /*inside a word*/
 #define OUT 0 /*ouside a word*/

 /* count digits, white space, others */

 main()
 {
 int c, i, j, k, nwhite, nother, state, lenght;
 int ndigit[10];
 int wordlenght[100];
 nwhite = nother = lenght = k = 0;
 state = OUT; 

 for (i = 0; i < 10; ++i)
 ndigit[i] = 0;

 for (j = 0; j < 100; ++j)
 wordlenght[j] = 0;

 while ((c = getchar()) != EOF) {
  if (c >= '0' && c <= '9')
  ++ndigit[c-'0'];

  else if (c == ' ' || c == '\n' || c == '\t') {
   ++nwhite;
   if (state == IN) {
    wordlenght[k] = lenght;
    ++k;
    lenght = 0;
    state = OUT;
    }
   }

  else {
   ++nother;
   ++lenght;
   state = IN;
   }
  }
 
 printf("\ndigits =");
 for (i = 0; i < 10; ++i)
  printf(" %d", ndigit[i]);
 
 printf(", white space = %d, other = %d\n", nwhite, nother);

 for (j = 0; j < 100; ++j) {
  if (wordlenght[j] != 0) {
   printf("%3d ", wordlenght[j]);
   for (k = wordlenght[j]; k > 0; --k)
    printf("-");
   printf("\n");
   } 
  }
 }
