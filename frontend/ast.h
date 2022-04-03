//
// Created by linfeng on 2022/3/11.
//

#ifndef GODCC_AST_H
#define GODCC_AST_H

#include <iostream>
#include <memory>
#include <ostream>
#include <deque>
#include "visitor.h"

class Visitor;
class CompUnitAst;
class FuncDefAst;
class FuncTypeAst;
class BlockAst;
class BlockUpAst;
class BlockItemAst;
class StmtAst;
class ExpAst;
class BinaryExprAst;
class UnaryExprAst;
class PrimaryExprAst;
class UnaryOpAst;
class IdentifierAst;

class DeclAst;
class ConstDeclAst;
class ConstDefAst;
class ConstDefUpAst;
class LValAst;

class VarDeclAst;
class VarDefAst;
class VarDefUpAst;


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
  std::shared_ptr<Ast> ident;            //标识符
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


// Block         ::= "{" {BlockItem} "}";
// BlockItem     ::= Decl | Stmt;
// ---->
//Block         ::= "{" BlockItemUp "}";
//BlockItemUp   ::= BlcokItem | BlockItemUp BlockItem
//BlockItem     ::= Decl | Stmt;
class BlockAst : public Ast {
 public:
  std::deque<std::shared_ptr<Ast>> blockItems;
  ~BlockAst() override = default;
  static std::deque<std::shared_ptr<Ast>>GetFromBlockItemUp(BlockUpAst*);
  void accept(Visitor *) override;
};

class BlockUpAst:public Ast{
public:
	std::shared_ptr<Ast> blockItem;
	std::shared_ptr<Ast> blockUp;
	bool isBlockUp = false;
	BlockUpAst(std::shared_ptr<Ast> left,std::shared_ptr<Ast> right);
	BlockUpAst(std::shared_ptr<Ast> left);
	std::shared_ptr<Ast> getBlockItem() const;
	~BlockUpAst() override = default;
	void accept(Visitor *) override;
};
class BlockItemAst:public Ast{
public:
	std::shared_ptr<Ast> item;
	~BlockItemAst() override = default;
	void accept(Visitor *) override;
};

enum class StmtType {
  kReturn,
  kDecl,
};

const char * StmtTypeToString(StmtType &type);

class StmtAst : public Ast {
 public:
  StmtType type;
  std::shared_ptr<Ast> l_val;
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
// EqExp       ::= RelExp | EqExp ("==" | "!=") RelExp;
// LAndExp     ::= RelExp | LAndExp "&&" RelExp;
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
	IDENTIFIER,
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

// 声明
// Decl          ::= ConstDecl;
class DeclAst : public Ast{
 public:
  std::shared_ptr<Ast> decl;
  ~DeclAst() override = default;
  void accept(Visitor *) override;
};


// 常量声明
// ConstDecl     ::= "const" INT ConstDefUp ";";
class ConstDeclAst : public Ast{
 public:
	std::deque<std::shared_ptr<Ast>> constDefs;
	std::string_view dataType;
	~ConstDeclAst() override = default;
	static std::deque<std::shared_ptr<Ast>>GetFromConstDefUpAst(ConstDefUpAst*);
	void accept(Visitor *) override;
};

//	常量定义列表
// ConstDefUp    ::= ConstDef  | ConstDefUp "," ConstDef
class ConstDefUpAst: public Ast{
 public:
    std::shared_ptr<Ast> constDefUp;
	std::shared_ptr<Ast> constDef;
	bool isConstDefUp = false;
	~ConstDefUpAst() override = default;
	ConstDefUpAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
	ConstDefUpAst(std::shared_ptr<Ast> right);
	std::shared_ptr<Ast> getConstDef() const;
	void accept(Visitor *) override;
};

// 常量定义
class ConstDefAst : public Ast{
 public:
  std::shared_ptr<Ast> ident; //标识符
  std::shared_ptr<Ast> const_val; //常量值 == 常量表达式
  ~ConstDefAst() override = default;
  void accept(Visitor *) override;
};

class VarDeclAst : public Ast{
 public:
  std::deque<std::shared_ptr<Ast>> varDefs;
  std::string_view dataType;
  ~VarDeclAst() override = default;
  static std::deque<std::shared_ptr<Ast>> GetFromVarDefUpAst(VarDefUpAst*);
  void accept(Visitor *) override;
};

class VarDefUpAst : public Ast{
 public:
  std::shared_ptr<Ast> varDefUp;
  std::shared_ptr<Ast> varDef;
  bool isVarDefUp = false;
  ~VarDefUpAst() override = default;
  VarDefUpAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  VarDefUpAst(std::shared_ptr<Ast> right);
  std::shared_ptr<Ast> getVarDef() const;
  void accept(Visitor *) override;
};

class VarDefAst : public Ast{
 public:
  bool is_expr = false;
  std::shared_ptr<Ast> ident; //标识符
  std::shared_ptr<Ast> var_expr; //表达式
  ~VarDefAst() override = default;
  void accept(Visitor *) override;
};


// 左值节点---其对应一个已经声明过的标识符
class LValAst : public Ast{
 public:
  std::shared_ptr<Ast> l_val;// --> IdentifierAst
  ~LValAst() override = default;
  void accept(Visitor *) override;
};


#endif//GODCC_AST_H
