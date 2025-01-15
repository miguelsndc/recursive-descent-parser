#include <iostream>
#include "lexer.h"
#include "token.h"

int main() {
    std::cout << "main" << std::endl;
    std::string exp = "2 + 3 + 4 + 6 * 2 / 4";
    Lexer lexer(exp);

    Token token;
    try {
        while (token.type != Token::Type::_EOF) {
            token = lexer.next_token();
            token.print();
        }
    } catch(const std::runtime_error &e) {
        std::cout << "Runtime error: " << e.what() << '\n';
    }
}