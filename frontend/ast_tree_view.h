//
// Created by linfeng on 2022/4/13.
//

#ifndef GODCC_FRONTEND_AST_TREE_VIEW_H_
#define GODCC_FRONTEND_AST_TREE_VIEW_H_
#include "../tools/dot.h"
#include "ast.h"
class AstViewVisitor : public Visitor {
 private:
  //  GodJSon j_son_;
  GDot j_son_;

 public:
  AstViewVisitor() = default;
  explicit AstViewVisitor(GDot j_son);
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
  void VisitVarDef(VarDefAst *) override;
  void VisitVarDefList(VarDefListAst *) override;

  void VisitArrayExprList(ArrayExprListAst *) override;
  void VisitInitVal(InitValAst *) override;
  void VisitInitValList(InitValListAst *) override;

  void VisitBinaryExpAst(BinaryExprAst *) override;
  void VisitUnaryExpAst(UnaryExprAst *) override;
  void VisitPostfixExprAst(PostfixExprAst *) override;

  void VisitUnaryOpAst(UnaryOpAst *) override;
  void VisitPrimaryExpAst(PrimaryExprAst *) override;
  void VisitNumberAst(NumberAst *) override;
  void VisitStringAst(StringAst *) override;
  void VisitIdentifierAst(IdentifierAst *) override;
};
#endif//GODCC_FRONTEND_AST_TREE_VIEW_H_
