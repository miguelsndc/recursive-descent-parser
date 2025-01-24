#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.h"

class Expression {
    public:
        bool is_boolean = false;
        virtual int eval() = 0;
        // converts the result of evaluation to string
        // e.g if the expression is boolean (`is_boolean = true`) and eval() returns `1`, to_string(1) returns "true"
        std::string to_string(int value);
        virtual ~Expression() = default;
};

class BinaryExpression: public Expression {
    public:
        Expression *e1, *e2;
        Token operand;
        BinaryExpression(Expression *_e1, Token _operand, Expression *_e2);
        int eval() override;
        ~BinaryExpression() override;
};

class UnaryExpression: public Expression {
    public:
        Expression *e1;
        Token operand;
        UnaryExpression(Expression *_e1, Token _operand);
        int eval() override;
        ~UnaryExpression() override;
};

class LiteralExpression: public Expression {
    public:
        Token token;
        LiteralExpression(Token _value);
        int eval() override;
};

#endif