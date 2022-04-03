//
// Created by linfeng on 2022/3/11.
//

#include "ast.h"

#include <utility>
const char * StmtTypeToString(StmtType &type){
  switch (type) {
	case StmtType::kReturn: return "Return";
	case StmtType::kDecl: return "Decl";
  }
  return "";
}

void CompUnitAst::accept(Visitor *visitor) {
  visitor->VisitCompUnitAst(this);
}

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
BinaryExprAst::BinaryExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op)
	: left(std::move(left)),
	  right(std::move(right)),
	  op(op),
	  is_two_op(true) {}
BinaryExprAst::BinaryExprAst(std::shared_ptr<Ast> right)
	: right(std::move(right)),
	  is_two_op(false) {}


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
