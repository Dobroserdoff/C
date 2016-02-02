#include "str.h"

extern int strp;
extern char buf[], *bufp, dump[MAXVAL][MAXLENGTH], *str[];

void push() {
	char *s = &dump[strp][0];
	bufp = &buf[0];

	if (strp < MAXVAL) {
		while ((*s++ = *bufp++) != '\n')
			;
		*s = *bufp;
	}
	else {
		printf("push error: stack is full");
		strp--;
	}

	str[strp] = &dump[strp++][0];

	bufp = &buf[0];
	while (*bufp)
		*bufp++ = '\0';
	bufp = &buf[0]; 
}