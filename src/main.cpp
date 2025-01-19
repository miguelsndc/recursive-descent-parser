#include <iostream>
#include "parser.h"

int main() {
    Parser parser("true || false == false");
    Expression *exp = parser.parse_exp();
    std::cout << exp->eval() << '\n';
}