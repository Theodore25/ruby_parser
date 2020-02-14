#include "node.h"
#include "pretty.h"
#include "util.h"

using namespace std;

extern NBlock *root;
extern FILE *yyin;

extern int yyparse();
extern int yylex();

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Ops!:(\n");
    return -1;
  }

  if ((yyin = fopen(argv[1], "r")) == NULL) {
    printf("\nCannot open file %s.\n", argv[1]);
    return -1;
  }

  // int lxm;
  // while ((lxm = yylex())) {
  //   cout << BOLD_GREEN << lexer_log(lxm) << endl;
  // }

  yyparse();

  ostringstream tree;
  if (root) {
    Pretty visitor(tree);
    visitor.visitBlock(*root);
    cout << tree.str();
  }

  fclose(yyin);
  return 0;
}
