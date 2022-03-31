//
// Created by linfeng on 2022/3/11.
//

#include "ast.h"

#include <utility>

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

void StmtAst::accept(Visitor *visitor) {
  visitor->VisitStmtAst(this);
}

void ExpAst::accept(Visitor *visitor) {
  visitor->VisitExp(this);
}

void AddExprAst::accept(Visitor *visitor) {
  visitor->VisitAddExpAst(this);
}
AddExprAst::AddExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op)
	: left(std::move(left)),
	  right(std::move(right)),
	  op(op),
	  is_add(true) {}
AddExprAst::AddExprAst(std::shared_ptr<Ast> right)
	: right(std::move(right)),
	  is_add(false) {}

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
void MulExprAst::accept(Visitor *visitor) {
  visitor->VisitMulExpAst(this);
}
MulExprAst::MulExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op)
	: left(std::move(left)),
	  right(std::move(right)),
	  op(op),
	  is_mul(true) {}
MulExprAst::MulExprAst(std::shared_ptr<Ast> right)
	: right(std::move(right)),
	  is_mul(false) {}

LOrExprAst::LOrExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op)
	: left(std::move(left)),
	  right(std::move(right)),
	  op(op),
	  is_lor(true) {}
LOrExprAst::LOrExprAst(std::shared_ptr<Ast> right)
	: right(std::move(right)),
	  is_lor(false) {}
void LOrExprAst::accept(Visitor *visitor) {
  visitor->VisitLOrExpAst(this);
}
LAndExprAst::LAndExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op)
	: left(std::move(left)),
	  right(std::move(right)),
	  op(op),
	  is_land(true) {}
LAndExprAst::LAndExprAst(std::shared_ptr<Ast> right)
	: right(std::move(right)),
	  is_land(false) {}
void LAndExprAst::accept(Visitor *visitor) {
  visitor->VisitLAndExpAst(this);
}

EqExprAst::EqExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op)
	: left(std::move(left)),
	  right(std::move(right)),
	  op(op),
	  is_eq(true) {}
EqExprAst::EqExprAst(std::shared_ptr<Ast> right)
	: right(std::move(right)),
	  is_eq(false) {}
void EqExprAst::accept(Visitor *visitor) {
  visitor->VisitEqExpAst(this);
}
RelExprAst::RelExprAst(std::shared_ptr<Ast> left, std::shared_ptr<Ast> right, std::string_view op)
	: left(std::move(left)),
	  right(std::move(right)),
	  op(op),
	  is_rel(true) {}
RelExprAst::RelExprAst(std::shared_ptr<Ast> right)
	: right(std::move(right)),
	  is_rel(false) {}
void RelExprAst::accept(Visitor *visitor) {
  visitor->VisitRelExpAst(this);
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
