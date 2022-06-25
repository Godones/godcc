//
// Created by linfeng on 2022/4/8.
//
#include "cst_tree_view.h"
// 生成json文件输出图形化显示
void CstViewVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  ast->comp_unit->accept(this);
  dot.close();
}
void CstViewVisitor::VisitCompUnitAst(CompUnitAst *comp_unit_ast) {
  dot.BeganWrite("CompUnit");
  if (comp_unit_ast->comp_unit) {
	comp_unit_ast->comp_unit->accept(this);
  }
  comp_unit_ast->comp_unit_Item->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitFuncDefAst(FuncDefAst *func_def_ast) {
  dot.BeganWrite("FuncDef");
  func_def_ast->funcType->accept(this);
  func_def_ast->ident->accept(this);
  if (func_def_ast->funcParamList) {
	func_def_ast->funcParamList->accept(this);
  }
  func_def_ast->block->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitFuncTypeAst(FuncTypeAst *func_type_ast) {
  dot.BeganWrite("Type");
  dot.BeganWrite(func_type_ast->type);
  dot.EndWrite();
  dot.EndWrite();
}
void CstViewVisitor::VisitBlockAst(BlockAst *block_ast) {
  dot.BeganWrite("Block");
  if (block_ast->block_item_list) {
	block_ast->block_item_list->accept(this);
  }
  dot.EndWrite();
}
void CstViewVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
  dot.BeganWrite("BlockItemList");
  if (block_item_list_ast->block_item_list) {
	block_item_list_ast->block_item_list->accept(this);
  }
  block_item_list_ast->block_item->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitBlockItem(BlockItemAst *block_item_ast) {
  dot.BeganWrite("BlockItem");
  block_item_ast->item->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitStmtAst(StmtAst *stmt_ast) {
  const char *type = StmtTypeToString(stmt_ast->type);
  char str[50] = {0};
  sprintf(str, "%sStmt", type);
  dot.BeganWrite(str);
  if (stmt_ast->type == StmtType::kAssign) {
	stmt_ast->l_val->accept(this);
	dot.BeganWrite("=");
	stmt_ast->expr->accept(this);
	dot.EndWrite();
  } else {
	if (stmt_ast->expr) {
	  stmt_ast->expr->accept(this);
	}
  }
  dot.EndWrite();
}
void CstViewVisitor::VisitExp(ExpAst *exp_ast) {
  dot.BeganWrite("Expr");
  exp_ast->realExpr->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitUnaryExpAst(UnaryExprAst *unary_expr_ast) {
  const char *pre_name = UnaryTypeToString(unary_expr_ast->unaryType);
  char str[50] = {0};
  sprintf(str, "%sUnaryExpr", pre_name);
  dot.BeganWrite(str);
  if (unary_expr_ast->unaryOp&&unary_expr_ast->unaryType!=UnaryType::kBDec&&unary_expr_ast->unaryType!=UnaryType::kBInc) {
	unary_expr_ast->unaryOp->accept(this);//一元运算符号 // call
  }
  if (unary_expr_ast->unaryType == UnaryType::kCall) {
	dot.BeganWrite("()");
	dot.EndWrite();
  }
  if (unary_expr_ast->unaryExpr) {
	unary_expr_ast->unaryExpr->accept(this);
  }
  if (unary_expr_ast->unaryOp&&(unary_expr_ast->unaryType==UnaryType::kBDec||unary_expr_ast->unaryType==UnaryType::kBInc)) {
	unary_expr_ast->unaryOp->accept(this);//一元运算符号 // x++/x--
  }
  dot.EndWrite();
}

void CstViewVisitor::VisitPostfixExprAst(PostfixExprAst *postfixExprAst) {
  dot.BeganWrite("PostfixExpr");
  postfixExprAst->postfixExpr->accept(this);
  if (postfixExprAst->postfixType==PostfixType::kBDec) {
	dot.BeganWrite("--");
	dot.EndWrite();
  } else if (postfixExprAst->postfixType==PostfixType::kBInc) {
	dot.BeganWrite("++");
	dot.EndWrite();
  }
  dot.EndWrite();
}


void CstViewVisitor::VisitUnaryOpAst(UnaryOpAst *unary_op_ast) {
  dot.BeganWrite("UnaryOp");
  dot.BeganWrite(unary_op_ast->op);
  dot.EndWrite();
  dot.EndWrite();
}
void CstViewVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  const char *pre_name = BinaryTypeToString(binary_expr_ast->type);
  char str[50] = {0};
  sprintf(str, "%sBinaryExp", pre_name);
  dot.BeganWrite(str);
  if (binary_expr_ast->left) {
	binary_expr_ast->left->accept(this);
	dot.BeganWrite(binary_expr_ast->op);
	dot.EndWrite();
  }
  binary_expr_ast->right->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitPrimaryExpAst(PrimaryExprAst *primary_expr_ast) {
  dot.BeganWrite("PrimaryExp");
  if (primary_expr_ast->primaryType == PrimaryType::EXP) {
	dot.BeganWrite("(");
	dot.EndWrite();
	primary_expr_ast->primaryExpr->accept(this);
	dot.BeganWrite(")");
	dot.EndWrite();
  } else {
	primary_expr_ast->primaryExpr->accept(this);
  }
  dot.EndWrite();
}
void CstViewVisitor::VisitNumberAst(NumberAst *number_ast) {
  dot.BeganWrite(std::to_string(number_ast->value).c_str());
  dot.EndWrite();
}
void CstViewVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {
  dot.BeganWrite("Identifier");
  dot.BeganWrite(identifier_ast->name);
  dot.EndWrite();
  dot.EndWrite();
}
void CstViewVisitor::VisitDecl(DeclAst *decl_ast) {
  dot.BeganWrite("Decl");
  decl_ast->decl->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  dot.BeganWrite("ConstDecl");
  dot.BeganWrite("const");
  dot.EndWrite();
  const_decl_ast->data_type->accept(this);
  const_decl_ast->const_def_list->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
  dot.BeganWrite("ConstDefList");
  if (const_def_list_ast->const_def_list) {
	const_def_list_ast->const_def_list->accept(this);
  }
  const_def_list_ast->const_def->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  dot.BeganWrite("ConstDef");
  const_def_ast->ident->accept(this);
  if (const_def_ast->array_expr_list) {
	const_def_ast->array_expr_list->accept(this);
  }
  dot.BeganWrite("=");
  dot.EndWrite();
  const_def_ast->const_val->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitLVal(LValAst *l_val_ast) {
  dot.BeganWrite("LVal");
  l_val_ast->l_val->accept(this);
  if (l_val_ast->array_expr_list) {
	l_val_ast->array_expr_list->accept(this);
  }
  dot.EndWrite();
}
void CstViewVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  dot.BeganWrite("VarDecl");
  var_decl_ast->dataType->accept(this);
  var_decl_ast->var_def_list->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
  dot.BeganWrite("VarDefList");
  if (var_def_list_ast->varDefList) {
	var_def_list_ast->varDefList->accept(this);
  }
  var_def_list_ast->varDef->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  dot.BeganWrite("VarDef");
  var_def_ast->ident->accept(this);
  if (var_def_ast->array_expr_list) {
	var_def_ast->array_expr_list->accept(this);
  }
  if (var_def_ast->var_expr) {
	dot.BeganWrite("=");
	dot.EndWrite();
	var_def_ast->var_expr->accept(this);
  }
  dot.EndWrite();
}
void CstViewVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
  dot.BeganWrite("if");
  if_stmt_ast->expr->accept(this);
  if_stmt_ast->stmt->accept(this);
  dot.EndWrite();
  if (if_stmt_ast->elseStmt) {
	dot.BeganWrite("else");
	if_stmt_ast->elseStmt->accept(this);
	dot.EndWrite();
  }
}
void CstViewVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
  dot.BeganWrite("while");
  while_stmt_ast->expr->accept(this);
  while_stmt_ast->stmt->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitForStmt(ForStmtAst *forStmtAst) {
  dot.BeganWrite("for");
  forStmtAst->expr1->accept(this);
  forStmtAst->expr2->accept(this);
  if (forStmtAst->expr3)
 	 forStmtAst->expr3->accept(this);
  forStmtAst->stmt->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
  dot.BeganWrite("FuncFParam");
  func_f_param_ast->funcType->accept(this);
  func_f_param_ast->ident->accept(this);
  if (func_f_param_ast->first_no_dim) {
	dot.BeganWrite("[]");
	dot.EndWrite();
  }
  if (func_f_param_ast->array_expr_list) {
	DEBUG("array_expr_list is not null");
	func_f_param_ast->array_expr_list->accept(this);
  }
  dot.EndWrite();
}
void CstViewVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {
  dot.BeganWrite("FuncFParamList");
  if (func_f_param_list_ast->funcFParamList) {
	func_f_param_list_ast->funcFParamList->accept(this);
  }
  func_f_param_list_ast->funcFParam->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_ast) {
  dot.BeganWrite("FuncRParam");
  if (func_r_param_ast->funcRParamListAst) {
	func_r_param_ast->funcRParamListAst->accept(this);
  }
  func_r_param_ast->expr->accept(this);
  dot.EndWrite();
}

void CstViewVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  dot.BeganWrite("ArrayExprList");
  if (array_expr_list_ast->array_expr_list) {
	array_expr_list_ast->array_expr_list->accept(this);
  }
  dot.BeganWrite("[");
  dot.EndWrite();
  array_expr_list_ast->array_expr->accept(this);
  dot.BeganWrite("]");
  dot.EndWrite();
  dot.EndWrite();
}
void CstViewVisitor::VisitInitVal(InitValAst *init_val_ast) {
  dot.BeganWrite("InitVal");
  if (init_val_ast->init_val) {
	init_val_ast->init_val->accept(this);
  }
  init_val_ast->init_val_list->accept(this);
  dot.EndWrite();
}
void CstViewVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
  dot.BeganWrite("InitValList");
  auto expr = dynamic_cast<InitValAst *>(init_val_list_ast->expr_init_val.get());
  if (expr || init_val_list_ast->expr_init_val == nullptr) {
	dot.BeganWrite("{");
	dot.EndWrite();
	if (expr)
	  expr->accept(this);
	dot.BeganWrite("}");
	dot.EndWrite();
  } else {
	init_val_list_ast->expr_init_val->accept(this);
  }
  dot.EndWrite();
}
CstViewVisitor::CstViewVisitor(GDot j_son) : dot(j_son) {}
