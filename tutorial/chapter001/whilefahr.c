#include <stdio.h>

/*Print fahrenheit to celsius and celsius to fahrenheit
conversion tables using "while" loop*/

#define LOWER 0 /*Lower limit of table*/
#define UPPER 300 /*Upper limit of table*/
#define STEP 20 /*Step size*/

 main()
 {

 int row;
 float fahr, celsius;

 fahr = LOWER;
 row = 1;
 printf("Farenheit to celsius conversion table\n");

 while (fahr <= UPPER)
     {
     celsius = 5.0 / 9.0 * (fahr-32.0);
     printf("%2d\t%5.1f\t%5.1f\n", row, fahr, celsius);
     fahr = fahr + STEP;
     row = row + 1;
     }

 celsius = LOWER;
 row = 1;
 printf("Celsius to farenheit conversion table\n");

 while(celsius <= UPPER)
     {
     fahr = 9.0 / 5.0 * (celsius) + 32.0;
     printf("%2d\t%5.1f\t%5.1f\n", row, celsius, fahr);
     celsius = celsius + STEP;
     row = row + 1;
     }
 }
