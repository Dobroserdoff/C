#include <stdio.h>

 /* copy input to output */

 main()
 {

 /* Proof that (getchar() != EOF) is boolean*/
 /* while (getchar() != EOF)
     {
     printf("%d\n", getchar() != EOF);
     }
 printf("%d\n", getchar() != EOF); */

 int c;
 
 while ((c = getchar()) != EOF)
     putchar(c);
 }
