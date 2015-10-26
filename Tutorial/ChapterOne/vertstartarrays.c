#include <stdio.h>

#define OUT 0
#define IN 1
 
 main()
 {
 int c, i, j, k, nwhite, nother, state, lenght, max;
 int ndigit[10];
 int wordlenght[50];
 nwhite = nother = lenght = k = max = 0;
 state = OUT; 

 for (i = 0; i < 10; ++i)
 ndigit[i] = 0;

 for (j = 0; j < 50; ++j)
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
 
 printf(", white space = %d, other = %d, ", nwhite, nother);

 for (j = 0; j < 49; ++j)
  if (wordlenght[j] > max)
   max = wordlenght[j];

printf("max word lenght = %d\n", max);
 
 for (k = max; k > 0; --k) {
  for (j = 0; j < 50; ++j) {
   if (wordlenght[j] > 0 && wordlenght[j] >= k)
    printf("  |");
   else 
    printf("   ");
   }
  printf("\n");
  }
 for (j = 0; j < 50; ++j)
  printf("%3d", wordlenght[j]);
 printf("\n");
 }
