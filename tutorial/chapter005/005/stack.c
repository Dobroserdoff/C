#include "str.h"

extern unsigned int strp;
extern char str[MAXVAL][MAXLENGTH];
extern char buf[];

void push(char *s) {
	int i = 0;
	char *t;

	t = &str[strp++][0];

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

char pop(void) {
	if (strp)
		return str[strp--];
	
	else
		printf("pop error: stack is empty\n");
}