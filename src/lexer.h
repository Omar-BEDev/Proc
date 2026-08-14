#ifndef LEXER_H
#define LEXER_H
#include <string_view>
#define ASSCIADDITION 43
#define ASSCISUBSTRACTION 45
#define ASSCIMULTIPLACATION 42
#define ASSCIDIVISION 47
#define ASSCiSPACE 32
#define ASSCIOPENBRACKETS 40
#define ASSCICLOSEBRACKETS 41
#define ASSCINEWLINE 10
#include <string>
#include "token.h"

using namespace std;

string extract_file_content(const char* path);
Token** lexer(string_view content);
#endif
