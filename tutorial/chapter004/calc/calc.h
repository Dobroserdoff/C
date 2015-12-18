#include <stdio.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1' /* signal that a command was found */
#define FUNCTION '2' /* signal that function was found */
#define VARIABLE '3' /* signal that variable was found */
#define MAXVAL 100 /* max depth of value stack */

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


