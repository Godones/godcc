//
// Created by linfeng on 2022/4/8.
//
#include "ast_tree_view.h"
// 生成json文件输出图形化显示
void AstViewVisitor::VisitCompUnitAst(CompUnitAst *comp_unit_ast) {
  j_son_.BeganWrite("CompUnit");
  if (comp_unit_ast->comp_unit){
	comp_unit_ast->comp_unit->accept(this);
  }
  comp_unit_ast->comp_unit_Item->accept(this);
  j_son_.EndWrite();

}

void AstViewVisitor::VisitFuncDefAst(FuncDefAst *func_def_ast) {
  j_son_.BeganWrite("FuncDef");
  func_def_ast->funcType->accept(this);
  func_def_ast->ident->accept(this);
  if (func_def_ast->funcParam){
	func_def_ast->funcParam->accept(this);
  }
  func_def_ast->block->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitFuncTypeAst(FuncTypeAst *func_type_ast) {
  j_son_.BeganWrite("Type");
  j_son_.BeganWrite(func_type_ast->type);
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void AstViewVisitor::VisitBlockAst(BlockAst *block_ast) {
  j_son_.BeganWrite("Block");
  for (auto &item: block_ast->blockItems) {
	item->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitBlockItem(BlockItemAst *block_item_ast) {
  j_son_.BeganWrite("BlockItem");
  block_item_ast->item->accept(this);
  j_son_.EndWrite();
}

void AstViewVisitor::VisitStmtAst(StmtAst *stmt_ast) {
  std::string type = StmtTypeToString(stmt_ast->type);
  j_son_.BeganWrite(type+"Stmt");
  if (stmt_ast->type==StmtType::kDecl){
	stmt_ast->l_val->accept(this);
	j_son_.BeganWrite("=");
	stmt_ast->expr->accept(this);
	j_son_.EndWrite();
  }else{
	if (stmt_ast->expr){
	  stmt_ast->expr->accept(this);
	}
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitExp(ExpAst *exp_ast) {
  j_son_.BeganWrite("Expr");
  exp_ast->realExpr->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitUnaryExpAst(UnaryExprAst *unary_expr_ast) {
  std::string pre_name = UnaryTypeToString(unary_expr_ast->unaryType);
  j_son_.BeganWrite(pre_name+"UnaryExp");
  if (unary_expr_ast->unaryOp) {
	unary_expr_ast->unaryOp->accept(this);//一元运算符号 // call
  }
  if (unary_expr_ast->unaryExpr){
	unary_expr_ast->unaryExpr->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitUnaryOpAst(UnaryOpAst *unary_op_ast) {
  j_son_.BeganWrite("UnaryOp");
  j_son_.BeganWrite(unary_op_ast->op);
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void AstViewVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  std::string pre_name = BinaryTypeToString(binary_expr_ast->type);
  j_son_.BeganWrite(pre_name+"BinaryExp");
  if (binary_expr_ast->left) {
	binary_expr_ast->left->accept(this);
	j_son_.BeganWrite(binary_expr_ast->op);
	j_son_.EndWrite();
  }
  binary_expr_ast->right->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitPrimaryExpAst(PrimaryExprAst *primary_expr_ast) {
  j_son_.BeganWrite("PrimaryExp");
  if (primary_expr_ast->primaryType == PrimaryType::EXP) {
	j_son_.BeganWrite("(");
	j_son_.EndWrite();
	primary_expr_ast->primaryExpr->accept(this);
	j_son_.BeganWrite(")");
	j_son_.EndWrite();
  } else {
	primary_expr_ast->primaryExpr->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitNumberAst(NumberAst *number_ast) {
  j_son_.BeganWrite("Number");
  j_son_.BeganWrite(std::to_string(number_ast->value));
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void AstViewVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {
  j_son_.BeganWrite("Identifier");
  j_son_.BeganWrite(identifier_ast->name);
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void AstViewVisitor::VisitDecl(DeclAst *decl_ast) {
  j_son_.BeganWrite("Decl");
  decl_ast->decl->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  j_son_.BeganWrite("ConstDecl");
  j_son_.BeganWrite("const");
  j_son_.EndWrite();
  j_son_.BeganWrite(const_decl_ast->dataType);
  j_son_.EndWrite();
  for (auto& const_def :const_decl_ast->constDefs) {
	const_def->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  j_son_.BeganWrite("ConstDef");
  const_def_ast->ident->accept(this);
  if (const_def_ast->array_expr_list){
	const_def_ast->array_expr_list->accept(this);
  }
  j_son_.BeganWrite("=");
  j_son_.EndWrite();
  const_def_ast->const_val->accept(this);
  j_son_.EndWrite();
}

void AstViewVisitor::VisitLVal(LValAst *l_val_ast) {
  j_son_.BeganWrite("LVal");
  l_val_ast->l_val->accept(this);
  if (l_val_ast->array_expr_list){
	l_val_ast->array_expr_list->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  j_son_.BeganWrite("VarDecl");
  var_decl_ast->dataType->accept(this);
  for (auto& var_def :var_decl_ast->varDefs) {
	var_def->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  j_son_.BeganWrite("VarDef");
  var_def_ast->ident->accept(this);
  if (var_def_ast->array_expr_list){
	var_def_ast->array_expr_list->accept(this);
  }
  if (var_def_ast->is_expr){
	j_son_.BeganWrite("=");
	j_son_.EndWrite();
	var_def_ast->var_expr->accept(this);
  }
  j_son_.EndWrite();
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
void AstViewVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
  j_son_.BeganWrite("FuncFParam");
  for (auto &funcFParam :func_f_param_ast->params) {
	funcFParam->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitFuncFParamDefAst(FuncFParamDefAst *func_f_param_def_ast) {
  j_son_.BeganWrite(func_f_param_def_ast->type);
  func_f_param_def_ast->ident->accept(this);
  j_son_.EndWrite();

}
void AstViewVisitor::VisitFuncRParamAst(FuncRParamAst *func_r_param_ast) {
  j_son_.BeganWrite("FuncRParam");
  for (auto &funcRParam :func_r_param_ast->params) {
	funcRParam->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  ast->comp_unit->accept(this);
  j_son_.close();
}
void AstViewVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  j_son_.BeganWrite("ArrayExprList");
  if (array_expr_list_ast->array_expr_list){
	array_expr_list_ast->array_expr_list->accept(this);
  }
  j_son_.BeganWrite("[");
  j_son_.EndWrite();
  array_expr_list_ast->array_expr->accept(this);
  j_son_.BeganWrite("]");
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void AstViewVisitor::VisitInitVal(InitValAst *init_val_ast) {
  j_son_.BeganWrite("InitVal");
  if (init_val_ast->init_val){
	init_val_ast->init_val->accept(this);
  }
  init_val_ast->init_val_list->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
  j_son_.BeganWrite("InitValList");
  auto expr = dynamic_cast<InitValAst*>(init_val_list_ast->expr_init_val.get());
  if (expr||init_val_list_ast->expr_init_val== nullptr){
	j_son_.BeganWrite("{");
	j_son_.EndWrite();
	if (expr)
		expr->accept(this);
	j_son_.BeganWrite("}");
	j_son_.EndWrite();
  } else{
	init_val_list_ast->expr_init_val->accept(this);
  }
  j_son_.EndWrite();
}
