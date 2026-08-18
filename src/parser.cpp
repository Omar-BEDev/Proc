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
TreeNode* parse_one(string_view val, string_view operation) {
    TreeNode *n = new TreeNode{};
    n->val = operation;
    TreeNode *n2 = new TreeNode{};
    n2->val = val;
    n->left = n2;
    return n;
}
static TreeNode* parse_two(string_view val1, string_view val2, string_view operation) {
   TreeNode *n = new TreeNode{};
    n->val = operation;
    TreeNode *n2 = new TreeNode{};
    n2->val = val1;
    n->left = n2;
    TreeNode *n3 = new TreeNode{};
    n2->val = val2;
    n->right = n3;
    return n;
}
static TreeNode* parse_bracket(string_view val, string_view bracket) {

}

TreeNode* Ast(Token* tokens,uint size) { 
    TreeNode *node = new TreeNode{};
    TreeNode *first_Node = new TreeNode{};
    int power = 0;
    int operaton_index = 0;
    uint i = 0;
    while(i < size) {
        if (tokens[i].token_type == NUMBER) {
            int current_power = searchPower(tokens[i+1].token_type);
            if (power < current_power && current_power == 1) {
                operaton_index++;
                if (operaton_index == 1) {
                    first_Node->val = tokens[i].val;
                }

                TreeNode *n = parse_one(tokens[i].val, tokens[i+1].val);
                node->left = n;
                node = n;
            }
            if (tokens[i].token_type == NUMBER) {
            int current_power = searchPower(tokens[i+1].token_type);
            if (power < current_power && current_power == 2) {
    
                TreeNode *n = parse_two(tokens[i].val, tokens[i+2].val,tokens[i+1].val);
                node->right = n;
                node = n;
            }
            
        }
        i++;
    }
}

}
