//
// Created by linfeng on 2022/4/8.
//

#ifndef GODCC_FRONTEND_AST_TO_IR_H_
#define GODCC_FRONTEND_AST_TO_IR_H_
// 中间代码生成
#include "visitor.h"


class IRGeneratorVisitor : public Visitor {
 public:
  std::shared_ptr<Program> programIr = nullptr;
  unsigned int register_num_ = 0;//记录分配的寄存器
 public:
  void VisitTranslationUnit(TranslationUnitAst *ast) override;

  void VisitCompUnitAst(CompUnitAst *) override;
  void VisitFuncDefAst(FuncDefAst *) override;
  void VisitFuncTypeAst(FuncTypeAst *) override;
  void VisitFuncFParamAst(FuncFParamAst *) override;
  void VisitFuncFParamDefAst(FuncFParamDefAst *) override;
  void VisitFuncRParamAst(FuncRParamAst *) override;


  void VisitBlockAst(BlockAst *) override;
  void VisitBlockItem(BlockItemAst *) override;

  void VisitStmtAst(StmtAst *) override;
  void VisitIfStmt(IfStmtAst *) override;
  void VisitWhileStmt(WhileStmtAst *) override;

  void VisitExp(ExpAst *) override;


  void VisitDecl(DeclAst *) override;
  void VisitConstDecl(ConstDeclAst *) override;
  void VisitConstDef(ConstDefAst *) override;
  void VisitLVal(LValAst *) override;

  void VisitVarDecl(VarDeclAst *) override;
  void VisitVarDef(VarDefAst *) override;

  void VisitArrayExprList(ArrayExprListAst*) override;
  void VisitInitVal(InitValAst *) override;
  void VisitInitValList(InitValListAst *) override;

  void VisitBinaryExpAst(BinaryExprAst *) override;
  void VisitUnaryExpAst(UnaryExprAst *) override;
  void VisitUnaryOpAst(UnaryOpAst *) override;
  void VisitPrimaryExpAst(PrimaryExprAst *) override;
  void VisitNumberAst(NumberAst *) override;
  void VisitIdentifierAst(IdentifierAst *) override;
};

#endif//GODCC_FRONTEND_AST_TO_IR_H_
