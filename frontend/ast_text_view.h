//
// Created by linfeng on 2022/4/8.
//

#ifndef GODCC_FRONTEND_AST_TEXT_VIEW_H_
#define GODCC_FRONTEND_AST_TEXT_VIEW_H_
#include <stack>

#include "../tools/njson.hpp"
#include "visitor.h"

class AstVisitor : public Visitor {
 private:
  std::stack<nlohmann::json *> json;

 public:
  AstVisitor();
  void VisitTranslationUnit(TranslationUnitAst *ast) override;
  void VisitCompUnitAst(CompUnitAst *) override;
  void VisitFuncDefAst(FuncDefAst *) override;
  void VisitFuncTypeAst(FuncTypeAst *) override;
  void VisitFuncFParamAst(FuncFParamAst *) override;
  void VisitFuncFParamListAst(FuncFParamListAst *) override;

  void VisitFuncRParamListAst(FuncRParamListAst *) override;

  void VisitBlockAst(BlockAst *) override;
  void VisitBlockItemListAst(BlockItemListAst *) override;
  void VisitBlockItem(BlockItemAst *) override;

  void VisitStmtAst(StmtAst *) override;
  void VisitIfStmt(IfStmtAst *) override;
  void VisitWhileStmt(WhileStmtAst *) override;
  void VisitForStmt(ForStmtAst *) override;

  void VisitExp(ExpAst *) override;

  void VisitDecl(DeclAst *) override;

  void VisitConstDecl(ConstDeclAst *) override;
  void VisitConstDefList(ConstDefListAst *) override;
  void VisitConstDef(ConstDefAst *) override;
  void VisitLVal(LValAst *) override;

  void VisitVarDecl(VarDeclAst *) override;
  void VisitVarDefList(VarDefListAst *) override;
  void VisitVarDef(VarDefAst *) override;

  void VisitArrayExprList(ArrayExprListAst *) override;
  void VisitInitVal(InitValAst *) override;
  void VisitInitValList(InitValListAst *) override;
  void VisitPostfixExprAst(PostfixExprAst *) override;
  void VisitBinaryExpAst(BinaryExprAst *) override;
  void VisitUnaryExpAst(UnaryExprAst *) override;
  void VisitUnaryOpAst(UnaryOpAst *) override;
  void VisitPrimaryExpAst(PrimaryExprAst *) override;
  void VisitNumberAst(NumberAst *) override;
  void VisitIdentifierAst(IdentifierAst *) override;
  void VisitStringAst(StringAst *) override;
};
#endif//GODCC_FRONTEND_AST_TEXT_VIEW_H_
