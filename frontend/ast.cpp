//
// Created by linfeng on 2022/3/11.
//

#include "ast.h"

#include <utility>

DataType getFuncType(const FuncTypeAst& func_type){
  if (strcmp(func_type.type,"int") == 0)
	return DataType::kInt;
  else if (strcmp(func_type.type,"float") == 0)
	return DataType::kFloat;
  else if (strcmp(func_type.type,"void") == 0)
    return DataType::kVoid;
  else
	INFO("the func type is not supported");
}

const char * StmtTypeToString(StmtType &type){
  switch (type) {
	case StmtType::kReturn: return "Return";
	case StmtType::kAssign: return "Assign";
	case StmtType::kExpr: return "Expr";
	case StmtType::kBlock: return "Block";
	case StmtType::kIf: return "If";
	case StmtType::kWhile: return "While";
	case StmtType::kBreak: return "Break";
	case StmtType::kContinue: return "Continue";
  }
  return "";
}
const char * BinaryTypeToString(BinaryType &type){
  switch (type) {
	case BinaryType::kLor: return "Lor";
	case BinaryType::kAnd: return "And";
	case BinaryType::kEq: return "Eq";
	case BinaryType::kRel: return "Rel";
	case BinaryType::kMul: return "Mul";
	case BinaryType::kAdd: return "Add";
  }
  return "";
}
const char *UnaryTypeToString(UnaryType &type){
  switch (type) {
	case UnaryType::kPrimary: return "Primary";
	case UnaryType::kUnary: return "Unary";
	case UnaryType::kCall: return "Call";
  }
  return "";
}

void TranslationUnitAst::accept(Visitor *visitor) {
  visitor->VisitTranslationUnit(this);
}

void CompUnitAst::accept(Visitor *visitor) {
  visitor->VisitCompUnitAst(this);
}
CompUnitAst::CompUnitAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	:comp_unit(std::move(left)), comp_unit_Item(std::move(right)) {}
CompUnitAst::CompUnitAst(std::shared_ptr<Ast> right)
	:comp_unit(nullptr), comp_unit_Item(std::move(right)) {}

void FuncDefAst::accept(Visitor *visitor) {

  visitor->VisitFuncDefAst(this);
}

void FuncTypeAst::accept(Visitor *visitor) {
  visitor->VisitFuncTypeAst(this);
}

void BlockAst::accept(Visitor *visitor) {
  visitor->VisitBlockAst(this);
}

BlockItemListAst::BlockItemListAst(std::shared_ptr<Ast>left,std::shared_ptr<Ast>right)
	:block_item_list(std::move(left)),block_item(std::move(right)){}

BlockItemListAst::BlockItemListAst(std::shared_ptr<Ast>left)
	:block_item(std::move(left)) {}
void BlockItemListAst::accept(Visitor *visitor) {
  visitor->VisitBlockItemListAst(this);
}

void BlockItemAst::accept(Visitor  *visitor) {
  visitor->VisitBlockItem(this);
}

void StmtAst::accept(Visitor *visitor) {
  visitor->VisitStmtAst(this);
}

void ExpAst::accept(Visitor *visitor) {
  visitor->VisitExp(this);
}

void UnaryExprAst::accept(Visitor *visitor) {
  visitor->VisitUnaryExpAst(this);
}

void PrimaryExprAst::accept(Visitor *visitor) {
  visitor->VisitPrimaryExpAst(this);
}

void NumberAst::accept(Visitor *visitor) {
  visitor->VisitNumberAst(this);
}

void UnaryOpAst::accept(Visitor *visitor) {
  visitor->VisitUnaryOpAst(this);
}

void IdentifierAst::accept(Visitor *visitor) {
  visitor->VisitIdentifierAst(this);
}

void BinaryExprAst::accept(Visitor *visitor) {
  visitor->VisitBinaryExpAst(this);
}
BinaryExprAst::BinaryExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right,BinaryType type,const char * op)
	: left(std::move(left)),
	  right(std::move(right)),
	  type(type),
	  op(op) {}


BinaryExprAst::BinaryExprAst(std::shared_ptr<Ast> right,BinaryType type)
	: right(std::move(right)),
	  type(type){}

void DeclAst::accept(Visitor *visitor) {
  visitor->VisitDecl(this);
}

void ConstDeclAst::accept(Visitor *visitor) {
  visitor->VisitConstDecl(this);
}

void ConstDefAst::accept(Visitor *visitor) {
  visitor->VisitConstDef(this);
}
void LValAst::accept(Visitor *visitor) {
  visitor->VisitLVal(this);
}

ConstDefListAst::ConstDefListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: const_def_list(std::move(left)),
	  const_def(std::move(right)){}
ConstDefListAst::ConstDefListAst(std::shared_ptr<Ast> right): const_def(std::move(right)){}


void ConstDefListAst::accept(Visitor *visitor) {
  visitor->VisitConstDefList(this);
}


void VarDeclAst::accept(Visitor *visitor) {
  visitor->VisitVarDecl(this);
}
VarDefListAst::VarDefListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: varDefList(std::move(left)),
	  varDef(std::move(right)){}


VarDefListAst::VarDefListAst(std::shared_ptr<Ast> right)
: varDef(std::move(right)){}

void VarDefListAst::accept(Visitor *visitor) {
  visitor->VisitVarDefList(this);
}


void VarDefAst::accept(Visitor *visitor) {
  visitor->VisitVarDef(this);
}
void IfStmtAst::accept(Visitor *visitor) {
  visitor->VisitIfStmt(this);
}
void WhileStmtAst::accept(Visitor *visitor) {
  visitor->VisitWhileStmt(this);
}

void FuncFParamAst::accept(Visitor *visitor) {
  visitor->VisitFuncFParamAst(this);
}
FuncFParamListAst::FuncFParamListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: funcFParamList(std::move(left)),
	  funcFParam(std::move(right)){}
FuncFParamListAst::FuncFParamListAst(std::shared_ptr<Ast> left)
	: funcFParam(std::move(left)){}


void FuncFParamListAst::accept(Visitor *visitor) {
  visitor->VisitFuncFParamListAst(this);
}

FuncRParamListAst::FuncRParamListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: funcRParamListAst(std::move(left)),
	 expr(std::move(right)){}
FuncRParamListAst::FuncRParamListAst(std::shared_ptr<Ast> left)
	  :expr(std::move(left)){}
void FuncRParamListAst::accept(Visitor *Visitor) {
  Visitor->VisitFuncRParamListAst(this);
}



ArrayExprListAst::ArrayExprListAst(std::shared_ptr<Ast> right)
	: array_expr(std::move(right)){}
ArrayExprListAst::ArrayExprListAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: array_expr(std::move(right)),
	  array_expr_list(std::move(left)){}
void ArrayExprListAst::accept(Visitor *visitor) {
	visitor->VisitArrayExprList(this);
}
InitValAst::InitValAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: init_val_list(std::move(right)),
	  init_val(std::move(left)){}
InitValAst::InitValAst(std::shared_ptr<Ast> right)
	: init_val_list(std::move(right)){}


void InitValAst::accept(Visitor *visitor) {
  visitor->VisitInitVal(this);
}
void InitValListAst::accept(Visitor *visitor) {
  visitor->VisitInitValList(this);
}
