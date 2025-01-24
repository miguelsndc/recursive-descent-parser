#include "lexer.h"
#include "token.h"
#include <stdexcept>

Lexer::Lexer(std::string &text): m_text(text) {
    if (m_text.size() > 0) {
        m_current_char = m_text[m_cursor];
    }
}

void Lexer::set_expression(std::string exp) {
    m_text = exp;
    m_cursor = 0;
    if (m_text.size() > 0) {
        m_current_char = m_text[m_cursor];
    }
}

void Lexer::skip_whitespace() {
    while (m_current_char && std::isspace(m_current_char)) {
        advance();
    }
};

void Lexer::advance() { 
    m_cursor++;

    if (m_cursor >= m_text.size()) {
        m_current_char = '\0';
    } else {
        m_current_char = m_text[m_cursor];
    }
};

Token Lexer::get_integer_literal() {
    std::string result = "";
    while (m_current_char && std::isdigit(m_current_char)) {
        result += m_current_char;
        advance();
    }
    return Token(Token::LITERAL, result);
};

Token Lexer::handle_less_than() {
    advance();

    if (m_current_char == '=') {
        advance();
        return Token(Token::REL, "<=");
    }

    return Token(Token::REL, "<");
}
Token Lexer::handle_ampersand() {
    advance();

    if (m_current_char == '&') {
        advance();
        return Token(Token::AND, "&&");
    }

    throw std::runtime_error("Error: Expected `&&`, got `&` instead.");
}
Token Lexer::handle_greater_than() {
    advance();

    if (m_current_char == '=') {
        advance();
        return Token(Token::REL, ">=");
    }

    return Token(Token::REL, ">");
}
Token Lexer::handle_equals() {
    advance();

    if (m_current_char == '=') {
        advance();
        return Token(Token::EQUALS, "==");
    }

    throw std::runtime_error("Error: Expected `==` got `=` instead");
}
Token Lexer::handle_pipe() {
    advance();

    if (m_current_char == '|') {
        advance();
        return Token(Token::OR, "||");
    }

    throw std::runtime_error("Error: Expected `||` got `|` instead");
}
Token Lexer::handle_exclamation() {
    advance();
    if (m_current_char == '=') {
        return Token(Token::EQUALS, "!=");
    }
    throw std::runtime_error("Error: Expected `!=` got `!` instead");
}    

Token Lexer::handle_true_literal() {
    std::string target = "true";
    std::string result = "";
    for (unsigned int i = 0; m_current_char && i < target.size(); i++) {
        result += m_current_char;
        advance();
    }
    
    if (result == target) {
        return Token(Token::LITERAL, result);
    }

    throw std::runtime_error("Error: Expected `true`, found: " + result + " instead");
}

Token Lexer::handle_false_literal() {
    std::string target = "false";
    std::string result = "";

    for (unsigned int i = 0; m_current_char && i < target.size(); i++) {
        result += m_current_char;
        advance();
    }
    
    if (result == target) {
        return Token(Token::LITERAL, result);
    }

    throw std::runtime_error("Error: Expected `false`, found: " + result + " instead");
}

Token Lexer::next_token() {
    std::string result = "";

    while (m_current_char) {
        if (std::isspace(m_current_char)) {
            skip_whitespace();
            continue;
        }

        if (std::isdigit(m_current_char)) {
            return get_integer_literal();
        }

        switch (m_current_char) {
                case '+':
                    advance();
                    return Token(Token::ADD, "+");
                case '-':
                    advance();
                    return Token(Token::ADD, "-");
                case '*':
                    advance();
                    return Token(Token::MULTIPLY, "*");
                case '/':
                    advance();
                    return Token(Token::MULTIPLY, "/");
                case '=':
                    return handle_equals();
                case '<':
                    return handle_less_than();
                case '>':
                    return handle_greater_than();
                case '!':
                    return handle_exclamation();
                case '&':
                    return handle_ampersand();
                case '|':
                    return handle_pipe();
                case 't':
                    return handle_true_literal();
                case 'f':
                    return handle_false_literal();
                case '(':
                    advance();
                    return Token(Token::LEFT_PAREN, "(");
                case ')':
                    advance();
                    return Token(Token::RIGHT_PAREN, ")");
                default:
                    throw std::runtime_error(std::string("Invalid character: ") + m_current_char);
            }
    }

    return Token(Token::_EOF, "");
}


