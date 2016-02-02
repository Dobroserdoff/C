#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLENGTH 1000 /* max size of stack element */
#define STRING '0' /* signal that a string was found */
#define COPY '1' /* signal to copy strings */
#define COMPARE '2' /* signal to compare strings */
#define CONCATENATE '3' /* signal to concatenate strings*/
#define INDEX '4' /* signal to find the first position of additional piece in string */
#define SORT '5' /* signal to sort stack */
#define DELETE '6' /* signal to delete the last string  in stack */
#define COMPUTE '7' /* signal to compute the last string in stack */
#define REVERSE '8' /* signal to reverse the last string in stack */
#define MAXVAL 50 /* max depth of value stack */
#define MAXNUM 10 /* max digits of n */

int getop();
void push();
void strncp();
int strncm();
void strnct();
void strnidx();
void strnsort();
void strndel();
void strncomp();
void strnrev();

