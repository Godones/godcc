//
// Created by linfeng on 2022/3/11.
//

#ifndef GODCC_AST_H
#define GODCC_AST_H

#include <deque>
#include <iostream>
#include <memory>
#include <ostream>
#include <variant>
#include "visitor.h"

using IntString = std::variant<int, std::string>;

class Visitor;
class TranslationUnitAst;
class CompUnitAst;

class FuncDefAst;
class FuncTypeAst;
class FuncFParamAst;
class FuncFParamListAst;

class FuncRParamListAst;

class BlockAst;
class BlockItemAst;
class StmtAst;
class IfStmtAst;
class WhileStmtAst;
class ForStmtAst;

class ExpAst;
class BinaryExprAst;
class UnaryExprAst;
class PostfixExprAst;
class PrimaryExprAst;
class UnaryOpAst;
class IdentifierAst;

class DeclAst;
class ConstDeclAst;
class ConstDefAst;
class LValAst;

class VarDeclAst;
class VarDefAst;
class VarDefListAst;

class InitValListAst;
class InitValAst;
class ArrayExprListAst;

class Ast {
 public:
  int line = 0;
  int column = 0;
  virtual ~Ast() = default;
  virtual void accept(Visitor *) = 0;
};

class TranslationUnitAst : public Ast {
 public:
  std::shared_ptr<Ast> comp_unit;
  ~TranslationUnitAst() override = default;
  void accept(Visitor *visitor) override;
};

//CompUnit ::= T
//	| CompUnit T
//	T  ::= Decl | FuncDef
class CompUnitAst : public Ast {
 public:
  std::shared_ptr<Ast> comp_unit;
  std::shared_ptr<Ast> comp_unit_Item;

 public:
  ~CompUnitAst() override = default;
  CompUnitAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  CompUnitAst(std::shared_ptr<Ast> right);
  void accept(Visitor *) override;
};

class FuncDefAst : public Ast {
 public:
  std::shared_ptr<Ast> funcType;     //类型
  std::shared_ptr<Ast> ident;        //标识符
  std::shared_ptr<Ast> funcParamList;//参数列表 -->需要判空
  std::shared_ptr<Ast> block;        //函数体
 public:
  ~FuncDefAst() override = default;
  void accept(Visitor *) override;
};

class FuncFParamListAst : public Ast {
 public:
  std::shared_ptr<Ast> funcFParam;
  std::shared_ptr<Ast> funcFParamList;

 public:
  ~FuncFParamListAst() override = default;
  void accept(Visitor *) override;
  FuncFParamListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  FuncFParamListAst(std::shared_ptr<Ast> right);
};

//FuncFParam   ::= FuncType IDENT
//				| FuncType IDENT "[" "]"
//				| FuncType IDENT "[" "]" ArrayExpList
//				| FuncType IDENT  ArrayExpList
class FuncFParamAst : public Ast {
 public:
  std::shared_ptr<Ast> funcType;
  std::shared_ptr<Ast> ident;
  std::shared_ptr<Ast> array_expr_list;
  bool first_no_dim = true;
  //当first_no_dim = true 说明第一维未标大小 属于第二三中情况
  //当first_no_dim = false 说明属于第一四种情况
 public:
  ~FuncFParamAst() override = default;
  void accept(Visitor *) override;
};

class FuncTypeAst : public Ast {
 public:
  const char *type;

 public:
  ~FuncTypeAst() override = default;
  void accept(Visitor *) override;
};

DataType getFuncType(const FuncTypeAst &func_type);

class FuncRParamListAst : public Ast {
  //参数列表
 public:
  std::string func_name;//函数名,用于语义检查
  std::shared_ptr<Ast> funcRParamListAst;
  std::shared_ptr<Ast> expr;
  FuncRParamListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  FuncRParamListAst(std::shared_ptr<Ast> left);
  void accept(Visitor *) override;
};

// Block         ::= "{" {BlockItem} "}";
// BlockItem     ::= Decl | Stmt;
// ---->
//Block         ::= "{" BlockItemList "}";
//BlockItemList   ::= BlcokItem | BlockItemList BlockItem
//BlockItem     ::= Decl | Stmt;
class BlockAst : public Ast {
 public:
  std::shared_ptr<Ast> block_item_list;
  ~BlockAst() override = default;
  void accept(Visitor *) override;
};

class BlockItemListAst : public Ast {
 public:
  std::shared_ptr<Ast> block_item_list;
  std::shared_ptr<Ast> block_item;
  BlockItemListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  BlockItemListAst(std::shared_ptr<Ast> left);
  ~BlockItemListAst() override = default;
  void accept(Visitor *) override;
};

