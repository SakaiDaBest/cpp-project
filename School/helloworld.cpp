#include <iostream>

int maxDraws(int a, int b, int c) {
    return a + b + (c - 1);
}

int main() {
    int a, b, c;
    std::cout << "Enter the number of games played (a <= b <= c): ";
    std::cin >> a >> b >> c;

    int max_draws = maxDraws(a, b, c);
    std::cout << "Maximum number of draws: " << max_draws << std::endl;

    return 0;}