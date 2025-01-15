#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
private:
    // debugging purposes
    std::string _get_type_as_string() {
        switch (type)
        {
            case INTEGER:
                return "INTEGER";
            case BOOLEAN:
                return "BOOLEAN";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case OR:
                return "OR";
            case AND:
                return "AND";
            case EQUALS:
                return "EQUALS";
            case REL:
                return "REL";
            case ADD:
                return "ADD";
            case MULTIPLY:
                return "MULTIPLY";
            case UNARY:
                return "UNARY";
            case PRIMARY:
                return "PRIMARY";
            case LITERAL:
                return "LITERAL";
            case _EOF:
                return "EOF";
        default:
            return "";
            break;
        }
    }
public:
    enum Type {
        INTEGER,
        BOOLEAN,
        LEFT_PAREN,
        RIGHT_PAREN,
        OR,
        AND,
        EQUALS,
        REL,
        ADD,
        MULTIPLY,
        UNARY,
        PRIMARY,
        LITERAL,
        _EOF,
    };

    Type type = INTEGER;
    std::string val = "";
    Token() = default;
    Token(Type t, std::string value);
    void print();
};

#endif