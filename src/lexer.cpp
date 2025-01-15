#include "lexer.h"
#include "token.h"
#include "typedefs.h"
#include <stdexcept>

Lexer::Lexer(std::string &text): _text(text) {
    if (_text.size() > 0) {
        _current_char = _text[_cursor];
    }
}

void Lexer::skip_whitespace() {
    while (_current_char && std::isspace(_current_char)) {
        advance();
    }
};

void Lexer::advance() { 
    _cursor++;

    if (_cursor >= _text.size()) {
        _current_char = '\0';
    } else {
        _current_char = _text[_cursor];
    }
};

Token Lexer::get_integer_literal() {
    std::string result = "";
    while (_current_char && std::isdigit(_current_char)) {
        result += _current_char;
        advance();
    }
    return Token(Token::Type::LITERAL, result);
};

Token Lexer::handle_less_than() {
    advance();

    if (_current_char == '=') {
        advance();
        return Token(Token::Type::REL, "<=");
    }

    return Token(Token::Type::REL, "<");
}
Token Lexer::handle_ampersand() {
    advance();

    if (_current_char == '&') {
        advance();
        return Token(Token::Type::AND, "&&");
    }

    throw std::runtime_error("Expected `&&`, got `&` instead.");
}
Token Lexer::handle_greater_than() {
    advance();

    if (_current_char == '=') {
        advance();
        return Token(Token::Type::REL, ">=");
    }

    return Token(Token::Type::REL, ">");
}
Token Lexer::handle_equals() {
    advance();

    if (_current_char == '=') {
        advance();
        return Token(Token::Type::EQUALS, "==");
    }

    throw std::runtime_error("Expected `==` got `=` instead");
}
Token Lexer::handle_pipe() {
    advance();

    if (_current_char == '|') {
        advance();
        return Token(Token::Type::REL, "||");
    }

    throw std::runtime_error("Expected `||` got `|` instead");
}
Token Lexer::handle_exclamation() {
    advance();
    if (_current_char == '=') {
        return Token(Token::Type::EQUALS, "!=");
    }
    return Token(Token::Type::UNARY, "!");
}    

Token Lexer::handle_true_literal() {
    std::string target = "true";
    std::string result = "";
    for (u32 i = 0; _current_char && i < target.size(); i++) {
        result += _current_char;
        advance();
    }
    
    if (result == target) {
        return Token(Token::Type::LITERAL, result);
    }

    throw std::runtime_error("Expected `true`, found: " + result + "instead");
}

Token Lexer::handle_false_literal() {
    std::string target = "false";
    std::string result = "";

    for (u32 i = 0; _current_char && i < target.size(); i++) {
        result += _current_char;
        advance();
    }
    
    if (result == target) {
        return Token(Token::Type::LITERAL, result);
    }

    throw std::runtime_error("Expected `false`, found: " + result + "instead");
}

Token Lexer::next_token() {
    std::string result = "";

    while (_current_char) {
        if (std::isspace(_current_char)) {
            skip_whitespace();
            continue;
        }

        if (std::isdigit(_current_char)) {
            return get_integer_literal();
        }

        switch (_current_char) {
                case '+':
                    advance();
                    return Token(Token::Type::ADD, "+");
                case '-':
                    advance();
                    return Token(Token::Type::ADD, "-");
                case '*':
                    advance();
                    return Token(Token::Type::MULTIPLY, "*");
                case '/':
                    advance();
                    return Token(Token::Type::MULTIPLY, "/");
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
                    return Token(Token::Type::LEFT_PAREN, "(");
                case ')':
                    advance();
                    return Token(Token::Type::RIGHT_PAREN, ")");
                default:
                    throw std::runtime_error(std::string("Invalid character: ") + _current_char);
            }
    }

    return Token(Token::Type::_EOF, "");
}


