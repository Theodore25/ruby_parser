#include "pretty.h"
#include "node.h"
#include <iostream>
#include <typeindex>
#include <typeinfo>

using namespace std;

void Pretty::visitInteger(NInteger &integer) {
  os << "Visit Integer: " << integer.value << "\n";
}

void Pretty::visitString(NString &str) {
  os << "Visit String: " << str.value << "\n";
}

void Pretty::visitIdentifier(NIdentifier &ident) {
  os << "Visit Identifier: " << ident.name << "\n";
}

void Pretty::visitSlice(NSlice &slice) {
  os << "Visit Slice:\n";
  slice.id.accept(*this);
  slice.idx.accept(*this);
}

void Pretty::visitBinop(NBinop &binop) {
  os << "Visit Binop: " << binop.op << "\n";
  binop.left.accept(*this);
  binop.right.accept(*this);
}

void Pretty::visitMethodCall(NMethodCall &meth) {
  os << "BEGIN Visit Meth Call:\n";
  meth.id.accept(*this);
  meth.arguments.accept(*this);
  os << "END Visit Meth Call:\n";
}

void Pretty::visitParamList(NParamList &list) {
  os << "Visit Param List\n";
  for (Node *expr : list.params)
    expr->accept(*this);
}

void Pretty::visitAssignment(NAssignment &assign) {
  os << "BEGIN Visit Assignment\n";
  assign.lhs.accept(*this);
  assign.rhs.accept(*this);
  os << "END Visit Assignment\n";
}

void Pretty::visitComparator(NComparator &comparator) {
  os << "Visit Comparator: " << comparator.op << "\n";
  comparator.left.accept(*this);
  comparator.right.accept(*this);
}

void Pretty::visitIfStmt(NIfStmt &stmt) {
  os << "BEGIN Visit IfStatement:\n";
  stmt.comparator.accept(*this);
  stmt.block.accept(*this);
  if (stmt.else_block != nullptr) {
    os << "Visit ElseStatement:\n";
    stmt.else_block->accept(*this);
  }
  os << "END Visit IfStatement:\n";
}

void Pretty::visitLoop(NLoop &loop) {
  os << "BEGIN Visit Loop:\n";
  loop.comparator.accept(*this);
  loop.block.accept(*this);
  os << "END Visit Loop:\n";
}

void Pretty::visitArray(NArray &array) {
  os << "Visit Array\n";
  for (Node *a : array.data) {
    a->accept(*this);
  }
}

void Pretty::visitBlock(NBlock &block) {
  os << "BEGIN Visit Block\n";
  for (Node *stmt : block.statements) {
    stmt->accept(*this);
  }
  os << "END Visit Block\n";
}

void Pretty::visitArgList(NArgList &list) {
  os << "Visit Args List\n";
  for (Node *a : list.args) {
    a->accept(*this);
  }
}

void Pretty::visitBreakStmt(NBreakStmt &brk) { os << "Visit Break\n"; }

void Pretty::visitReturnStmt(NReturnStmt &ret) {
  os << "BEGIN Visit Return\n";
  if (ret.ret_stmt != nullptr) {
    ret.ret_stmt->accept(*this);
  }
  os << "END Visit Return\n";
}

void Pretty::visitDefinition(NDefinition &def) {
  os << "BEGIN Visit Definition:\n";
  def.id.accept(*this);
  def.args.accept(*this);
  def.block.accept(*this);
  os << "END Visit Definition:\n";
}