#include "str.h"

unsigned int n = 0, strp = 0;
char buf[MAXLENGTH], str[MAXVAL][MAXLENGTH];

int main() {
	int type;

	while ((type = getop()) != EOF) {
		switch (type) {
			/*case COPY:
			strncp();
			break;
			case COMPARE:
			strncm();
			break;
			case CONCATENATE:
			strnct();
			break;
			case DELETE:
			strndel();
			break;*/
		case STRING:
			push(buf);
			break;
		default:
			printf("main error: unknown command");
			break;
		}
	}
	return 0;
}