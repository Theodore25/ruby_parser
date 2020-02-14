#ifndef NODE_H
#define NODE_H

#include "visitor.h"
#include <iostream>
#include <vector>

typedef std::vector<Node *> NodeList;

class Node {
public:
  virtual ~Node() {}
  virtual void accept(Visitor &v) = 0;
};

class NInteger : public Node {
public:
  long long value;
  NInteger(long long value) : value(value) {}
  void accept(Visitor &v) override { v.visitInteger(*this); }
};

class NIdentifier : public Node {
public:
  std::string name;
  NIdentifier(const std::string &name) : name(name) {}
  void accept(Visitor &v) override { v.visitIdentifier(*this); }
};

class NString : public Node {
public:
  std::string value;
  NString(std::string value) : value(value) {}
  void accept(Visitor &visitor) override { visitor.visitString(*this); }
};

class NSlice : public Node {
public:
  Node &id;
  Node &idx;
  NSlice(Node &id, Node &idx) : id(id), idx(idx) {}
  void accept(Visitor &visitor) override { visitor.visitSlice(*this); }
};

class NMethodCall : public Node {
public:
  Node &id;
  Node &arguments;
  NMethodCall(Node &id, Node &arguments) : id(id), arguments(arguments) {}
  void accept(Visitor &v) override { v.visitMethodCall(*this); }
};

class NBinop : public Node {
public:
  Node &left;
  Node &right;
  std::string op;
  NBinop(Node &left, Node &right, const std::string &op)
      : left(left), right(right), op(op) {}
  void accept(Visitor &visitor) override { visitor.visitBinop(*this); }
};

class NParamList : public Node {
public:
  NodeList params;
  NParamList() {}
  void accept(Visitor &visitor) override { visitor.visitParamList(*this); }
};

class NAssignment : public Node {
public:
  Node &lhs;
  Node &rhs;
  NAssignment(Node &lhs, Node &rhs) : lhs(lhs), rhs(rhs) {}
  void accept(Visitor &v) override { v.visitAssignment(*this); }
};

class NComparator : public Node {
public:
  Node &left;
  Node &right;
  std::string op;

  NComparator(Node &left, Node &right, const std::string &op)
      : left(left), right(right), op(op) {}

  void accept(Visitor &visitor) override { visitor.visitComparator(*this); }
};

class NIfStmt : public Node {
public:
  Node &comparator;
  Node &block;
  Node *else_block;

  NIfStmt(Node &comparator, Node &block, Node *else_block = nullptr)
      : comparator(comparator), block(block), else_block(else_block) {}
  void accept(Visitor &visitor) override { visitor.visitIfStmt(*this); }
};

class NArray : public Node {
public:
  NodeList data;
  NArray() {}
  void accept(Visitor &visitor) override { visitor.visitArray(*this); }
};

class NLoop : public Node {
public:
  Node &comparator;
  Node &block;
  NLoop(Node &comparator, Node &block) : comparator(comparator), block(block) {}
  void accept(Visitor &visitor) override { visitor.visitLoop(*this); }
};

class NDefinition : public Node {
public:
  Node &id;
  Node &args;
  Node &block;

  NDefinition(Node &id, Node &args, Node &block)
      : id(id), args(args), block(block) {}
  void accept(Visitor &v) override { v.visitDefinition(*this); }
};

class NArgList : public Node {
public:
  NodeList args;
  NArgList() {}
  void accept(Visitor &visitor) override { visitor.visitArgList(*this); }
};

class NBreakStmt : public Node {
public:
  NBreakStmt() {}
  void accept(Visitor &visitor) override { visitor.visitBreakStmt(*this); }
};

class NReturnStmt : public Node {
public:
  Node *ret_stmt;
  NReturnStmt(Node *ret_stmt = nullptr) : ret_stmt(ret_stmt) {}
  void accept(Visitor &visitor) override { visitor.visitReturnStmt(*this); }
};

class NBlock : public Node {
public:
  NodeList statements;
  NBlock() {}
  void accept(Visitor &v) override { v.visitBlock(*this); }
};

#endif