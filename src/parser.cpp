#include "token.h"
#include <cstdlib>
#include "parser.h"
using namespace std;


ErrorType checkTokens(Token* tokens, int* line, uint size) {
    uint type_s = 1;
    TokenType* stack = (TokenType* )calloc(type_s, sizeof(TokenType));
    int top = 0; 
    uint i = 0;
    bool excepting_value = false;
    while (i < size) {
        if (top == -1) {
            return MISSINGTOKEN;
            break;
        }
        if (tokens[i].token_type == OPEN_BRACKETS) {
            top++;
        }
        else if (tokens[i].token_type == CLOSE_BRACKETS) {
            top--;
        }
        if (tokens[i].token_type == NUMBER || tokens[i].token_type == CLOSE_BRACKETS) {
            if (i > 0 &&tokens[i - 1].token_type == OPEN_BRACKETS && excepting_value == true
                && tokens[i].token_type != NUMBER
            ) {
                *line = tokens[i].line;
                return SYNTAXERROR;
            }

            else if (
                i > 0 && tokens[i- 1].token_type == NUMBER
                && tokens[i].token_type == NUMBER
                && excepting_value == false
        ) {
                *line = tokens[i].line;
                return SYNTAXERROR;
        }
    
            excepting_value = false;
        }
        else {
            if (
                tokens[i].token_type != OPEN_BRACKETS 
                && excepting_value == true
            ) {
                *line = tokens[i].line;
                return SYNTAXERROR;
            }
            excepting_value = true;
        }
        i++;
    }

    if (top > 0) {
        return  MISSINGTOKEN;
    }
    if (excepting_value == true) {
        return SYNTAXERROR;
    }
    free(stack);
    stack = NULL;
    return NOERROR;
}