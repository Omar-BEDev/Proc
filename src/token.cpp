#include <string_view>
#include <unordered_map>
#include "token.h"
using namespace std;


unordered_map<char, TokenType> symbols {
    {'*', MULTIPLACATION},
    {'+', ADDITION},
    {'-', SUBSTRACTION},
    {'/', DIVISION},
    {'(', OPEN_BRACKETS},
    {')', CLOSE_BRACKETS},
};


TokenType checkIsTokenAvailable(char symbol) {
    auto it = symbols.find(symbol);
    if (it == symbols.end()) {
        return NOT_FOUND;
    }
    return it->second;
}
