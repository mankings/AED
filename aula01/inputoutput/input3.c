#include <stdio.h>
#define SIZE 20

int main(void) {
    char str[SIZE];
    puts("Qual o teu nome?");
    scanf("%s", str); //boa opção, mas para de ler após espaço - usar scan("%[^\n]", str) para ler a linha inteira
    printf("Boas %s\n", str);
    return 0;
}