class BlockItemAst : public Ast {
 public:
  std::shared_ptr<Ast> item;
  ~BlockItemAst() override = default;
  void accept(Visitor *) override;
};

enum class StmtType {
  kReturn,
  kAssign,
  kBlock,
  kExpr,
  kIf,
  kWhile,
  kBreak,
  kContinue,
  kFor,
};

const char *StmtTypeToString(StmtType &type);
// Stmt ::= LVal "=" Exp ";"
//	      | [Exp] ";"
//	      | Block
//		  | "return" [Exp] ";";
//		  |"if" "(" Exp ")" Stmt ["else" Stmt]
// []表示重复0或1次
class StmtAst : public Ast {
 public:
  StmtType type;
  std::shared_ptr<Ast> l_val = nullptr;
  std::shared_ptr<Ast> expr = nullptr;
  ~StmtAst() override = default;
  void accept(Visitor *) override;
};

class IfStmtAst : public Ast {
 public:
  std::shared_ptr<Ast> expr;
  std::shared_ptr<Ast> stmt;
  std::shared_ptr<Ast> elseStmt;
  ~IfStmtAst() override = default;
  void accept(Visitor *) override;
};

class WhileStmtAst : public Ast {
 public:
  std::shared_ptr<Ast> expr;
  std::shared_ptr<Ast> stmt;
  ~WhileStmtAst() override = default;
  void accept(Visitor *) override;
};

// for(expr;expr;expr)stmt
class ForStmtAst : public Ast {
 public:
  std::shared_ptr<Ast> expr1;
  std::shared_ptr<Ast> expr2;
  std::shared_ptr<Ast> expr3;
  std::shared_ptr<Ast> stmt;
  ~ForStmtAst() override = default;
  void accept(Visitor *) override;
};


// 表达式节点
class ExpAst : public Ast {
 public:
  IntString value;              // 用于编译期值
  bool have_value = false;// 用于编译期值
  DataType data_type;     // 用于语义检查,在声明语句中需要判断两边类型是否匹配
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

enum class BinaryType {
  kLor,
  kAnd,
  kEq,
  kRel,
  kMul,
  kAdd,
};
const char *BinaryTypeToString(BinaryType &type);
class BinaryExprAst : public Ast {
 public:
  IntString value;              // 用于编译期值
  bool have_value = false;// 用于编译期值
  DataType data_type;     // 用于语义检查,在声明语句中需要判断两边类型是否匹配
  std::shared_ptr<Ast> left;
  std::shared_ptr<Ast> right;
  BinaryType type;
  const char *op{};

 public:
  ~BinaryExprAst() override = default;
  virtual void accept(Visitor *) override;
  BinaryExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, BinaryType type, const char *op);
  BinaryExprAst(std::shared_ptr<Ast> right, BinaryType type);
};

enum class UnaryType {
  kPostfix,
  kUnary,
  kCall,
  kBDec,
  kBInc,
};
// 一元表达式
// UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp | IDENT "(" [FuncRParams] ")";
const char *UnaryTypeToString(UnaryType &type);
class UnaryExprAst : public Ast {
 public:
  IntString value;              // 用于编译期值
  bool have_value = false;// 用于编译期值
  DataType data_type;     // 用于语义检查,在声明语句中需要判断两边类型是否匹配

  std::shared_ptr<Ast> unaryOp;  //符号 --只有类型为unary时才有
  std::shared_ptr<Ast> unaryExpr;//表达式
  UnaryType unaryType;           //类型
  ~UnaryExprAst() override = default;
  void accept(Visitor *) override;
};


enum class PostfixType {
  kPrimary,
  kBDec,
  kBInc,
};
class PostfixExprAst : public Ast {
 public :
  IntString value;              // 用于编译期值
  bool have_value = false;// 用于编译期值
  DataType data_type;     // 用于语义检查,在声明语句中需要判断两边类型是否匹配
  std::shared_ptr<Ast> postfixExpr;
  PostfixType postfixType; //kBDec,kBInc
  ~PostfixExprAst() override = default;
  void accept(Visitor *) override;
};


enum class PrimaryType {
  EXP,//(exp) --- 带括号的表达式
  NUMBER,
  IDENTIFIER,
  STRING,//字符串
};
class PrimaryExprAst : public Ast {
 public:
 public:
  IntString value;              // 用于编译期值
  bool have_value = false;// 用于编译期值
  DataType data_type;     // 用于语义检查,在声明语句中需要判断两边类型是否匹配

