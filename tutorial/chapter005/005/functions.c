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
		str[strp - 1][strlen(str[strp - 1]) - n] = '\0';
	}

	printf("top stack position after deletion: %s", str[strp - 1]);
}

void strncomp() {
	char *t = &str[strp - 1][0];
	int i = 0;

	while (*t++ != '\n')
		i++;

	printf("top stack position length: %d\n", i);
}

void strnrev() {
	char temp[MAXLENGTH];
	char *t = &temp[0];
	char *r = &str[strp - 1][strlen(str[strp - 1]) - 2];

	while (*t++ = *r--)
		;
	*(--t) = '\n';
	*(++t) = '\0';

	printf("reverse result: %s", temp);
}

void strnidx() {
	int i, j = 0, k = 1;
	char *t = &str[strp - 1][0];
	char *r = &str[strp - 2][0];

	for (i = 0; *r; i++) {
		while (*r++ == *t && *t != '\0') {
			j++;
			*t++;
			if (*t == '\n') {
				printf("search result: %d\n", i);
				k = 0;
				i += j - 1;
				j = 0;
				t = &str[strp - 1][0];
				break;
			}
			else if (*r != *t) {
				i += j - 1;
				j = 0;
				t = &str[strp - 1][0];
			}
		}
	}

	if (k)
		printf("search result: none\n");
}