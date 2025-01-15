#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "typedefs.h"

class Lexer {
  private:
    std::string _text;
    char _current_char = '\0';
    u32 _cursor = 0;

    void skip_whitespace();
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
    Token next_token();
};

#endif