  PrimaryType primaryType;
  std::shared_ptr<Ast> primaryExpr;
  ~PrimaryExprAst() override = default;
  void accept(Visitor *) override;
};

// 数字节点
class NumberAst : public Ast {
 public:
  IntString value;
  ~NumberAst() override = default;
  void accept(Visitor *) override;
};

class StringAst : public Ast {
 public:
  IntString value;
  ~StringAst() override = default;
  void accept(Visitor *) override;
};



// 一元运算符
class UnaryOpAst : public Ast {
 public:
  const char *op;
  ~UnaryOpAst() override = default;
  void accept(Visitor *) override;
  UnaryOpAst(const char *op_);
  UnaryOpAst() =default;
};

class IdentifierAst : public Ast {
 public:
  const char *name;

 public:
  ~IdentifierAst() override = default;
  void accept(Visitor *) override;
};

// 声明
// Decl          ::= ConstDecl;
class DeclAst : public Ast {
 public:
  std::shared_ptr<Ast> decl;
  ~DeclAst() override = default;
  void accept(Visitor *) override;
};

// 常量声明
// ConstDecl     ::= "const" INT ConstDefList ";";
class ConstDeclAst : public Ast {
 public:
  std::shared_ptr<Ast> const_def_list;
  std::shared_ptr<Ast> data_type;
  ~ConstDeclAst() override = default;
  void accept(Visitor *) override;
};

//	常量定义列表
// ConstDefList    ::= ConstDef  | ConstDefList "," ConstDef
class ConstDefListAst : public Ast {
 public:
  std::shared_ptr<Ast> const_def;
  std::shared_ptr<Ast> const_def_list;
  ~ConstDefListAst() override = default;
  ConstDefListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  ConstDefListAst(std::shared_ptr<Ast> right);
  void accept(Visitor *) override;
};

// 常量定义
class ConstDefAst : public Ast {
 public:
  std::shared_ptr<Ast> ident;          //标识符
  std::shared_ptr<Ast> array_expr_list;// a [][] = {1,2,3}
  std::shared_ptr<Ast> const_val;      //常量值 == 常量表达式
  ~ConstDefAst() override = default;
  void accept(Visitor *) override;
};

//ArrayExpList  ::=  ""
//	::= "[" Exp "]"
//	| ArrayExpList "[" Exp "]"
class ArrayExprListAst : public Ast {
 public:
  std::vector<int>array_num;//记录数组的值
  std::shared_ptr<Ast> array_expr_list;
  std::shared_ptr<Ast> array_expr;
  ~ArrayExprListAst() override = default;
  ArrayExprListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  ArrayExprListAst(std::shared_ptr<Ast> right);
  void accept(Visitor *) override;
};

class InitValAst : public Ast {
 public:
  std::vector<int> values;//用于存放初始化列表的值
  std::shared_ptr<Ast> init_val;
  std::shared_ptr<Ast> init_val_list;
  ~InitValAst() override = default;
  InitValAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  InitValAst(std::shared_ptr<Ast> right);
  void accept(Visitor *) override;
};

class InitValListAst : public Ast {
 public:
  std::vector<int> values;//用于存放初始化列表的值
  std::shared_ptr<Ast> expr_init_val;
  ~InitValListAst() override = default;
  void accept(Visitor *) override;
};

class VarDeclAst : public Ast {
 public:
  std::shared_ptr<Ast> var_def_list;
  std::shared_ptr<Ast> dataType;
  ~VarDeclAst() override = default;
  void accept(Visitor *) override;
};

class VarDefListAst : public Ast {
 public:
  std::shared_ptr<Ast> varDefList;
  std::shared_ptr<Ast> varDef;
  ~VarDefListAst() override = default;
  VarDefListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right);
  VarDefListAst(std::shared_ptr<Ast> right);
  void accept(Visitor *) override;
};

class VarDefAst : public Ast {
 public:
  std::shared_ptr<Ast> ident;//标识符
  std::shared_ptr<Ast> array_expr_list;
  std::shared_ptr<Ast> var_expr;//表达式
  ~VarDefAst() override = default;
  void accept(Visitor *) override;
};

// 左值节点---其对应一个已经声明过的标识符
class LValAst : public Ast {
 public:
  IntString value;
  bool have_value;
  DataType data_type;// 用于语义检查,在声明语句中需要判断两边类型是否匹配
  std::shared_ptr<Ast> l_val;          // --> IdentifierAst
  std::shared_ptr<Ast> array_expr_list;//a[][]
  ~LValAst() override = default;
  void accept(Visitor *) override;
};

std::string  getString(IntString value);
int getInt(IntString value);

#endif//GODCC_AST_H
