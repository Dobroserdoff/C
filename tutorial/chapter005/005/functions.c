#include "str.h"

void strncp() {
	char *t = &str[--strp];
	char *r = &str[--strp];

	while (n-- > 0 && *t != '\n')
		*r++ = *t++;

	printf("%s", str);
}

void strncm() {
	char *t = &str[--strp];
	char *r = &str[--strp];

	for (n; *r++ == *t++, n > 0; n--)
		if (*t == '\n')
			break;

	if (*t == *r || *t == '\n')
		printf("Compare result: 0");
	else
		printf("Compare result: %d", *t - *r);
}

void strnct() {
	if (n > 2) {
		char *t, *r, *q;
		t = pop();
		r = pop();
		q = r;

		while (*r++ != '\n')
			;
		*r--;

		while (n-- >= 0)
			if ((*r++ = *t++) == '\n')
				break;

		*r = '\0';
		printf("Q - %s", q);
		push(q);

		printf("%s", str);
	}
	else
		printf("concatenation error: insufficient data to operate");
}

void strndel() {
	if (n != 0) {
		str[strp - 1][-1 - n] = '\0';
		str[strp - 1][-2] = '\n';
	}

	else
		pop();
}