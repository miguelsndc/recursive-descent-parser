#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "operand.h"
#include "token.h"

class Expression {
    public:
        bool is_boolean = false;
        virtual int eval() = 0;
};

class BinaryExpression: public Expression {
    public:
        Expression *e1, *e2;
        Operand op;
        BinaryExpression(Expression *_e1, Operand _op, Expression *_e2);
        int eval() override;
};

class UnaryExpression: public Expression {
    public:
        Expression *e1;
        Operand op;
        UnaryExpression(Expression *_e1, Operand _op);
        int eval() override;
};

class LiteralExpression: public Expression {
    public:
        Token value;
        LiteralExpression(Token _value);
        int eval() override;
};

#endif