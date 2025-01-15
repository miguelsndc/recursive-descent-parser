## Grammar

```
<exp>         ::= <or_exp>
<or_exp>      ::= <and_exp> [ “||” <and_exp> ]
<and_exp>     ::= <eq_exp> [ “&&” <eq_exp> ]
<eq_exp>      ::= <rel_exp> [ “==” <rel_exp> | “!=” <rel_exp> ]
<rel_exp>     ::= <add_exp> [ “<” <add_exp> | “>” <add_exp> | “<=” <add_exp> | “>=” <add_exp> ]
<add_exp>     ::= <mul_exp> [ “+” <mul_exp> | “-” <mul_exp> ]
<mul_exp>     ::= <unary_exp> [ “*” <unary_exp> | “/” <unary_exp> ]
<unary_exp>   ::= “-” <primary_exp> | <primary_exp>
<primary_exp> ::= <literal> | “(“ <exp> “)”
<literal>     ::= integer literals | boolean literals
```

### Things i'll need

- **Expression**: Base class that holds the value and the power to evaluate expressions
- **Binary** and **Unary** Expressions
- **Boolean** and **Integer** values
- A **Lexer** to analyze the expression and return tokens
- **Token** that stores it's type and value

#### Types of Tokens:
- **Operand** will hold the operands (duh) like: ```|| && + - /```
- **Literals** store the individual values and their types: _i.e_ a Token with value **8** and type **Integer**.
___

- Individual functions to parse each expression according to the grammar
- A big big parser that orchestrate everything.