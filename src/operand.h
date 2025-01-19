#ifndef OPERAND_H
#define OPERAND_H

#include <string>
#include "token.h"

class Operand {
public:
    std::string val = "";

    // conversion between token and operand
    // operand values are a subset of Token::type
    Operand() = default;
    Operand(Token &t);
};

#endif