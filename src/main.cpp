#include <iostream>
#include "parser.h"

int main() {
    Parser parser;
    std::string exp; 
    // handle multiple test cases
    // while(std::getline(std::cin, exp)) {
    //     std::cout << parser.parse(exp) << '\n';
    // }
    std::getline(std::cin, exp);
    std::cout << parser.parse(exp) << '\n';
}
