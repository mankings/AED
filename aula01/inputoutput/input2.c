#include <stdio.h>
#define SIZE 20

int main(void) {
    char str[SIZE];
    puts("Qual o teu nome?");
    fgets(str, SIZE, stdin); //opção ideal para input, lê espaços
    printf("Boas %s\n", str);
    return 0;
}