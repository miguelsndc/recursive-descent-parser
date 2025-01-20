#include "parser.h"
#include <stdexcept>

Parser::Parser(std::string exp) {
    this->exp = exp;
    lexer.set_expression(exp);
    read_token();
}

void Parser::read_token() {
    curr_token = lexer.next_token();
}

Expression * Parser::parse_exp() {
    return parse_or_exp();
}

Expression * Parser::parse_or_exp() {
    Expression* left = parse_and_exp();
    while (curr_token.type == Token::OR) {
        Operand op = curr_token;
        read_token();
        Expression *right = parse_and_exp();
        left = new BinaryExpression(left, op, right);
    }
    return left;
}

Expression * Parser::parse_and_exp() {
    Expression* left = parse_eq_exp();
    while (curr_token.type == Token::AND) {
        Operand op = curr_token;
        read_token();
        Expression *right = parse_eq_exp();
        left = new BinaryExpression(left, op, right);
    }
    return left;
}

Expression * Parser::parse_eq_exp() {
    Expression* left = parse_rel_exp();
    while (curr_token.type == Token::EQUALS) {
        Operand op = curr_token;
        read_token();
        Expression *right = parse_rel_exp();
        left = new BinaryExpression(left, op, right);
    }
    return left;
}

Expression * Parser::parse_rel_exp() {
    Expression* left = parse_add_exp();
    while (curr_token.type == Token::REL) {
        Operand op = curr_token;
        read_token();
        Expression *right = parse_add_exp();
        left =  new BinaryExpression(left, op, right);
    }
    return left;
}

Expression * Parser::parse_add_exp() {
    Expression* left = parse_mul_exp();
    while (curr_token.type == Token::ADD) {
        Operand op = curr_token;
        read_token();
        Expression *right = parse_mul_exp();
        left = new BinaryExpression(left, op, right);
    }
    return left;
}

Expression * Parser::parse_mul_exp() {
    Expression* left = parse_unary_exp();
    while (curr_token.type == Token::MULTIPLY) {
        Operand op = curr_token;
        read_token();
        Expression *right = parse_unary_exp();
        left = new BinaryExpression(left, op, right);
    }
    return left;
}

Expression * Parser::parse_primary_exp() {
    if (curr_token.type == Token::LITERAL) {
        Expression* e = new LiteralExpression(curr_token);
        read_token();
        return e;
    } else if (curr_token.type == Token::LEFT_PAREN) {  
        read_token();  
        Expression *e = parse_exp();
        
        if (curr_token.type != Token::RIGHT_PAREN) {
            throw std::runtime_error("Expected closing parenthesis");
        }
        read_token();
        return e;
    } 
    
    throw std::runtime_error("Expected literal or (expression)");
}

Expression * Parser::parse_unary_exp() {
    if ((curr_token.type == Token::ADD && curr_token.val == "-") || curr_token.type == Token::UNARY) {
        Operand op = curr_token;
        read_token();
        Expression *e = (curr_token.type == Token::ADD ? (parse_unary_exp()) : parse_primary_exp());
        return new UnaryExpression(e, op);
    } 
    return parse_primary_exp();
}