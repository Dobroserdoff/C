#include "str.h"

int n = 0, strp = 0;
char buf[MAXLENGTH], str[MAXVAL][MAXLENGTH];

int main() {
	int type;

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
					strncm();
				else
					printf("compare error: insufficient data to proceed\n");
				break;
			case CONCATENATE:
				if (strp > 1)
					strnct();
				else
					printf("compare error: insufficient data to proceed\n");
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
				push(buf);
				break;
			case INDEX:
				if (strp > 1)
					strnidx();
				else
					printf("index error: insufficient data to proceed\n");
				break;
			default:
				printf("main error: unknown command\n");
				break;
		}
	}
	return 0;
}