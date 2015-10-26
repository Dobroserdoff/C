#include <stdio.h>

#define MAXLINE 1000

void clearesc(char m[],int l);
void clearspc(char n[],int k);

main() {
 char line[MAXLINE];
 int c, i;

 while((c=getchar())!=EOF) {
    for (i=0; i<=MAXLINE; ++i)
        line[i] = c;
        if (c == '\n') {
            clearesc(line, i);
            clearspc(line, i);
            printf("\n%s", line);
        }
 }
 }

 void clearesc(char line[], int lim) {
     int j;

     for (j=0; j<lim; ++j)
        if (line[j] == '\t')
            line[j] = ' ';
 }
 
 void clearspc(char line[], int lim) {
    int k, l, m, b, list[lim];
    b = l = 0; 
                                              
    for (k=0; k<lim; ++k) {
        if (line[k] == ' ') {
            if (b == 0)
                b = 1;
            else {
               list[l] = k;
               ++l;
            }
        }
        else 
            b = 0;      
    }
    /*line[lim+1] = '\0';*/

    for (list[l = 0]; l < lim; ++l)
       line[list[l]] = line[list[l]+1];
 }
