#include <stdio.h>
#include <string.h>

#define MAXSTR 150

FILE * open_file(char *, char *, char *);

int main(int argc, char *argv[]) {
    int i, j = 2;
    FILE *first_fp, *second_fp;
    char first_str[MAXSTR], second_str[MAXSTR], buffer[MAXSTR], *temp;
    
    while (--argc > 1) {
        first_fp = open_file(argv[0], argv[1], "r");
        second_fp = open_file(argv[0], argv[j++], "r");
        
        for (i = 1; (temp = fgets(buffer, MAXSTR, first_fp)) != NULL; i++) {
            strcpy(first_str, temp);
            temp = fgets(buffer, MAXSTR, second_fp);
            strcpy(second_str, temp);
            
            if (strcmp(first_str, second_str) != 0) {
                printf("Files %s and %s different at string no %d: \n%s%s", argv[1], argv[j - 1], i, first_str, second_str);
                goto error;
            }
        }

        printf("Files %s and %s are identical\n", argv[1], argv[j - 1]);

        error:

        fclose(first_fp);
        fclose(second_fp);
    }

    return 0;
}

FILE * open_file(char * run, char *name, char *mode) {
    FILE *fp;

    if ((fp = fopen(name, mode)) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", run, name);
        return NULL;
    }

    return fp;
}
