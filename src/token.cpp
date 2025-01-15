#include "token.h"
#include <iostream>

void Token::print() {
    std::cout << "Token(" << _get_type_as_string() << ", "<< this->val << ")\n";
}

Token::Token(Type t, std::string value): type(t), val(value) {};