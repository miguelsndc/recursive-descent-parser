#include "expression.h"
#include <iostream>
#include <stdexcept>

std::string Expression::to_string(int value) {
    if (is_boolean) {
        return (value ? "true" : "false");
    }
    return std::to_string(value);
}


BinaryExpression::BinaryExpression(Expression *_e1, Token _operand, Expression *_e2) 
: e1(_e1), e2(_e2), operand(_operand)
{
    this->is_boolean = operand.type == Token::OR || operand.type == Token::REL || operand.type == Token::EQUALS || operand.type == Token::AND;
}

BinaryExpression::~BinaryExpression() {
    delete e1;
    delete e2;
}

int BinaryExpression::eval() {
    int v1 = e1->eval();
    int v2 = e2->eval();

    if (e1->is_boolean ^ e2->is_boolean) {
        throw std::runtime_error("Operations must be between literals of same type.");
   }


    if (operand.val == "+") return v1 + v2;
    if (operand.val == "-") return v1 - v2;
    if (operand.val == "/") {
        if (v2 == 0) throw std::runtime_error("Division by zero");
        return v1 / v2;
    }
    if (operand.val == "*") return v1 * v2;
    if (operand.val == ">") return v1 > v2;
    if (operand.val == "<") return v1 < v2;
    if (operand.val == ">=") return v1 >= v2;
    if (operand.val == "!=") return v1 != v2;
    if (operand.val == "==") return v1 == v2;
    if (operand.val == "<=") return v1 <= v2;
    if (operand.val == "||") return v1 || v2;
    if (operand.val == "&&") return v1 && v2;

    throw std::runtime_error("Unknown operator: " + operand.val);
}

UnaryExpression::UnaryExpression(Expression *_e1, Token _operand) 
: e1(_e1), operand(_operand) {}

UnaryExpression::~UnaryExpression() {
    delete e1;
}

int UnaryExpression::eval() {
    int v1 = e1->eval();

    if (!e1->is_boolean && operand.val == "-") return -v1; 

    throw std::runtime_error("Unknown or Unmatched operanderator: " + operand.val);
}

LiteralExpression::LiteralExpression(Token _value) 
: token(_value) {
    is_boolean = token.val == "true" || token.val == "false";
}

int LiteralExpression::eval() {
    if (is_boolean) {
        return (token.val == "true");
    }
    return std::stoi(token.val);
}

