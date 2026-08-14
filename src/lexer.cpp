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
Token** lexer(string_view content) {
    uint content_size = content.size();
    uint i = 0;
    int current_i = 0;
    int numsi = 0;
    char* number = (char *) malloc(11);
    Token** tokens = (Token**) calloc(content_size , sizeof(Token*));
    while (i < content_size) {
        
        while (i < content_size && content[i] >= '0' && content[i] <= '0' + 9) {
            
            number[numsi++] = content[i++];
            
        }
        if (numsi > 0) {
            Token *token = (Token*) calloc(1,sizeof(Token));
            token->token_type = NUMBER;
            number[numsi] = '\0';
            token->val = number;
            numsi = 0;
            number = NULL;
            number = (char *) malloc(11);
            tokens[current_i++] = token;
        }
        if (
            i < content_size && (content[i] == ASSCIADDITION || content[i] == ASSCIMULTIPLACATION
            || content[i] == ASSCISUBSTRACTION || content[i] == ASSCIDIVISION
            || content[i] == ASSCICLOSEBRACKETS || content[i] == ASSCIOPENBRACKETS)
        ) {
            Token *token = (Token*) calloc(1,sizeof(Token));
            token->val = string_view(&content[i], 1);
            token->token_type = checkIsTokenAvailable(content[i]);
            tokens[current_i++] = token;
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

    return tokens;
}