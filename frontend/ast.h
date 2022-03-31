//
// Created by linfeng on 2022/3/11.
//

#ifndef GODCC_AST_H
#define GODCC_AST_H

#include <iostream>
#include <memory>
#include <ostream>

#include "visitor.h"

class Visitor;
class CompUnitAst;
class FuncDefAst;
class FuncTypeAst;
class BlockAst;
class StmtAst;
class ExpAst;
class BinaryExprAst;
class UnaryExprAst;
class PrimaryExprAst;
class UnaryOpAst;
class IdentifierAst;
class Ast {
 public:
  int spaces = 0;
  virtual ~Ast() = default;

  virtual void setSpaces(int spaces) {
	this->spaces = spaces;
  }
  virtual void printSpace() {
	for (int i = 0; i < spaces; i++) {
	  std::cout << " ";
	}
  }
  virtual void accept(Visitor *) = 0;
};

class CompUnitAst : public Ast {
 public:
  std::shared_ptr<Ast> funcDef;

 public:
  ~CompUnitAst() override = default;

  void accept(Visitor *) override;
};

class FuncDefAst : public Ast {
 public:
  std::shared_ptr<Ast> funcType;//类型
  std::string ident;            //标识符
								//    std::shared_ptr<><Ast> param;//参数
  std::shared_ptr<Ast> block;   //函数体
 public:
  ~FuncDefAst() override = default;

  void accept(Visitor *) override;
};

class FuncTypeAst : public Ast {
 public:
  std::string type;
  //    std::shared_ptr<><Ast> param;
 public:
  ~FuncTypeAst() override = default;

  void accept(Visitor *) override;
};

class BlockAst : public Ast {
 public:
  std::shared_ptr<Ast> stmts;

  ~BlockAst() override = default;

  void accept(Visitor *) override;
};

class StmtAst : public Ast {
 public:
  std::shared_ptr<Ast> expr;

  ~StmtAst() override = default;

  void accept(Visitor *) override;
};

// 表达式节点
class ExpAst : public Ast {
 public:
  std::shared_ptr<Ast> realExpr;

 public:
  ~ExpAst() override = default;
  void accept(Visitor *) override;
};

// 二元关系表达式

// AddExp      ::= MulExp | AddExp ("+" | "-") MulExp;
// MulExp      ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
// RelExp      ::= AddExp | RelExp ("<" | "<=" | ">" | ">=") AddExp;
//EqExp       ::= RelExp | EqExp ("==" | "!=") RelExp;
//LAndExp     ::= RelExp | LAndExp "&&" RelExp;
// LOrExp      ::= LAndExp | LOrExp "||" LAndExp;

class BinaryExprAst : public Ast {
 public:
  std::shared_ptr<Ast> left;
  std::shared_ptr<Ast> right;
  std::string_view op;
  bool is_two_op = false;

 public:
  ~BinaryExprAst() override = default;
  virtual void accept(Visitor *) override;
  BinaryExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op);
  BinaryExprAst(std::shared_ptr<Ast> right);
};



// 一元表达式
class UnaryExprAst : public Ast {
 public:
  enum class UnaryType {
	PRIMARY,
	UNARY,
  };

 public:
  std::shared_ptr<Ast> unaryOp;  //符号 --只有类型为unary时才有
  std::shared_ptr<Ast> unaryExpr;//表达式
  UnaryType unaryType;           //类型
  ~UnaryExprAst() override = default;
  void accept(Visitor *) override;
};

class PrimaryExprAst : public Ast {
 public:
  enum class PrimaryType {
	EXP,//(exp) --- 带括号的表达式
	NUMBER,
  };

 public:
  PrimaryType primaryType;
  std::shared_ptr<Ast> primaryExpr;
  ~PrimaryExprAst() override = default;
  void accept(Visitor *) override;
};

// 数字节点
class NumberAst : public Ast {
 public:
  int value;

  ~NumberAst() override = default;

  void accept(Visitor *) override;
};

// 一元运算符
class UnaryOpAst : public Ast {
 public:
  std::string_view op;
  ~UnaryOpAst() override = default;
  void accept(Visitor *) override;
};

class IdentifierAst : public Ast {
 public:
  std::string_view name;

 public:
  ~IdentifierAst() override = default;

  void accept(Visitor *) override;
};

#endif//GODCC_AST_H
