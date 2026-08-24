#include <charconv>
#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
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
int calculator(char s, int a, int b) {
    switch (s) {
    case '+':
    return a+b;
    case '-':
    return a-b;
    case '*':
    return a*b;
    case '/':
    return a/b;
    default:
    return 0;
    }
    return 0;
}
int calculate_tree_node_values(TreeNode* ast) {
    if (ast == nullptr) {
        return 0;
    }
    
    int a = 0;
    int b = 0;
    int result = 0;
    if (!ast->left || ast->right && ast->token_type == NUMBER) {
        int n = 0;
        from_chars(ast->val.data(), ast->val.data() + ast->val.size(), n);
        return n;
    }
    int left_value = calculate_tree_node_values(ast->left);
    int right_value = calculate_tree_node_values(ast->right);
        if (ast->token_type != NUMBER) {
            result = calculator(ast->val[0],  left_value,  right_value);
        }
    return result;  
    
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
    printf("the result is %d",calculate_tree_node_values(ast));
    return 0;
}
