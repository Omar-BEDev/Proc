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
    int tokensSize = 0;
    string content = extract_file_content(filename);
    Token* tokens = lexer(content, &tokensSize);
    for (int i = 0; i < tokensSize; i++) {
        
        printf("%d - [%.*s : %s]\n", i + 1, (int)tokens[i].val.size(), tokens[i].val.data(), token_type_name(tokens[i].token_type));
    }
    return 0;
}