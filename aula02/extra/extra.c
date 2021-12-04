#include <stdio.h>

void cumSum(int* a, int* b, int* n) {
    int c = 0;
    for(int i = 0; i < n; i++) {
        c += a[i];
        b[i] = c;
    }
}

void printArray(char* s, int* a, int* n) {
    printf("%s:", s);
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void) {
    int size = 5;
    int a[5] = {1, 2, 3, 4, 5};
    printArray("a", a, size);
    return 0;
}