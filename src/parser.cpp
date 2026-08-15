#include "token.h"
#include <cstdlib>

using namespace std;
typedef enum {
    SYNTAXERROR,
    MISSINGTOKEN,
    NOERROR
} ErrorType ;

ErrorType checkTokens(Token* tokens, int* line, int size) {
    uint type_s = 1;
    TokenType* stack = (TokenType* )calloc(type_s, sizeof(TokenType));
    int top = 0; 
    uint i = 0;
    int line_number = 0;
    while (i < size) {
        if (
            i + 1 < size &&(tokens[i].token_type == NUMBER || tokens[i].type == PUNCTUATION) && 
            tokens[i + 1].type != OPERATOR
        ){
            *line = tokens[i + 1].line; 
            return SYNTAXERROR;
        }
        if (
            i + 1 < size && tokens[i].type == OPERATOR 
            && tokens[i + 1].type == OPERATOR 
        ){
            *line = tokens[i + 1].line; 
            return SYNTAXERROR;
        }
        i++;
    }
    i = 0;
    while (i < size) {
        if (top > type_s) {
            type_s *= 2;
            stack = (TokenType*) realloc(stack, type_s * sizeof(TokenType));
        }
        TokenType tokenType = tokens[i].token_type;
        if (tokenType == OPEN_BRACKETS) {
            stack[top] = tokenType;
        }
        if (tokenType == CLOSE_BRACKETS) {
            top--;
            stack[top] = tokenType;
        }
        top++;
    }
    if (top > 0) {
        return MISSINGTOKEN;
    }
    free(stack);
    stack = NULL;
    return NOERROR;
}