#include <stdio.h>

/*Replace intends, backspaces and backslashes with it's visible form*/

main()
 {
 int a;
 a = 0;

 while ((a = getchar()) != EOF) {
  if (a == 9) {
   putchar(92);
   putchar(116);
   }
  else if(a == 8) {
   putchar(92);
   putchar(98);
   }
  else if (a == 92) {
   putchar(92);
   putchar(92);
   }
  else
   putchar(a);
  }
 putchar('\n');
 }
