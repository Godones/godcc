//
// Created by linfeng on 2022/3/11.
//

#include "ast.h"

#include <utility>
const char * StmtTypeToString(StmtType &type){
  switch (type) {
	case StmtType::kReturn: return "Return";
	case StmtType::kDecl: return "Decl";
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
// 递归从BlockItemUp中将表达式抽取到一个列表中
std::deque<std::shared_ptr<Ast>> BlockAst::GetFromBlockItemUp(BlockUpAst*block_up_ast) {
  if (block_up_ast == nullptr) {
	return {};
  }
  std::deque<std::shared_ptr<Ast>> block_items;
  block_items.push_front(block_up_ast->getBlockItem());
  while (block_up_ast->isBlockUp) {
	block_up_ast = dynamic_cast<BlockUpAst*>(block_up_ast->blockUp.get());
	block_items.push_front(block_up_ast->getBlockItem());
  }
  return block_items;
}
BlockUpAst::BlockUpAst(std::shared_ptr<Ast>left,std::shared_ptr<Ast>right)
	:blockUp(std::move(left)),blockItem(std::move(right)),isBlockUp(true) {}

BlockUpAst::BlockUpAst(std::shared_ptr<Ast>left)
	:blockItem(std::move(left)), isBlockUp(false) {}

std::shared_ptr<Ast> BlockUpAst::getBlockItem() const{
  return blockItem;
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
BinaryExprAst::BinaryExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right,BinaryType type,std::string_view op)
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
std::deque<std::shared_ptr<Ast>> ConstDeclAst::GetFromConstDefUpAst(ConstDefUpAst *const_def_up_ast) {
  if (const_def_up_ast == nullptr) {
	return {};
  }
  std::deque<std::shared_ptr<Ast>> const_defs;
  const_defs.push_front(const_def_up_ast->getConstDef());
  while (const_def_up_ast->isConstDefUp) {
	const_def_up_ast = dynamic_cast<ConstDefUpAst*>(const_def_up_ast->constDefUp.get());
	const_defs.push_front(const_def_up_ast->getConstDef());
  }
  return const_defs;
}

void ConstDefAst::accept(Visitor *visitor) {
  visitor->VisitConstDef(this);
}
void LValAst::accept(Visitor *visitor) {
  visitor->VisitLVal(this);
}

ConstDefUpAst::ConstDefUpAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: constDefUp(std::move(left)),
	  constDef(std::move(right)),
	  isConstDefUp(true){}
ConstDefUpAst::ConstDefUpAst(std::shared_ptr<Ast> right): constDef(std::move(right)){}

// 带up的都为空实现，因为这些只是中间辅助手段
// 最后并不会用到
void BlockUpAst::accept(Visitor *) {}
void ConstDefUpAst::accept(Visitor *visitor) {}
void VarDefUpAst::accept(Visitor *visitor) {}



std::shared_ptr<Ast> ConstDefUpAst::getConstDef() const {
  return constDef;
}
std::deque<std::shared_ptr<Ast>> VarDeclAst::GetFromVarDefUpAst(VarDefUpAst *val_def_up_ast) {
  if (val_def_up_ast == nullptr) {
	return {};
  }
  std::deque<std::shared_ptr<Ast>> val_defs;
  val_defs.push_front(val_def_up_ast->getVarDef());
  while (val_def_up_ast->isVarDefUp) {
	val_def_up_ast = dynamic_cast<VarDefUpAst*>(val_def_up_ast->varDefUp.get());
	val_defs.push_front(val_def_up_ast->getVarDef());
  }
  return val_defs;
}
void VarDeclAst::accept(Visitor *visitor) {
  visitor->VisitVarDecl(this);
}
VarDefUpAst::VarDefUpAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: varDefUp(std::move(left)),
	  varDef(std::move(right)),
	  isVarDefUp(true){}
VarDefUpAst::VarDefUpAst(std::shared_ptr<Ast> right): varDef(std::move(right)){}
std::shared_ptr<Ast> VarDefUpAst::getVarDef() const {
  return varDef;
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


std::deque<std::shared_ptr<Ast>> FuncFParamAst::GetParamsFromFuncFParaUp(FuncFParamUpAst *func_f_param_up_ast) {
  if (func_f_param_up_ast == nullptr) {
	return {};
  }
  std::deque<std::shared_ptr<Ast>> func_f_params;
  func_f_params.push_front(func_f_param_up_ast->getFuncFParam());
  while (func_f_param_up_ast->isFuncFParamUp) {
	func_f_param_up_ast = dynamic_cast<FuncFParamUpAst*>(func_f_param_up_ast->funcFParamUp.get());
	func_f_params.push_front(func_f_param_up_ast->getFuncFParam());
  }
  return func_f_params;
}

void FuncFParamAst::accept(Visitor *visitor) {
  visitor->VisitFuncFParamAst(this);
}
FuncFParamUpAst::FuncFParamUpAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: funcFParamUp(std::move(left)),
	  funcFParamDef(std::move(right)),
	  isFuncFParamUp(true){}
FuncFParamUpAst::FuncFParamUpAst(std::shared_ptr<Ast> left)
	: funcFParamDef(std::move(left)){}
void FuncFParamUpAst::accept(Visitor *) {}
std::shared_ptr<Ast> FuncFParamUpAst::getFuncFParam() const {
  return funcFParamDef;
}
void FuncFParamDefAst::accept(Visitor *visitor) {
  visitor->VisitFuncFParamDefAst(this);
}
void FuncRParamAst::accept(Visitor *visitor) {
  visitor->VisitFuncRParamAst(this);
}
std::deque<std::shared_ptr<Ast>> FuncRParamAst::GetParamsFromFuncRParaUp(FuncRParamUpAst *func_r_param_up_ast) {
  if (func_r_param_up_ast== nullptr){
	return {};
  }
  std::deque<std::shared_ptr<Ast>> func_r_params;
  func_r_params.push_front(func_r_param_up_ast->getFuncRParam());
  while (func_r_param_up_ast->isFuncFParamUp) {
	func_r_param_up_ast = dynamic_cast<FuncRParamUpAst*>(func_r_param_up_ast->funcRParamUp.get());
	func_r_params.push_front(func_r_param_up_ast->getFuncRParam());
  }
  return func_r_params;
}
FuncRParamUpAst::FuncRParamUpAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right)
	: funcRParamUp(std::move(left)),
	 expr(std::move(right)),
	 isFuncFParamUp(true){}
FuncRParamUpAst::FuncRParamUpAst(std::shared_ptr<Ast> left)
	  :expr(std::move(left)){}
void FuncRParamUpAst::accept(Visitor *) {}
std::shared_ptr<Ast> FuncRParamUpAst::getFuncRParam() const {
  return expr;
}
void TranslationUnitAst::accept(Visitor *visitor) {
  visitor->VisitTranslationUnit(this);
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
