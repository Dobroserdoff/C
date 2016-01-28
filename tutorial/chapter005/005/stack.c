#include "str.h"

extern int strp;
extern char str[MAXVAL][MAXLENGTH];
extern char buf[];

void push(char *s) {
	int i = 0;
	char *t = &str[strp++][0];

	if (strp < MAXVAL) {
		while ((*t++ = *s++) != '\n')
			i++;
		*t = *s;
	}

	else
		printf("push error: stack is full");

	while (i-- > 0)
		buf[i] = '\0';
}