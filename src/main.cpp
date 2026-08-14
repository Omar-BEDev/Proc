#include <cstdio>
#include "lexer.h"
#include "token.h"

using namespace std;

static const char* token_type_name(TokenType type) {
    switch (type) {
        case NUMBER: return "NUMBER";
        case SUBSTRACTION: return "SUBSTRACTION";
        case ADDITION: return "ADDITION";
        case DIVISION: return "DIVISION";
        case MULTIPLACATION: return "MULTIPLACATION";
        case OPEN_BRACKETS: return "OPEN_BRACKETS";
        case CLOSE_BRACKETS: return "CLOSE_BRACKETS";
        case NOT_FOUND: return "NOT_FOUND";
    }
    return "UNKNOWN";
}

int main() {
    const char* filename = "m.txt";
    string content = extract_file_content(filename);
    Token** tokens = lexer(content);
    for (int i = 0; tokens[i] != nullptr; i++) {
        Token* token = tokens[i];
        printf("%d - [%.*s : %s]\n", i + 1, (int)token->val.size(), token->val.data(), token_type_name(token->token_type));
    }
    return 0;
}