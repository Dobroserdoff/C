#include <stdio.h>

#define swap(t, x, y) do {swapdef((t), (x), (y));} while (0)
    
int main() {
    swap(0, 2, 3);
    return 0;    
}
    
void swapdef(t, x, y) {
    t = x;
    x = y;
    y = t;
    printf("%d, %d\n", x, y);
}
