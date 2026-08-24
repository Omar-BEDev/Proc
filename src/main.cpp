#include <cstdio>
#include <iostream>
#include "lexer.h"
#include "token.h"
#include "parser.h"
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

static void print_ast(TreeNode* node, const char* prefix = "", bool is_last = true) {
    if (!node) return;
    printf("%s%s%.*s\n", prefix, is_last ? "|-- " : "|-- ", (int)node->val.size(), node->val.data());
    string child_prefix = string(prefix) + "|   ";
    if (node->left || node->right) {
        if (node->left && node->right) {
            print_ast(node->left, child_prefix.c_str(), false);
            print_ast(node->right, child_prefix.c_str(), true);
        } else {
            TreeNode* only = node->left ? node->left : node->right;
            print_ast(only, child_prefix.c_str(), true);
        }
    }
}

int main() {
    const char* filename = "m.txt";
    int tokensSize = 0;
    string content = extract_file_content(filename);
    Token* tokens = lexer(content, &tokensSize);
    for (int i = 0; i < tokensSize; i++) {
        
        printf("%d - [%.*s : %s : %d]\n", i + 1, (int)tokens[i].val.size(), tokens[i].val.data(), token_type_name(tokens[i].token_type), tokens[i].line);
    }
    int line = 0;
    ErrorType err = checkTokens(tokens, &line, tokensSize);
    if (err == MISSINGTOKEN) {
        printf("error(line: %d): missing Bracket token')'\n",line);
        cerr << "error(line:" <<  line << " ): missing Bracket token')'"  << endl;
    }
    TreeNode * ast = Ast(tokens, tokensSize);
    if (ast) {
        printf("AST:\n");
        print_ast(ast);
    }
    return 0;
}