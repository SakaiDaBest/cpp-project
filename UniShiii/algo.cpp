
#include <iostream>
#include <string>
#include <algorithm> // For std::transform
#include <cctype>    // For std::toupper

int main() {
    std::string text = "hello world";
    std::transform(text.begin()+3, text.end(), text.begin()+3, ::toupper);
    std::cout << "Uppercase string: " << text << std::endl;
    return 0;
}


