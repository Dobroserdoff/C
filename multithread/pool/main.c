#include <stdio.h>
#include <unistd.h>

struct timeval {
    time_t      tv_sec;     /* seconds */
    suseconds_t tv_usec;    /* microseconds */
};

int par[3] = { 1, 2, 4 };
int asr[3] = { 100000, 500000, 1000000 };
int rr[3] = { 0, 100, 1000 };
int br[3] = { 0, 10, 100 };

void gettime(struct timeval*, int*, int*, int*, int*);

int main() {
    int i, j, k, l;
    int p, a, r, b, sec, msec;
    struct timeval end;
    char* sep1 = { "========================================" };
    char* sep2 = { "----------------------------------------" };

    for (i = 0; i < (sizeof(par) / 4); i++) {
        p = par[i];
       
        for (j = 0; j < (sizeof(asr) / 4); j++) {
            a = asr[j];
            
            for (k = 0; k < (sizeof(rr) / 4); k++) {
                r = rr[k];

                for (l = 0; l <= k; l++) {
                    b = br[l];
                    gettime(&end, &p, &a, &r, &b);

                    printf("%10d%10d%10d%10d%10ld\n", p, a, r, b);                  
                }
            }
            if (j != (sizeof(asr) / 4) - 1) {
                puts(sep2);
            }
        }
        puts(sep1);  
    }
}

void gettime(struct timeval* endp, int* pp, int* ap, int* rp, int* bp) {
    struct timeval begin;

    
}
