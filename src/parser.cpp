#include "token.h"
#include <cstddef>
#include <cstdlib>
#include <string_view>
#include <unordered_map>
#include "parser.h"
using namespace std;

unordered_map<TokenType, int> powers {
    {ADDITION, 1},
    {SUBSTRACTION, 1},
    {MULTIPLACATION, 2},
    {DIVISION, 2},
};
int searchPower(TokenType token_type) {
    auto it = powers.find(token_type);
    if (it == powers.end() ) {
        return 0;
    }
    return it->second;
}
ErrorType checkTokens(Token* tokens, int* line, uint size) {
    uint type_s = 1;
    TokenType* stack = (TokenType* )calloc(type_s, sizeof(TokenType));
    int top = 0; 
    uint i = 0;
    bool excepting_value = false;
    while (i < size) {
        if (tokens[i].token_type == OPEN_BRACKETS) {
            top++;
        }
        else if (tokens[i].token_type == CLOSE_BRACKETS) {
            top--;
        }
        if (top == -1) {
            return MISSINGTOKEN;
            break;
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
        *line = tokens[i - 1].line;
        return  MISSINGTOKEN;
    }
    if (excepting_value == true) {
        return SYNTAXERROR;
    }
    free(stack);
    stack = NULL;
    return NOERROR;
}


TreeNode* parse_two(Token* tokens, uint *i, uint* size) {
    TreeNode* left = parse_bracket(tokens, i, size);
    while (*i < *size && tokens[*i].token_type == MULTIPLACATION || tokens[*i].token_type == DIVISION) {
        TreeNode *opr = new TreeNode{};
        opr->val = tokens[*i].val;
        (*i)++;
        TreeNode* right = parse_bracket(tokens, i, size);
        opr->left = left;
        opr->right = right;
        return opr;
    }
    return left;
}

TreeNode* parse_one(Token* tokens, uint *i, uint* size) {
    TreeNode* left = parse_two(tokens, i);
    (*i)++;
    while (*i < *size && tokens[*i].token_type == ADDITION || tokens[*i].token_type == SUBSTRACTION) {
        TreeNode *opr = new TreeNode{};
        opr->val = tokens[*i].val;
        (*i)++;
        TreeNode* right = parse_two(tokens, i, size);
        opr->left = left;
        opr->right = right;
        return opr;
    }
    return left;
}


TreeNode* Ast(Token* tokens,uint size) { 
   uint i = 0;
   TreeNode* Ast = parse_one(tokens, &i, &size);
   return Ast;
}
