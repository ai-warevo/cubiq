#include <iostream>
#include <string_view>

int main() {
    constexpr std::string_view greeting = "Hello, world!";
    std::cout << greeting << std::endl;
    return 0;
}
