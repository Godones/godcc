//
// Created by linfeng on 2022/4/13.
//

#include "ast_tree_view.h"
AstViewVisitor::AstViewVisitor(GDot j_son):j_son_(j_son){}
void AstViewVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  j_son_.BeganWrite("TranslationUnit");
  ast->comp_unit->accept(this);
  j_son_.EndWrite();
  j_son_.close();
}
void AstViewVisitor::VisitCompUnitAst(CompUnitAst *comp_unit_ast) {
  j_son_.BeganWrite("CompUnit");
  std::stack<std::shared_ptr<Ast>> comp_unit_list;
  while (comp_unit_ast){
	comp_unit_list.push(comp_unit_ast->comp_unit_Item);
	comp_unit_ast = dynamic_cast<CompUnitAst *>((comp_unit_ast->comp_unit).get());
  }
  while (!comp_unit_list.empty()){
	comp_unit_list.top()->accept(this);
	comp_unit_list.pop();
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitFuncDefAst(FuncDefAst *func_def_ast) {
  char str[50] ={0};
  auto type = dynamic_cast<FuncTypeAst*>(func_def_ast->funcType.get());
  assert(type);
  auto ident = dynamic_cast<IdentifierAst*>(func_def_ast->ident.get());
  assert(ident);
  sprintf(str,"FuncDef:%s %s",type->type,ident->name);
  j_son_.BeganWrite(str);
  if (func_def_ast->funcParamList){
	func_def_ast->funcParamList->accept(this);
  }
  func_def_ast->block->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitFuncTypeAst(FuncTypeAst *) {}
void AstViewVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
  char str[50]={0};
  auto type = dynamic_cast<FuncTypeAst*>(func_f_param_ast->funcType.get());
  assert(type);
  auto ident = dynamic_cast<IdentifierAst*>(func_f_param_ast->ident.get());
  assert(ident);
  bool first = false;
  if(func_f_param_ast->first_no_dim){
	first = true;
  }
  sprintf(str,"%s %s%s",type->type,ident->name,first?"[]":"");
  j_son_.BeganWrite(str);
  if (func_f_param_ast->array_expr_list){
	func_f_param_ast->array_expr_list->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {
  j_son_.BeganWrite("FuncFParamList");
  std::stack<std::shared_ptr<Ast>> list;
  while (func_f_param_list_ast){
	list.push(func_f_param_list_ast->funcFParam);
	func_f_param_list_ast = dynamic_cast<FuncFParamListAst *>((func_f_param_list_ast->funcFParamList).get());
  }
  while (!list.empty()){
	list.top()->accept(this);
	list.pop();
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (func_r_param_list_ast){
	list.push(func_r_param_list_ast->expr);
	func_r_param_list_ast = dynamic_cast<FuncRParamListAst *>((func_r_param_list_ast->funcRParamListAst).get());
  }
  while (!list.empty()){
	j_son_.BeganWrite("FuncRParam");
	list.top()->accept(this);
	j_son_.EndWrite();
	list.pop();
  }
}
void AstViewVisitor::VisitBlockAst(BlockAst *block_ast) {
  j_son_.BeganWrite("Block");
  block_ast->block_item_list->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (block_item_list_ast){
	list.push(block_item_list_ast->block_item);
	block_item_list_ast = dynamic_cast<BlockItemListAst *>((block_item_list_ast->block_item_list).get());
  }
  while (!list.empty()){
	list.top()->accept(this);
	list.pop();
  }
}
void AstViewVisitor::VisitBlockItem(BlockItemAst *block_item_ast) {
  j_son_.BeganWrite("BlockItem");
  block_item_ast->item->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitStmtAst(StmtAst *stmt_ast) {
  switch (stmt_ast->type) {
	case StmtType::kReturn: {
	  j_son_.BeganWrite("ReturnStmt");
	  if (stmt_ast->expr){
		stmt_ast->expr->accept(this);
	  }
	  break;
	};
	case StmtType::kAssign: {
	  j_son_.BeganWrite("AssignStmt:=");
	  stmt_ast->l_val->accept(this);
	  stmt_ast->expr->accept(this);
	  j_son_.EndWrite();
	  break;
	};
	case StmtType::kBlock: {
	  stmt_ast->expr->accept(this);
	  break;
	};
	case StmtType::kExpr: {
	  j_son_.BeganWrite("ExprStmt");
	  if (stmt_ast->expr)
		  stmt_ast->expr->accept(this);
	  j_son_.EndWrite();
	  break;
	};
	case StmtType::kIf: {
	  j_son_.BeganWrite("IfStmt");
	  stmt_ast->expr->accept(this);
	  j_son_.EndWrite();
	  break;
	};
	case StmtType::kWhile: {
	  j_son_.BeganWrite("WhileStmt");
	  stmt_ast->expr->accept(this);
	  j_son_.EndWrite();
	  break;
	};
	case StmtType::kBreak: {
	  j_son_.BeganWrite("BreakStmt");
	  j_son_.EndWrite();
	  break;
	};
	case StmtType::kContinue: {
	  j_son_.BeganWrite("ContinueStmt");
	  j_son_.EndWrite();
	  break;
	};
  }
}
void AstViewVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
  j_son_.BeganWrite("if");
  if_stmt_ast->expr->accept(this);
  if_stmt_ast->stmt->accept(this);
  j_son_.EndWrite();
  if (if_stmt_ast->elseStmt) {
	j_son_.BeganWrite("else");
	if_stmt_ast->elseStmt->accept(this);
	j_son_.EndWrite();
  }
}
void AstViewVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
  j_son_.BeganWrite("while");
  while_stmt_ast->expr->accept(this);
  while_stmt_ast->stmt->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitExp(ExpAst *exp_ast) {
  exp_ast->realExpr->accept(this);
}
void AstViewVisitor::VisitDecl(DeclAst *decl_ast) {
  decl_ast->decl->accept(this);
}
void AstViewVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  char str[50];
  auto type = dynamic_cast<FuncTypeAst*>(const_decl_ast->data_type.get());
  assert(type);
  sprintf(str,"ConstDecl:%s %s","const ",type->type);
  j_son_.BeganWrite(str);
  const_decl_ast->const_def_list->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (const_def_list_ast){
	list.push(const_def_list_ast->const_def);
	const_def_list_ast = dynamic_cast<ConstDefListAst *>((const_def_list_ast->const_def_list).get());
  }
  while (!list.empty()){
	list.top()->accept(this);
	list.pop();
  }
}
void AstViewVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  j_son_.BeganWrite("ConstDef:=");
  const_def_ast->ident->accept(this);
  if (const_def_ast->array_expr_list){
	const_def_ast->array_expr_list->accept(this);
  }
  const_def_ast->const_val->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitLVal(LValAst *l_val_ast) {
  auto ident = dynamic_cast<IdentifierAst*>(l_val_ast->l_val.get());
  assert(ident);
  j_son_.BeganWrite(ident->name);
  if (l_val_ast->array_expr_list){
	l_val_ast->array_expr_list->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  char str[50];
  auto type = dynamic_cast<FuncTypeAst*>(var_decl_ast->dataType.get());
  assert(type);
  sprintf(str,"VarDecl:%s",type->type);
  j_son_.BeganWrite(str);
  var_decl_ast->var_def_list->accept(this);
  j_son_.EndWrite();
}

void AstViewVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (var_def_list_ast){
	list.push(var_def_list_ast->varDef);
	var_def_list_ast = dynamic_cast<VarDefListAst *>((var_def_list_ast->varDefList).get());
  }
  while (!list.empty()){
	list.top()->accept(this);
	list.pop();
  }
}
void AstViewVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  if (var_def_ast->var_expr)
	j_son_.BeganWrite("Vardef:=");
  var_def_ast->ident->accept(this);
  if (var_def_ast->array_expr_list){
	var_def_ast->array_expr_list->accept(this);
  }
  if (var_def_ast->var_expr){
	var_def_ast->var_expr->accept(this);
	j_son_.EndWrite();
  }
}
void AstViewVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (array_expr_list_ast){
	list.push(array_expr_list_ast->array_expr);
	array_expr_list_ast = dynamic_cast<ArrayExprListAst *>((array_expr_list_ast->array_expr_list).get());
  }
  while (!list.empty()){
	j_son_.BeganWrite("[ ]");
	list.top()->accept(this);
	j_son_.EndWrite();
	list.pop();
  }
}
void AstViewVisitor::VisitInitVal(InitValAst *init_val_ast) {
  if (init_val_ast->init_val){
	init_val_ast->init_val->accept(this);
  }
  init_val_ast->init_val_list->accept(this);
}
void AstViewVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
  auto expr = dynamic_cast<InitValAst*>(init_val_list_ast->expr_init_val.get());
  if (expr||init_val_list_ast->expr_init_val== nullptr){
	j_son_.BeganWrite("InitValList:={}");
	if (expr)
	  expr->accept(this);
	j_son_.EndWrite();
  } else{
	init_val_list_ast->expr_init_val->accept(this);
  }
}
void AstViewVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  if (binary_expr_ast->left){
	//
	j_son_.BeganWrite(binary_expr_ast->op);
	binary_expr_ast->left->accept(this);
  }
  binary_expr_ast->right->accept(this);
  if(binary_expr_ast->left){
	j_son_.EndWrite();
  }
}
void AstViewVisitor::VisitUnaryExpAst(UnaryExprAst *unary_expr_ast) {
  switch (unary_expr_ast->unaryType) {
	case UnaryType::kPrimary: {
	  unary_expr_ast->unaryExpr->accept(this);
	  break;
	}
	case UnaryType::kUnary: {
	  j_son_.BeganWrite("UnaryExpr");
	  unary_expr_ast->unaryOp->accept(this);
	  unary_expr_ast->unaryExpr->accept(this);
	  j_son_.EndWrite();
	  break;
	};
	case UnaryType::kCall: {
	  j_son_.BeganWrite("FuncCall:()");
	  unary_expr_ast->unaryOp->accept(this);
	  if (unary_expr_ast->unaryExpr){
		unary_expr_ast->unaryExpr->accept(this);
	  }
	  j_son_.EndWrite();
	  break;
	};
  }
}
void AstViewVisitor::VisitUnaryOpAst(UnaryOpAst *unary_op_ast) {
  j_son_.BeganWrite(unary_op_ast->op);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitPrimaryExpAst(PrimaryExprAst *primary_expr_ast) {
  primary_expr_ast->primaryExpr->accept(this);
}
void AstViewVisitor::VisitNumberAst(NumberAst *number_ast) {
  char str[20];
  sprintf(str,"%s:%d","Number",number_ast->value);
  j_son_.BeganWrite(str);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {
  char str[20];
  sprintf(str,"%s:%s","Identifier",identifier_ast->name);
  j_son_.BeganWrite(str);
  j_son_.EndWrite();
}
