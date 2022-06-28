//
// Created by linfeng on 2022/4/8.
//

#ifndef GODCC_FRONTEND_AST_TO_IR_H_
#define GODCC_FRONTEND_AST_TO_IR_H_
// 中间代码生成
#include <stack>

#include "tools/symbolTable.h"
#include "visitor.h"

class IRGeneratorVisitor : public Visitor {
 private:
  SymbolTable *m_symbolTable;
  SymbolTable *globalSymbolTable;
  std::string *makeSymbolWithLevel(const char *name, int level);
  Instruction make_jump(int label);
  Instruction make_branch(int condition, int label1, int label2);

  //记录while循环的开头标签和结尾标签
  std::stack<unsigned int> while_begin_label;        //continue跳转的位置
  std::vector<std::pair<int, int>> break_instruction;//记录break的指令，需要修改break跳转的位置
  std::vector<Instruction> func_param;               //保存函数参数

  //数组访问
  std::string array_name;                            //数组名
  std::string pre_array_name;                       //数组名前缀

  int number_record = 0;//记录指令的标号
  int label_record = 0; //记录标签的标号
  int str_record = 0;  //记录字符串的标号

  void add_library_function();
 public:
  std::shared_ptr<Program> programIr = nullptr;
 public:
  explicit IRGeneratorVisitor(SymbolTable *symbolTable);
  ~IRGeneratorVisitor();
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

  void VisitPostfixExprAst(PostfixExprAst *) override;
  void VisitBinaryExpAst(BinaryExprAst *) override;
  void VisitUnaryExpAst(UnaryExprAst *) override;
  void VisitUnaryOpAst(UnaryOpAst *) override;
  void VisitPrimaryExpAst(PrimaryExprAst *) override;
  void VisitNumberAst(NumberAst *) override;
  void VisitStringAst(StringAst *) override;
  void VisitIdentifierAst(IdentifierAst *) override;
};

#endif//GODCC_FRONTEND_AST_TO_IR_H_
