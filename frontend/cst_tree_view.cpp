//
// Created by linfeng on 2022/4/8.
//
#include "cst_tree_view.h"
// 生成json文件输出图形化显示
void CstViewVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  ast->comp_unit->accept(this);
  j_son_.close();
}
void CstViewVisitor::VisitCompUnitAst(CompUnitAst *comp_unit_ast) {
  j_son_.BeganWrite("CompUnit");
  if(comp_unit_ast->comp_unit){
	comp_unit_ast->comp_unit->accept(this);
  }
  comp_unit_ast->comp_unit_Item->accept(this);
  j_son_.EndWrite();
}

void CstViewVisitor::VisitFuncDefAst(FuncDefAst *func_def_ast) {
  j_son_.BeganWrite("FuncDef");
  func_def_ast->funcType->accept(this);
  func_def_ast->ident->accept(this);
  if (func_def_ast->funcParamList){
	func_def_ast->funcParamList->accept(this);
  }
  func_def_ast->block->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitFuncTypeAst(FuncTypeAst *func_type_ast) {
  j_son_.BeganWrite("Type");
  j_son_.BeganWrite(func_type_ast->type);
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void CstViewVisitor::VisitBlockAst(BlockAst *block_ast) {
  j_son_.BeganWrite("Block");
  block_ast->block_item_list->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
  j_son_.BeganWrite("BlockItemList");
  if (block_item_list_ast->block_item_list){
  	block_item_list_ast->block_item_list->accept(this);
  }
  block_item_list_ast->block_item->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitBlockItem(BlockItemAst *block_item_ast) {
  j_son_.BeganWrite("BlockItem");
  block_item_ast->item->accept(this);
  j_son_.EndWrite();
}

void CstViewVisitor::VisitStmtAst(StmtAst *stmt_ast) {
  const char * type = StmtTypeToString(stmt_ast->type);
  char str[50] = {0};
  sprintf(str,"%sStmt",type);
  j_son_.BeganWrite(str);
  if (stmt_ast->type==StmtType::kAssign){
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
void CstViewVisitor::VisitExp(ExpAst *exp_ast) {
  j_son_.BeganWrite("Expr");
  exp_ast->realExpr->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitUnaryExpAst(UnaryExprAst *unary_expr_ast) {
  const char * pre_name = UnaryTypeToString(unary_expr_ast->unaryType);
  char str[50] = {0};
  sprintf(str,"%sUnaryExpr",pre_name);
  j_son_.BeganWrite(str);
  if (unary_expr_ast->unaryOp) {
	unary_expr_ast->unaryOp->accept(this);//一元运算符号 // call
  }
  if (unary_expr_ast->unaryType==UnaryType::kCall){
	j_son_.BeganWrite("()");
	j_son_.EndWrite();
  }
  if (unary_expr_ast->unaryExpr){
	unary_expr_ast->unaryExpr->accept(this);
  }
  j_son_.EndWrite();
}
void CstViewVisitor::VisitUnaryOpAst(UnaryOpAst *unary_op_ast) {
  j_son_.BeganWrite("UnaryOp");
  j_son_.BeganWrite(unary_op_ast->op);
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void CstViewVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  const char * pre_name = BinaryTypeToString(binary_expr_ast->type);
  char str[50] = {0};
  sprintf(str,"%sBinaryExp",pre_name);
  j_son_.BeganWrite(str);
  if (binary_expr_ast->left) {
	binary_expr_ast->left->accept(this);
	j_son_.BeganWrite(binary_expr_ast->op);
	j_son_.EndWrite();
  }
  binary_expr_ast->right->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitPrimaryExpAst(PrimaryExprAst *primary_expr_ast) {
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
void CstViewVisitor::VisitNumberAst(NumberAst *number_ast) {
  j_son_.BeganWrite("Number");
  j_son_.EndWrite();
}
void CstViewVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {
  j_son_.BeganWrite("Identifier");
  j_son_.BeganWrite(identifier_ast->name);
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void CstViewVisitor::VisitDecl(DeclAst *decl_ast) {
  j_son_.BeganWrite("Decl");
  decl_ast->decl->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  j_son_.BeganWrite("ConstDecl");
  j_son_.BeganWrite("const");
  j_son_.EndWrite();
  const_decl_ast->data_type->accept(this);
  const_decl_ast->const_def_list->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
  j_son_.BeganWrite("ConstDefList");
  if (const_def_list_ast->const_def_list){
	const_def_list_ast->const_def_list->accept(this);
  }
  const_def_list_ast->const_def->accept(this);
  j_son_.EndWrite();
}

void CstViewVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
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

void CstViewVisitor::VisitLVal(LValAst *l_val_ast) {
  j_son_.BeganWrite("LVal");
  l_val_ast->l_val->accept(this);
  if (l_val_ast->array_expr_list){
	l_val_ast->array_expr_list->accept(this);
  }
  j_son_.EndWrite();
}
void CstViewVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  j_son_.BeganWrite("VarDecl");
  var_decl_ast->dataType->accept(this);
  var_decl_ast->var_def_list->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
  j_son_.BeganWrite("VarDefList");
  if (var_def_list_ast->varDefList){
    var_def_list_ast->varDefList->accept(this);
  }
  var_def_list_ast->varDef->accept(this);
  j_son_.EndWrite();
}

void CstViewVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  j_son_.BeganWrite("VarDef");
  var_def_ast->ident->accept(this);
  if (var_def_ast->array_expr_list){
	var_def_ast->array_expr_list->accept(this);
  }
  if (var_def_ast->var_expr){
	j_son_.BeganWrite("=");
	j_son_.EndWrite();
	var_def_ast->var_expr->accept(this);
  }
  j_son_.EndWrite();
}
void CstViewVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
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
void CstViewVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
  j_son_.BeganWrite("while");
  while_stmt_ast->expr->accept(this);
  while_stmt_ast->stmt->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
  j_son_.BeganWrite("FuncFParam");
  func_f_param_ast->funcType->accept(this);
  func_f_param_ast->ident->accept(this);
  if(func_f_param_ast->first_no_dim){
	j_son_.BeganWrite("[]");
	j_son_.EndWrite();
  }
  if (func_f_param_ast->array_expr_list){
	DEBUG("array_expr_list is not null");
	func_f_param_ast->array_expr_list->accept(this);
  }
  j_son_.EndWrite();
}
void CstViewVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {
  j_son_.BeganWrite("FuncFParamList");
  if (func_f_param_list_ast->funcFParamList){
	func_f_param_list_ast->funcFParamList->accept(this);
  }
  func_f_param_list_ast->funcFParam->accept(this);
  j_son_.EndWrite();
}


void CstViewVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_ast) {
  j_son_.BeganWrite("FuncRParam");
  if (func_r_param_ast->funcRParamListAst){
    func_r_param_ast->funcRParamListAst->accept(this);
  }       
  func_r_param_ast->expr->accept(this);   
  j_son_.EndWrite();
}

void CstViewVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  j_son_.BeganWrite("ArrayExprList");
  if (array_expr_list_ast->array_expr_list){
	array_expr_list_ast->array_expr_list->accept(this);
  }
  DEBUG("array_expr_list_ast->array_expr");
  j_son_.BeganWrite("[");
  j_son_.EndWrite();
  array_expr_list_ast->array_expr->accept(this);
  j_son_.BeganWrite("]");
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void CstViewVisitor::VisitInitVal(InitValAst *init_val_ast) {
  j_son_.BeganWrite("InitVal");
  if (init_val_ast->init_val){
	init_val_ast->init_val->accept(this);
  }
  init_val_ast->init_val_list->accept(this);
  j_son_.EndWrite();
}
void CstViewVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
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
CstViewVisitor::CstViewVisitor(GDot j_son):j_son_(j_son){}
