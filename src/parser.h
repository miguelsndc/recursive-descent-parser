#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "operand.h"
#include "token.h"
#include "expression.h"

class Parser {
    private:
        std::string exp = "";
        Lexer lexer;
        Token curr_token;
        void read_token(); 
        Expression *parse_or_exp();
        Expression *parse_and_exp();
        Expression *parse_eq_exp();
        Expression *parse_rel_exp();
        Expression *parse_add_exp();
        Expression *parse_mul_exp();
        Expression *parse_unary_exp();
        Expression *parse_primary_exp();
    public:

    Parser(std::string exp);

    Expression *parse_exp();
};

#endif