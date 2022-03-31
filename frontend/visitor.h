//
// Created by linfeng on 2022/3/12.
//

#ifndef GODCC_VISITOR_H
#define GODCC_VISITOR_H

#include <memory>

#include "../IR/IR.h"
#include "../log/log.h"
#include "ast.h"

class CompUnitAst;

class FuncDefAst;

class FuncTypeAst;

class BlockAst;

class StmtAst;

class ExpAst;

class UnaryExprAst;

class UnaryOpAst;
class BinaryExprAst;
class AddExprAst;

class MulExprAst;
class LAndExprAst;
class LOrExprAst;
class RelExprAst;
class EqExprAst;

class NumberAst;

class PrimaryExprAst;

class IdentifierAst;

class Visitor {
 public:
  virtual void VisitCompUnitAst(CompUnitAst *) = 0;

  virtual void VisitFuncDefAst(FuncDefAst *) = 0;

  virtual void VisitFuncTypeAst(FuncTypeAst *) = 0;

  virtual void VisitBlockAst(BlockAst *) = 0;

  virtual void VisitStmtAst(StmtAst *) = 0;

  virtual void VisitExp(ExpAst *) = 0;
  virtual void VisitBinaryExpAst(BinaryExprAst *) =0;
  virtual void VisitUnaryExpAst(UnaryExprAst *) = 0;

  virtual void VisitAddExpAst(AddExprAst *) = 0;
  virtual void VisitMulExpAst(MulExprAst *) = 0;
  virtual void VisitLOrExpAst(LOrExprAst *) = 0;

  virtual void VisitLAndExpAst(LAndExprAst *) = 0;
  virtual void VisitEqExpAst(EqExprAst *) = 0;
  virtual void VisitRelExpAst(RelExprAst *) = 0;

  virtual void VisitUnaryOpAst(UnaryOpAst *) = 0;

  virtual void VisitPrimaryExpAst(PrimaryExprAst *) = 0;

  virtual void VisitNumberAst(NumberAst *) = 0;

  virtual void VisitIdentifierAst(IdentifierAst *) = 0;
};

class AstVisitor : public Visitor {
 public:
  void VisitCompUnitAst(CompUnitAst *) override;

  void VisitFuncDefAst(FuncDefAst *) override;

  void VisitFuncTypeAst(FuncTypeAst *) override;

  void VisitBlockAst(BlockAst *) override;

  void VisitStmtAst(StmtAst *) override;

  void VisitExp(ExpAst *) override;
  void VisitBinaryExpAst(BinaryExprAst *) override;
  void VisitUnaryExpAst(UnaryExprAst *) override;

  void VisitAddExpAst(AddExprAst *) override;

  void VisitMulExpAst(MulExprAst *) override;
  void VisitUnaryOpAst(UnaryOpAst *) override;
  void VisitLOrExpAst(LOrExprAst *) override;
  void VisitLAndExpAst(LAndExprAst *) override;
  void VisitEqExpAst(EqExprAst *) override;
  void VisitRelExpAst(RelExprAst *) override;
  void VisitPrimaryExpAst(PrimaryExprAst *) override;

  void VisitNumberAst(NumberAst *) override;

  void VisitIdentifierAst(IdentifierAst *) override;
};

//// 符号表建立
//class BuildSymbolVisitor : public Visitor {
//public:
//    void VisitCompUnitAst( CompUnitAst*) override;
//    void VisitFuncDefAst( FuncDefAst*)  override;
//    void VisitFuncTypeAst( FuncTypeAst*)  override;
//    void VisitBlockAst( BlockAst*) override;
//    void VisitStmtAst( StmtAst*) override;
//    void VisitExp(ExpAst*) override;
//    void VisitUnaryExpAst(UnaryExprAst*) override;
//    void VisitBinaryExpAst(BinaryExprAst*) override;
//    void VisitUnaryOpAst(UnaryOpAst*) override;
//    void VisitPrimaryExpAst(PrimaryExprAst*) override;
//    void VisitNumberAst(NumberAst*) override;
//    void VisitIdentifierAst( IdentifierAst*) override;
//};

// 中间代码生成
class IRGeneratorVisitor : public Visitor {
 public:
  std::shared_ptr<Program> programIr = nullptr;
  unsigned int register_num_ = 0;//记录分配的寄存器
 public:
  void VisitCompUnitAst(CompUnitAst *) override;

  void VisitFuncDefAst(FuncDefAst *) override;

  void VisitFuncTypeAst(FuncTypeAst *) override;

  void VisitBlockAst(BlockAst *) override;

  void VisitStmtAst(StmtAst *) override;

  void VisitExp(ExpAst *) override;
  void VisitBinaryExpAst(BinaryExprAst *) override;
  void VisitUnaryExpAst(UnaryExprAst *) override;
  void VisitAddExpAst(AddExprAst *) override;
  void VisitMulExpAst(MulExprAst *) override;
  void VisitLOrExpAst(LOrExprAst *) override;
  void VisitLAndExpAst(LAndExprAst *) override;
  void VisitEqExpAst(EqExprAst *) override;
  void VisitRelExpAst(RelExprAst *) override;

  void VisitUnaryOpAst(UnaryOpAst *) override;

  void VisitPrimaryExpAst(PrimaryExprAst *) override;

  void VisitNumberAst(NumberAst *) override;

  void VisitIdentifierAst(IdentifierAst *) override;
};

BinaryOp to_BinaryOp(const std::string_view &op);

#endif//GODCC_VISITOR_H
