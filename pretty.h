#ifndef PRETTY_H
#define PRETTY_H

#include "visitor.h"
#include <sstream>

#define BOLD_COLOR "\e[1m\e[37m"

class Pretty : Visitor {
  std::ostream &os;

public:
  Pretty(std::ostream &ostream) : os(ostream) { os << BOLD_COLOR; }
  void visitInteger(NInteger &integer);
  void visitString(NString &str);
  void visitIdentifier(NIdentifier &ident);
  void visitSlice(NSlice &slice);
  void visitMethodCall(NMethodCall &meth);
  void visitDefinition(NDefinition &def);
  void visitReturnStmt(NReturnStmt &ret);
  void visitBreakStmt(NBreakStmt &brk);
  void visitBinop(NBinop &binop);
  void visitParamList(NParamList &list);
  void visitArgList(NArgList &list);
  void visitAssignment(NAssignment &assign);
  void visitComparator(NComparator &comparator);
  void visitArray(NArray &array);
  void visitIfStmt(NIfStmt &stmt);
  void visitLoop(NLoop &loop);
  void visitBlock(NBlock &block);
};

#endif