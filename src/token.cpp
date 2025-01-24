#include "token.h"
#include <iostream>

void Token::print() {
    std::cout << "Token(" << _get_type_as_string() << ", "<< this->val << ")\n";
}

bool Token::is_logical() {
    return type == OR || type == AND;
}
bool Token::is_arithmetic() {
    return type == ADD || type == MULTIPLY;
}
bool Token::is_relational() {
    return type == REL;
}
bool Token::is_equality() {
    return type == EQUALS;
}

Token::Token(Type t, std::string value): type(t), val(value) {};