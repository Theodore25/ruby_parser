#ifndef VISITOR_H
#define VISITOR_H

class Node;
class NInteger;
class NString;
class NIdentifier;
class NSlice;
class NBinop;
class NArray;
class NComparator;
class NIfStmt;
class NLoop;
class NBreakStmt;
class NReturnStmt;
class NDefinition;
class NMethodCall;
class NArgList;
class NParamList;
class NAssignment;
class NBlock;

class Visitor {
public:
  virtual void visitInteger(NInteger &integer) = 0;
  virtual void visitString(NString &str) = 0;
  virtual void visitIdentifier(NIdentifier &ident) = 0;
  virtual void visitSlice(NSlice &slice) = 0;
  virtual void visitBinop(NBinop &binop) = 0;
  virtual void visitDefinition(NDefinition &def) = 0;
  virtual void visitReturnStmt(NReturnStmt &ret) = 0;
  virtual void visitBreakStmt(NBreakStmt &brk) = 0;
  virtual void visitMethodCall(NMethodCall &meth) = 0;
  virtual void visitParamList(NParamList &list) = 0;
  virtual void visitArgList(NArgList &list) = 0;
  virtual void visitAssignment(NAssignment &assign) = 0;
  virtual void visitArray(NArray &array) = 0;
  virtual void visitComparator(NComparator &comparator) = 0;
  virtual void visitIfStmt(NIfStmt &stmt) = 0;
  virtual void visitLoop(NLoop &loop) = 0;
  virtual void visitBlock(NBlock &block) = 0;
};

#endif