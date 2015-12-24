#include <stdio.h>
#include <stdlib.h>
#include "str.h"

int n = 0, i, strp = 0; 
char buf[MAXLENGTH];
char *str[MAXVAL];

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
                strncd();
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

