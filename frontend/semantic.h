//
// Created by linfeng on 2022/5/3.
//

#ifndef GODCC_SEMANTIC_H
#define GODCC_SEMANTIC_H
#include <stack>

#include "visitor.h"

class SemanticVisitor : public Visitor {
  DataType type_current = DataType::kNone;// 记录当前的数据类型
  bool while_flag = false;                // 记录是否在while循环中
  bool func_flag = false;                 // 记录函数是否以return结束
  std::string current_func_name;          // 记录当前函数名
 public:
  SymbolTable *globalSymbolTable;

 public:
  SemanticVisitor();
  ~SemanticVisitor();
  void VisitTranslationUnit(TranslationUnitAst *ast) override;
  void VisitCompUnitAst(CompUnitAst *) override;

  void VisitFuncDefAst(FuncDefAst *) override;
  void VisitFuncTypeAst(FuncTypeAst *) override;
  void VisitFuncFParamListAst(FuncFParamListAst *) override;
  void VisitFuncFParamAst(FuncFParamAst *) override;

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
  void VisitInitValList(InitValListAst *) override;
  void VisitInitVal(InitValAst *) override;

  void VisitBinaryExpAst(BinaryExprAst *) override;
  void VisitUnaryExpAst(UnaryExprAst *) override;
  void VisitPostfixExprAst(PostfixExprAst *) override;
  void VisitUnaryOpAst(UnaryOpAst *) override;
  void VisitPrimaryExpAst(PrimaryExprAst *) override;
  void VisitNumberAst(NumberAst *) override;
  void VisitIdentifierAst(IdentifierAst *) override;
};
int calculate(int left, int right, std::string_view op);
#endif//GODCC_SEMANTIC_H
