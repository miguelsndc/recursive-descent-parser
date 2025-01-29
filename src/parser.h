#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "token.h"
#include "expression.h"

class Parser {
    private:
        std::string m_exp = "";
        Lexer* m_lexer = nullptr;
        Token m_curr_token;
        void read_token(); 
        Expression *parse_or_exp();
        Expression *parse_and_exp();
        Expression *parse_eq_exp();
        Expression *parse_rel_exp();
        Expression *parse_add_exp();
        Expression *parse_mul_exp();
        Expression *parse_unary_exp();
        Expression *parse_primary_exp();
        // helper method, parses the expression and returns a pointer to the chain of expressions
        // for later deallocation on `parse()`, ensures i don't explode any computers when testing multiple cases
        std::pair<std::string, Expression*> handle_parse(std::string exp);
    public:
    Parser();
    ~Parser();
    Expression *parse_exp();
    void parse();
};

#endif