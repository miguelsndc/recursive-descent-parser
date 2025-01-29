#include "parser.h"
#include <iostream>
#include <stdexcept>

std::pair<std::string, Expression*> Parser::handle_parse(std::string _exp) {
    m_exp = _exp;
    // reset lexer
    m_lexer->set_expression(_exp);
    read_token();
    Expression * result = nullptr;
    try {
        result = parse_exp();
        std::string ans = result->to_string(result->eval());
        return {ans, result};
    } catch (const std::exception& err) {
        std::string error = err.what();
        return {error, result};
    }
}

std::string Parser::parse() {
    int c; std::cin >> c;
    while(c--) {
        std::string exp;
        std::getline(std::cin, exp);
        // ensure memory is free'd per test case
        auto [answer, expression_ptr_dealloc] = handle_parse(exp);
        if (expression_ptr_dealloc != nullptr) {
            delete expression_ptr_dealloc;
        }
        std::cout << answer << '\n';
    }
}

Parser::Parser() {
    m_lexer = new Lexer();
}

Parser::~Parser() {
    delete m_lexer;
}

void Parser::read_token() {
    m_curr_token = m_lexer->next_token();
}

Expression * Parser::parse_exp() {
    return parse_or_exp();
}

Expression * Parser::parse_or_exp() {
    Expression* left = parse_and_exp();
    while (m_curr_token.type == Token::OR) {
        Token operand = m_curr_token;
        read_token();
        Expression *right = parse_and_exp();
        left = new BinaryExpression(left, operand, right);
    }
    return left;
}

Expression * Parser::parse_and_exp() {
    Expression* left = parse_eq_exp();
    while (m_curr_token.type == Token::AND) {
        Token operand = m_curr_token;
        read_token();
        Expression *right = parse_eq_exp();
        left = new BinaryExpression(left, operand, right);
    }
    return left;
}

Expression * Parser::parse_eq_exp() {
    Expression* left = parse_rel_exp();
    while (m_curr_token.type == Token::EQUALS) {
        Token operand = m_curr_token;
        read_token();
        Expression *right = parse_rel_exp();
        left = new BinaryExpression(left, operand, right);
    }
    return left;
}

Expression * Parser::parse_rel_exp() {
    Expression* left = parse_add_exp();
    while (m_curr_token.type == Token::REL) {
        Token operand = m_curr_token;
        read_token();
        Expression *right = parse_add_exp();
        left =  new BinaryExpression(left, operand, right);
    }
    return left;
}

Expression * Parser::parse_add_exp() {
    Expression* left = parse_mul_exp();
    while (m_curr_token.type == Token::ADD) {
        Token operand = m_curr_token;
        read_token();
        Expression *right = parse_mul_exp();
        left = new BinaryExpression(left, operand, right);
    }
    return left;
}

Expression * Parser::parse_mul_exp() {
    Expression* left = parse_unary_exp();
    while (m_curr_token.type == Token::MULTIPLY) {
        Token operand = m_curr_token;
        read_token();
        Expression *right = parse_unary_exp();
        left = new BinaryExpression(left, operand, right);
    }
    return left;
}

Expression * Parser::parse_primary_exp() {
    if (m_curr_token.type == Token::LITERAL) {
        Expression* e = new LiteralExpression(m_curr_token);
        read_token();
        return e;
    } else if (m_curr_token.type == Token::LEFT_PAREN) {  
        read_token();  
        Expression *e = parse_exp();
        
        if (m_curr_token.type != Token::RIGHT_PAREN) {
            throw std::runtime_error("Error: Expected closing parenthesis");
        }
        read_token();
        return e;
    } 
    
    throw std::runtime_error("Error: Expected literal or (expression)");
}

Expression * Parser::parse_unary_exp() {
    if ((m_curr_token.type == Token::ADD && m_curr_token.val == "-") || m_curr_token.type == Token::UNARY) {
        Token operand = m_curr_token;
        read_token();
                                              // handle -<integer literal>
        Expression *e = (m_curr_token.type == Token::ADD ? (parse_unary_exp()) : parse_primary_exp());
        return new UnaryExpression(e, operand);
    } 
    return parse_primary_exp();
}