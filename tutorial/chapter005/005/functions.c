#include "str.h"

extern int strp, n;
extern char str[MAXVAL][MAXLENGTH];

void strncp() {
	char *t = &str[strp - 1][0];
	char *r = &str[strp - 2][0];

	if (n == -1)
		n = strlen(r);
	
	while (n-- > 0 && *r != '\n')
		*t++ = *r++;

	printf("copy result: %s", str[strp - 1]);
}

void strncm() {
	char *t = &str[strp - 1][0];
	char *r = &str[strp - 2][0];

	if (n == -1)
		n = strlen(r);

	while (*t++ == *r++ && n-- > 0)
		if (*r == '\n')
			break;

	if (*--r == *--t || *r == '\n')
		printf("compare result: 0\n");
	else
		printf("compare result: %d\n", *r - *t);
}

void strnct() {
	char *t = &str[strp - 1][0];
	char *r = &str[strp - 2][0];
	char q[MAXLENGTH], *qp;

	qp = &q[0];

	if (n == -1)
		n = strlen(r);

	while (n-- > 0 && *r != '\n')
		*qp++ = *r++;

	while ((*qp++ = *t++) != '\n')
			;
	
	*qp = '\0';
	strp--;
	push(q);

	printf("concatenation result: %s", str[strp - 1]);
}

void strndel() {
	if (n == -1 || n >= strlen(str[strp - 1]))
		str[--strp][0] = '\0';
	else {
		str[strp - 1][strlen(str[strp - 1]) - (n + 1)] = '\n';
		str[strp - 1][strlen(str[strp - 1]) - (n)] = '\0';
    }

	printf("top stack position after deletion: %s", str[strp - 1]);
}
