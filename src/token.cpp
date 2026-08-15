#include "token.h"
#include <unordered_map>
using namespace std;

unordered_map<char, TokenType> symbols{
    {'*', MULTIPLACATION}, {'+', ADDITION},      {'-', SUBSTRACTION},
    {'/', DIVISION},       {'(', OPEN_BRACKETS}, {')', CLOSE_BRACKETS},
};
unordered_map<TokenType, Type> types = {
    {MULTIPLACATION, OPERATOR},   {ADDITION, OPERATOR},
    {SUBSTRACTION, OPERATOR},     {DIVISION, OPERATOR},
    {OPEN_BRACKETS, PUNCTUATION}, {CLOSE_BRACKETS, PUNCTUATION},

};

TokenType checkIsTokenAvailable(char symbol) {
  auto it = symbols.find(symbol);
  if (it == symbols.end()) {
    return NOT_FOUND;
  }
  return it->second;
}
Type checkSymbolType(TokenType tokenType) {
    auto it = types.find(tokenType);
    if (it == types.end()) {
        return NOT_TYPE;
    }
    return it->second;
}
