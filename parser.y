
%code requires {
  #include<string>
  #include<vector>
  #include "node.h"

}

%{
#include "util.h"
#include "node.h"
NBlock *root;

extern int yylineno;
extern int yycolumn;
extern int yyleng;
extern int yylex();
void yyerror(const char *message);

%}

%output  "parser.cpp"
%defines "parser.h"

%union {
  Node *node;
  NBlock *block;
  NIdentifier *ident;
  NParamList * params;
  NArgList * arglist;
  NArray * array;
  std::string *string;
  int token;
}

%token-table
%token<token> TADD TSUB TMUL TDIV

%token<token> TNEQ TEQ
%token<token> TLT TGT
%token<token> TLE TGE

%token<token> TLPR TRPR
%token<token> TLBR TRBR

%token<token> TASSIGN TCOMMA

%token<token> TIF TELSE
%token<token> TWHILE TDO TEND TBREAK
%token<token> TDEF TRETURN

%token<string> TID TINTEGER TSTRING

%left TADD TSUB
%left TMUL TDIV

%start program

%type <block> program stmts
%type <params> params
%type <arglist> arglist
%type <array> array

%type <node> stmt assignment_stmt
%type <node> ident literals
%type <node> integer string
%type <node> expr methodcall
%type <node> slice index
%type <node> binop term
%type <node> if_stmt comparator
%type <node> loop definition
%type <node> return_stmt

%%

program : /* blank */ { root = new NBlock(); }
        | stmts { root = $1; }
        ;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($1); }
      | stmts stmt { $1->statements.push_back($2); }
      ;

stmt : assignment_stmt
     | methodcall
     | if_stmt
     | loop
     | definition
     | TBREAK { $$ = new NBreakStmt(); };
     | return_stmt
     ;


return_stmt : TRETURN expr{ $$ = new NReturnStmt($2); }
            | TRETURN { $$ = new NReturnStmt(); }
            ;

definition : TDEF ident TLPR arglist TRPR stmts TEND { $$ = new NDefinition(*$2, *$4, *$6); }; 

arglist : /*blank*/  { $$ = new NArgList(); }
      | ident { $$ = new NArgList(); $$->args.push_back($1); }
      | arglist TCOMMA ident  { $1->args.push_back($3); }
      ; 

loop  : TWHILE comparator TDO stmts TEND { $$ = new NLoop(*$2, *$4); };


if_stmt : TIF comparator stmts TEND { $$ = new NIfStmt(*$2, *$3); }
        | TIF comparator stmts TELSE stmts TEND { $$ = new NIfStmt(*$2, *$3, $5); };

comparator  : term TLT term { $$ = new NComparator(*$1, *$3, "<"); }
            | term TGT term { $$ = new NComparator(*$1, *$3, ">"); }
            | term TLE term { $$ = new NComparator(*$1, *$3, "<="); }
            | term TGE term { $$ = new NComparator(*$1, *$3, ">="); }
            | term TEQ term { $$ = new NComparator(*$1, *$3, "=="); }
            | term TNEQ term { $$ = new NComparator(*$1, *$3, "!="); }
            ;

assignment_stmt : ident TASSIGN expr { $$ = new NAssignment(*$1, *$3); }
            | slice TASSIGN expr { $$ = new NAssignment(*$1, *$3); }
            ;

expr  : literals
      | ident
      | methodcall
      | slice
      | binop
      | TLBR array TRBR { $$ = $2; }
      ;

array : term { $$ = new NArray(); $$->data.push_back($1); } 
      | array TCOMMA term { $1->data.push_back($3); }
      ;

binop : term TADD term { $$ = new NBinop(*$1, *$3, "+"); }
      | term TSUB term { $$ = new NBinop(*$1, *$3, "-"); }
      | term TMUL term { $$ = new NBinop(*$1, *$3, "*"); }
      | term TDIV term { $$ = new NBinop(*$1, *$3, "/"); }
      ;

term  : ident 
      | integer 
      | slice 
      | methodcall
      | TLPR binop TRPR { $$ = $2; };

methodcall : ident TLPR params TRPR { $$ = new NMethodCall(*$1, *$3); }

params : /*blank*/  { $$ = new NParamList(); }
      | expr { $$ = new NParamList(); $$->params.push_back($1); }
      | params TCOMMA expr  { $1->params.push_back($3); }
      ;

slice : ident TLBR index TRBR { $$ = new NSlice(*$1, *$3); };

index : integer | ident;

literals  : integer | string ;

string : TSTRING { $$ = new NString(*$1); delete $1; };

integer : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; };
      | TSUB TINTEGER { $$ = new NInteger(-1 * atol($2->c_str())); delete $2; };

ident : TID { $$ = new NIdentifier(*$1); delete $1; };

%%

void yyerror(const char *s) { printf("%sparser_error: %s, loc<%d:%d>\n", BOLD_RED, s, yylineno, yycolumn); }

const char* get_token_name(int t) { return yytname[YYTRANSLATE(t)]; }
