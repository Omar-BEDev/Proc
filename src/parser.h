#ifndef PARSER_H
#define PARSER_H
#include "token.h"
typedef enum {
    SYNTAXERROR,
    MISSINGTOKEN,
    NOERROR
} ErrorType ;
ErrorType checkTokens(Token* tokens, int* line, uint size);
TreeNode* parse_one(Token *tokens,uint* i, uint *size);
TreeNode* parse_two(Token *tokens,uint* i, uint* size);
TreeNode* Ast(Token* tokens,uint size);

inline TreeNode* parse_bracket(Token* tokens, uint *i, uint* size) {
    
    while (*i < *size && tokens[*i].token_type == OPEN_BRACKETS) {
        (*i)++;
        TreeNode* opr_tree = parse_one(tokens, i, size);
        if (*i < *size && tokens[*i].token_type == CLOSE_BRACKETS) {
            (*i)++;
            return opr_tree;
        }
    }
    TreeNode* left = new TreeNode{};
    left->val = tokens[*i].val;
    (*i)++;
    return left;
}
#endif
