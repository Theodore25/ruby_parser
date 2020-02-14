#include "util.h"

extern char *yytext;
extern int yylineno;
extern int yyleng;
extern int yycolumn;
extern const char *yytname;
extern const char *get_token_name(int t);

std::string lexer_log(int lxm) {
  return "Token(type: " + std::string(get_token_name(lxm)) + ", value: '" +
         yytext + "', loc<" + std::to_string(yylineno) + ", " +
         std::to_string(yycolumn - yyleng) + ">)";
}
