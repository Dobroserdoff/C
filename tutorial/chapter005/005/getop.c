#include "str.h"

extern unsigned int strp, n;
extern char buf[];

int getop() {
	int a, b = 0, c, k = 0;
	char num[MAXNUM], *temp;

	temp = &buf[0];

	while ((c = getchar()) != EOF) {
		if (c == 'C' && isupper(b = getchar())) {
			while (isdigit(a = getchar()))
				num[k++] = a;
			num[k] = '\0';
			n = atoi(num);

			if (b == 'P')
				return COPY;
			else if (b == 'M')
				return COMPARE;
			else if (b == 'T')
				return CONCATENATE;
			else if (b == 'D')
				return DELETE;
		}

		else {
			*temp++ = c;
			if (b) {
				*temp++ = b;
				b = 0;
			}

			if (c == '\n') {
				*temp = '\0';
				return STRING;
			}
		}
	}
	return c;
}