#include <stdio.h>
#define SIZE 20

int main(void) {
    char str[SIZE];
    puts("Qual o teu nome?");
    gets(str); //não usar, muito deprecado
    printf("Boas %s\n", str);
    return 0;
}