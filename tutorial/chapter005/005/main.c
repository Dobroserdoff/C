#include "str.h"

int n = 0, strp = 0;
char buf[MAXLENGTH], *bufp = &buf[0]; 
char dump[MAXVAL][MAXLENGTH];
char *str[MAXVAL];

int main() {
	int type, i = 0;

	while ((type = getop()) != EOF) {
		switch (type) {
			case COPY:
				if (strp > 1)
					strncp();
				else
					printf("copy error: insufficient data to proceed\n");
				break;
			case COMPARE:
				if (strp > 1)
					printf("compare result: %d\n", strncm(str[strp - 1], str[strp - 2]));
				else
					printf("compare error: insufficient data to proceed\n");
				break;
			case CONCATENATE:
				if (strp > 1)
					strnct();
				else
					printf("concatenate error: insufficient data to proceed\n");
				break;
			case INDEX:
				if (strp > 1)
					strnidx();
				else
					printf("index error: insufficient data to proceed\n");
				break;
			case SORT:
				if (strp > 1) {
					strnsort();
					printf("sort result:\n");
					i = strp;
					while (i)
						printf("%s", str[strp - i--]);
				}
				else
					printf("sort error: insufficient data to proceed\n");
				break;
			case DELETE:
				strndel();
				break;
			case COMPUTE:
				strncomp();
				break;
			case REVERSE:
				strnrev();
				break;
			case STRING:
				push();
				break;
			default:
				printf("main error: unknown command\n");
				break;
		}
	}
	return 0;
}