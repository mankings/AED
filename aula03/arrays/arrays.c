#include <assert.h>
#include <stdio.h>

void display(int* a, size_t size) {
    printf("Array = [ ");
    for(size_t i = 0; i < (size - 1); i++) {
        printf("%d, ", a[i]);
    }
    printf("%d ]\n", a[size - 1]);
}

int* append(int* array1, size_t size1, int* array2, size_t size2) {
    assert(size1 > 0 && size2 > 0);

    size_t n = size1 + size2;
}

int main(void) {

    return 0;
}