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
