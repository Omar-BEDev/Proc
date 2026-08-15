#ifndef TOKEN_H
#define TOKEN_H

#include <string_view>
#include <unordered_map>

using namespace std;

typedef enum {
    NUMBER,
    SUBSTRACTION,
    ADDITION,
    DIVISION,
    MULTIPLACATION,
    OPEN_BRACKETS,
    CLOSE_BRACKETS,
    NOT_FOUND
} TokenType;
typedef enum {
  OPERATOR,
  PUNCTUATION,
  NOT_TYPE
} Type;

extern unordered_map<char, TokenType> symbols;

typedef struct Token {
    basic_string_view<char> val;
    TokenType token_type;
    Type type;
    int line;
} Token;

TokenType checkIsTokenAvailable(char symbol);
Type checkSymbolType(TokenType tokenType);
#endif
