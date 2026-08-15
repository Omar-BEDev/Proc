```c
//lexer.c
#include "lexer.h"
#include "token.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string_view>
using namespace std;


string extract_file_content(const char* path) {
    ifstream file(path);
    if (!file.is_open()) {
        return "not found file";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
Token* lexer(string_view content, int * returnContentSize) {
    uint content_size = content.size();
    uint i = 0;
    uint size = 1;
    uint current_i = 0;
    int numsi = 0;
    char* number = (char *) malloc(11);
    Token* tokens = (Token*) calloc(size , sizeof(Token));
    while (i < content_size) {
        if (current_i >= size) {
            size *= 2;
            tokens = (Token*) realloc(tokens, size * sizeof(Token));
        }
        while (i < content_size && content[i] >= '0' && content[i] <= '0' + 9) {
            
            number[numsi++] = content[i++];
            
        }
        if (numsi > 0) {
            checkReallocAvailable(&tokens, &size, current_i);
            number[numsi] = '\0';
            tokens[current_i++] = {.val = number,.token_type = NUMBER};
            numsi = 0;
            number = NULL;
            number = (char *) malloc(11);
        }
        
        if (
            i < content_size && (content[i] == ASSCIADDITION || content[i] == ASSCIMULTIPLACATION
            || content[i] == ASSCISUBSTRACTION || content[i] == ASSCIDIVISION
            || content[i] == ASSCICLOSEBRACKETS || content[i] == ASSCIOPENBRACKETS)
        ) {
            checkReallocAvailable(&tokens, &size, current_i);
            TokenType token_type = checkIsTokenAvailable(content[i]);
            tokens[current_i++] = {
                .val = string_view(&content[i], 1), 
                .token_type = token_type
            };
            i++;
        }
        else if (i < content_size && (content[i] == ASSCiSPACE || content[i] == ASSCINEWLINE)) {
            i++;
        }
        else {
            i++;
        }
    }
    free(number);
    *returnContentSize = current_i;
    return tokens;
}

```
```c
//lexer.h
#ifndef LEXER_H
#define LEXER_H
#include <string_view>
#define ASSCIADDITION 43
#define ASSCISUBSTRACTION 45
#define ASSCIMULTIPLACATION 42
#define ASSCIDIVISION 47
#define ASSCiSPACE 32
#define ASSCIOPENBRACKETS 40
#define ASSCICLOSEBRACKETS 41
#define ASSCINEWLINE 10
#include <string>
#include "token.h"

using namespace std;

string extract_file_content(const char* path);
Token* lexer(string_view content, int* returnContentSize);
static inline void checkReallocAvailable(Token** tokens, uint* size, uint current_i) {
    if (current_i >= *size) {
        *size *= 2;
        *tokens = (Token *)realloc(&tokens, *size * sizeof(Token));
    }
}
#endif

```