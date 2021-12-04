#include <stdio.h>

void swap1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int* b) {    //CALL-BY-POINTER
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 1;
    int y = -1;
    swap2(&x, &y);
    printf("%d %d", x, y);
    return 0;
}