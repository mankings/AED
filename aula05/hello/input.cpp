#include <iostream>

int main(void) {
    std::cout << "Insert integer: ";
    int n = 0;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cout << i << std::endl;
}