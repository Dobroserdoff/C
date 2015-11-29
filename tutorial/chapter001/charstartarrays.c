#include <stdio.h>

 main()
 {
 int c, i, j, k, nwhite, nother, state, max;
 int ndigit[10];
 char alphabet[26], storage[26];
 nwhite = nother = k = max = 0;

 for (i = 0; i < 10; ++i)
 ndigit[i] = 0;
 
 for (j = 0; j < 26; ++j) {
  alphabet[j] = 'a' + j;
  storage[j] = 0;
  }

 while ((c = getchar()) != EOF) {
  if (c >= '0' && c <= '9')
   ++ndigit[c-'0'];

  else if (c == ' ' || c == '\n' || c == '\t')
   ++nwhite;

  else {
   if (c >= 'a' && c <= 'z')
    ++storage[c-'a'];
   ++nother;
   }
  }

 printf("\ndigits =");
 for (i = 0; i < 10; ++i)
  printf(" %d", ndigit[i]);

 printf(", white space = %d, other = %d\n", nwhite, nother);

 for (j = 0; j < 26; ++j)
  if (storage[j] > max)
   max = storage[j];

 printf("Letters = ");
 for (i = 0; i < 26; ++i)
     printf("%5d", storage[i]);
 printf("\nMax = %d\n", max);

 for (k = max; k > 0; --k) {
  for (j = 0; j < 26; ++j) {
   if (storage[j] >= k)
    printf("  |");
   else
    printf("   ");
   }
  printf("\n");
  }

 for (j = 0; j < 26; ++j) {
  printf("  %c", alphabet[j]);
  }
 printf("\n");
 }
