#ifndef PARSER_H
#define PARSER_H
#include "token.h"
typedef enum {
    SYNTAXERROR,
    MISSINGTOKEN,
    NOERROR
} ErrorType ;
ErrorType checkTokens(Token* tokens, int* line, uint size);

#endif
