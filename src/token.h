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
            case LITERAL:
                return "LITERAL";
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
            case PRIMARY:
                return "PRIMARY";
            case _EOF:
                return "EOF";
        default:
            return "";
            break;
        }
    }
public:
    enum Type {
        BEGIN, // alias
        LEFT_PAREN, // (
        RIGHT_PAREN, // )
        OR, // ||
        AND, // && 
        EQUALS, // == !=
        REL, // <, >, >=, <=
        ADD, // +, -
        MULTIPLY, // *, /
        UNARY, // -
        PRIMARY, // <literal> ( exp )
        LITERAL, // integers and booleans
        _EOF, // end of file 
    };

    Type type = BEGIN;
    std::string val = "";

    Token() = default;
    Token(Type t, std::string value);

    // utility functions
    bool is_logical();
    bool is_arithmetic();
    bool is_relational();
    bool is_equality();

    // also debugging
    void print();
};

#endif