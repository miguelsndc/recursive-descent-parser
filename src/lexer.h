#ifndef LEXER_H
#define LEXER_H

#include "token.h"

class Lexer {
  private:
    std::string m_text = "";
    char m_current_char = '\0';
    unsigned int m_cursor = 0;

    void skip_whitespace();

    // take next token
    void advance();
    
    // utility functions
    Token handle_less_than();
    Token handle_ampersand();
    Token handle_greater_than();
    Token handle_equals();
    Token handle_pipe();
    Token handle_exclamation();
    Token handle_true_literal();
    Token handle_false_literal();
    Token get_integer_literal();

  public:  
    Lexer(std::string& text);

    Lexer() = default;
    void set_expression(std::string exp);

    Token next_token();
};

#endif