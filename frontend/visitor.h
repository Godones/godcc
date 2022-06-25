//
// Created by linfeng on 2022/3/12.
//

#ifndef GODCC_VISITOR_H
#define GODCC_VISITOR_H

#include <algorithm>
#include <memory>

#include "../IR/IR.h"
#include "ast.h"
#include "tools/log.h"

class CompUnitAst;
class TranslationUnitAst;

class FuncDefAst;
class FuncTypeAst;

class FuncFParamAst;
class FuncFParamListAst;

class FuncRParamListAst;

class BlockAst;
class BlockItemListAst;
class BlockItemAst;

class StmtAst;
class WhileStmtAst;
class ForStmtAst;
class IfStmtAst;

class ExpAst;
class UnaryExprAst;
class UnaryOpAst;
class PostfixExprAst;

class BinaryExprAst;
class NumberAst;
class PrimaryExprAst;
class IdentifierAst;
class DeclAst;

class ConstDeclAst;
class ConstDefListAst;
class ConstDefAst;
class LValAst;

class VarDeclAst;
class VarDefAst;
class VarDefListAst;

class ArrayExprListAst;
class InitValListAst;
class InitValAst;

class Visitor {
 public:
  virtual void VisitTranslationUnit(TranslationUnitAst *ast) = 0;
  virtual void VisitCompUnitAst(CompUnitAst *) = 0;
  virtual void VisitFuncDefAst(FuncDefAst *) = 0;
  virtual void VisitFuncTypeAst(FuncTypeAst *) = 0;
  virtual void VisitFuncFParamListAst(FuncFParamListAst *) = 0;
  virtual void VisitFuncFParamAst(FuncFParamAst *) = 0;
  virtual void VisitFuncRParamListAst(FuncRParamListAst *) = 0;
  virtual void VisitBlockAst(BlockAst *) = 0;
  virtual void VisitBlockItemListAst(BlockItemListAst *) = 0;
  virtual void VisitBlockItem(BlockItemAst *) = 0;
  virtual void VisitStmtAst(StmtAst *) = 0;
  virtual void VisitIfStmt(IfStmtAst *) = 0;
  virtual void VisitWhileStmt(WhileStmtAst *) = 0;
  virtual void VisitForStmt(ForStmtAst *) = 0;
  virtual void VisitExp(ExpAst *) = 0;
  virtual void VisitDecl(DeclAst *) = 0;
  virtual void VisitConstDecl(ConstDeclAst *) = 0;
  virtual void VisitConstDefList(ConstDefListAst *) = 0;
  virtual void VisitConstDef(ConstDefAst *) = 0;
  virtual void VisitLVal(LValAst *) = 0;
  virtual void VisitVarDecl(VarDeclAst *) = 0;
  virtual void VisitVarDefList(VarDefListAst *) = 0;
  virtual void VisitVarDef(VarDefAst *) = 0;
  virtual void VisitArrayExprList(ArrayExprListAst *) = 0;
  virtual void VisitInitValList(InitValListAst *) = 0;
  virtual void VisitInitVal(InitValAst *) = 0;
  virtual void VisitBinaryExpAst(BinaryExprAst *) = 0;
  virtual void VisitUnaryExpAst(UnaryExprAst *) = 0;
  virtual void VisitUnaryOpAst(UnaryOpAst *) = 0;
  virtual void VisitPrimaryExpAst(PrimaryExprAst *) = 0;
  virtual void VisitNumberAst(NumberAst *) = 0;
  virtual void VisitIdentifierAst(IdentifierAst *) = 0;
  virtual void VisitPostfixExprAst(PostfixExprAst *) = 0;
};

BinaryOp to_BinaryOp(const std::string_view &op);

#endif//GODCC_VISITOR_H
