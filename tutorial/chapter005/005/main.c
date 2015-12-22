#include <stdio.h>
#include <stdlib.h>
#include "str.h"

int n = 0, i, strp = 0; 
int strmark[MAXVAL];
char buf[MAXLENGTH], str[MAXLENGTH];

int main()
{
    int type;
    strmark[strp] = 0;
           
    while ((type = getop()) != EOF)
    {
        if (strp < 2)
            printf("error: insufficient data to operate");
        else {
            switch (type)
            {
                case COPY:
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
                    break;
                case STRING:
                    printf("%s", str);
                default:
                    printf("main error: unknown command");
                    break;
            }
        }
    }
    return 0;
}

