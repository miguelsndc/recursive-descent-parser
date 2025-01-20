#include "expression.h"
#include <iostream>
#include <stdexcept>

BinaryExpression::BinaryExpression(Expression *_e1, Operand _op, Expression *_e2) 
: e1(_e1), e2(_e2), op(_op)
{
    std::cout << e1->eval() << ' ' << op.val << ' ' << e2->eval() << " - ";
    std::cout << "Creating binary expression with operator: " << op.val << std::endl;
}

int BinaryExpression::eval() {
    int v1 = e1->eval();
    int v2 = e2->eval();

    if ((op.val == "+" || op.val == "-" || op.val == "/" || op.val == "*") && (e1->is_boolean || e2->is_boolean)) {
        throw std::runtime_error("Arithmetic operations can't execute on boolean literals");
    }

    if (op.val == "+") return v1 + v2;
    if (op.val == "-") return v1 - v2;
    if (op.val == "/") {
        if (v2 == 0) throw std::runtime_error("Division by zero");
        return v1 / v2;
    }
    if (op.val == "*") return v1 * v2;

    if (op.val == ">") return v1 > v2;
    if (op.val == "<") return v1 < v2;
    if (op.val == ">=") return v1 >= v2;
    if (op.val == "!=") return v1 != v2;
    if (op.val == "==") return v1 == v2;
    if (op.val == "<=") return v1 <= v2;
    if (op.val == "||") return v1 || v2;
    if (op.val == "&&") return v1 && v2;

    throw std::runtime_error("Unknown operator: " + op.val);
}

UnaryExpression::UnaryExpression(Expression *_e1, Operand _op) 
: e1(_e1), op(_op) {}

int UnaryExpression::eval() {
    int v1 = e1->eval();

    if (e1->is_boolean && op.val == "!") return !v1;
    if (!e1->is_boolean && op.val == "-") return -v1; 

    throw std::runtime_error("Unknown or Unmatched operator: " + op.val);
}

LiteralExpression::LiteralExpression(Token _value) 
: value(_value) {
    std::cout << '(' << value.val << ')' << '\n';
    if (value.val == "true") {
        this->is_boolean = true;
    } else if (value.val == "false") {
        this->is_boolean = true;
    }
}

int LiteralExpression::eval() {
    if (is_boolean) {
        return (value.val == "true");
    }
    return std::stoi(value.val);
}


