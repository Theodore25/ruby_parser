%{
#include "parser.h"
#include "util.h"

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

extern int yylineno;
int yycolumn = 1;

void add_column(int yyleng);
void lexer_error(const char *message);

%}

%option noyywrap nodefault yylineno
%option outfile="lexer.cpp" header-file="lexer.h"

digit      [0-9]
letter     [a-zA-Z]
ws         [ \t]+
id         ("_"|{letter})("_"|{letter}|{digit})*
sign       [-+]
comment    #.*
string     \"[^\"\n]*\"
integer    (0|([1-9]{digit}*))

%%

"\n"        { yycolumn = 1; }
{ws}        { add_column(yyleng); }

{comment}   ;

"+"         { add_column(yyleng); return TOKEN(TADD); }
"-"         { add_column(yyleng); return TOKEN(TSUB); }
"*"         { add_column(yyleng); return TOKEN(TMUL); }
"/"         { add_column(yyleng); return TOKEN(TDIV); }

"!="        { add_column(yyleng); return TOKEN(TNEQ); }
"=="        { add_column(yyleng); return TOKEN(TEQ); }
"<"         { add_column(yyleng); return TOKEN(TLT); }
">"         { add_column(yyleng); return TOKEN(TGT); }
"<="        { add_column(yyleng); return TOKEN(TLE); }
">="        { add_column(yyleng); return TOKEN(TGE); }

"("         { add_column(yyleng); return TOKEN(TLPR); }
")"         { add_column(yyleng); return TOKEN(TRPR); }
"["         { add_column(yyleng); return TOKEN(TLBR); }
"]"         { add_column(yyleng); return TOKEN(TRBR); }

"="         { add_column(yyleng); return TOKEN(TASSIGN); }
","         { add_column(yyleng); return TOKEN(TCOMMA); }

"if"        { add_column(yyleng); return TOKEN(TIF); }
"else"      { add_column(yyleng); return TOKEN(TELSE); }
"while"     { add_column(yyleng); return TOKEN(TWHILE); }
"do"        { add_column(yyleng); return TOKEN(TDO); }
"end"       { add_column(yyleng); return TOKEN(TEND); }
"break"     { add_column(yyleng); return TOKEN(TBREAK); }
"def"       { add_column(yyleng); return TOKEN(TDEF); }
"return"    { add_column(yyleng); return TOKEN(TRETURN); }

{id}        { add_column(yyleng); SAVE_TOKEN; return TID; }
{integer}   { add_column(yyleng); SAVE_TOKEN; return TINTEGER; }
{string}    { add_column(yyleng); SAVE_TOKEN; return TSTRING; }
.           { lexer_error("unknown literal"); yyterminate(); }

%%

void lexer_error(const char* message){
  printf("%slexer_error: %s, loc<%d:%d>\n", BOLD_RED, message, yylineno, yycolumn);
}

void add_column(int yyleng) {
  yycolumn += yyleng;
}


