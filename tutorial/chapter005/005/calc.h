#include <stdio.h>

#define MAXLENGTH 1000 /* max size of stack string */
#define STRING '0' /* signal that a string was found */
#define COPY '1' /* signal to copy strings */
#define COMPARE '2' /* signal to compare strings */
#define CONCATENATE '3' /* signal to concatenate */
#define MAXVAL 50 /* max depth of value stack */
#define MAXNUM 10 /* max digits of n */

int getop(char []);
void push(double);
double pop(void);
double modulus(double a, double b);
void function (char []);
void command (char []);
void variable(char []);
void comprint(int);
void comduplicate(int);
void comswap(void);
void comclear(void);


