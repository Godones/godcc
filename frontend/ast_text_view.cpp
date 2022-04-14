//
// Created by linfeng on 2022/4/8.
//

#include "ast_text_view.h"
void AstVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  ast->comp_unit->accept(this);
}

// todo!(这里尝试使用递归)
void AstVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
  compUnitAst->printSpace();
  std::cout << "CompUnitAST <> \n";
  if (compUnitAst->comp_unit){
	compUnitAst->comp_unit->accept(this);
  }
  compUnitAst->comp_unit_Item->accept(this);
}

void AstVisitor::VisitFuncDefAst(FuncDefAst *funcDefAst) {
  funcDefAst->printSpace();
  std::cout << "FuncDefAST <> ";
  funcDefAst->funcType->accept(this);
  funcDefAst->ident->setSpaces(funcDefAst->spaces + 1);
  funcDefAst->ident->accept(this);
  if (funcDefAst->funcParamList){
	funcDefAst->funcParamList->setSpaces(funcDefAst->spaces + 1);
	funcDefAst->funcParamList->accept(this);
  }
  funcDefAst->block->setSpaces(funcDefAst->spaces + 1);
  funcDefAst->block->accept(this);
}

void AstVisitor::VisitFuncTypeAst(FuncTypeAst *funcTypeAst) {
  std::cout << funcTypeAst->type << "\n";
}

void AstVisitor::VisitBlockAst(BlockAst *blockAst) {
  blockAst->printSpace();
  std::cout << "BlockAst <>\n";
  //  DEBUG("blockAst->stmts.size() = %d ",  blockAst->blockItems.size());
  blockAst->block_item_list->setSpaces(blockAst->spaces + 1);
  blockAst->block_item_list->accept(this);
}
void AstVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
  block_item_list_ast->printSpace();
  std::cout << "BlockItemListAst <>\n";
  if (block_item_list_ast->block_item_list){
	block_item_list_ast->block_item_list->setSpaces(block_item_list_ast->spaces + 1);
	block_item_list_ast->block_item_list->accept(this);
  }
  block_item_list_ast->block_item->setSpaces(block_item_list_ast->spaces + 1);
  block_item_list_ast->block_item->accept(this);
}
void AstVisitor::VisitBlockItem(BlockItemAst *block_item_ast) {
  block_item_ast->printSpace();
  std::cout << "BlockItemAst <>\n";
  block_item_ast->item->setSpaces(block_item_ast->spaces + 1);
  block_item_ast->item->accept(this);
}

void AstVisitor::VisitStmtAst(StmtAst *stmtAst) {
  stmtAst->printSpace();
  std::cout <<StmtTypeToString(stmtAst->type)<<"StmtAst <>\n";
  if (stmtAst->type==StmtType::kAssign) {
	stmtAst->l_val->setSpaces(stmtAst->spaces + 1);
	stmtAst->l_val->accept(this);
  }
  if (stmtAst->expr!=nullptr) {
	stmtAst->expr->setSpaces(stmtAst->spaces + 1);
	stmtAst->expr->accept(this);
  }
  std::cout << "\n";
}

void AstVisitor::VisitIdentifierAst(IdentifierAst *identifierAst) {
  identifierAst->printSpace();
  std::cout << "IdentifierAst <> ";
  std::cout << identifierAst->name << "\n";
}

void AstVisitor::VisitExp(ExpAst *expAst) {
  expAst->printSpace();
  std::cout << "ExpAst <>\n";
  expAst->realExpr->setSpaces(expAst->spaces + 1);
  expAst->realExpr->accept(this);
}


void AstVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  binary_expr_ast->printSpace();
  std::cout << BinaryTypeToString(binary_expr_ast->type)<<"BinaryExprAst <> ";
  // 如果存在左子树
  if (binary_expr_ast->left) {
	std::cout << binary_expr_ast->op << "\n";
	binary_expr_ast->left->setSpaces(binary_expr_ast->spaces + 1);
	binary_expr_ast->left->accept(this);
  }
  // 右子树
  std::cout << "\n";
  binary_expr_ast->right->setSpaces(binary_expr_ast->spaces + 1);
  binary_expr_ast->right->accept(this);
}

void AstVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
  unaryExprAst->printSpace();
  std::cout << UnaryTypeToString(unaryExprAst->unaryType)<<"UnaryExpAst <> \n";
  if (unaryExprAst->unaryType == UnaryType::kUnary||unaryExprAst->unaryType == UnaryType::kCall) {
	unaryExprAst->unaryOp->setSpaces(unaryExprAst->spaces + 1);
	unaryExprAst->unaryOp->accept(this);//一元运算符号// call
	std::cout << "\n";
	if (unaryExprAst->unaryExpr){
	  unaryExprAst->unaryExpr->setSpaces(unaryExprAst->spaces + 1);
	  unaryExprAst->unaryExpr->accept(this);
	}
  } else {
	unaryExprAst->unaryExpr->setSpaces(unaryExprAst->spaces + 1);
	unaryExprAst->unaryExpr->accept(this);
  }
}
void AstVisitor::VisitUnaryOpAst(UnaryOpAst *unaryOpAst) {
  std::cout << unaryOpAst->op;
}

void AstVisitor::VisitPrimaryExpAst(PrimaryExprAst *primaryExprAst) {
  primaryExprAst->printSpace();
  std::cout << "PrimaryExpAst <> \n";
  primaryExprAst->primaryExpr->setSpaces(primaryExprAst->spaces + 1);
  primaryExprAst->primaryExpr->accept(this);
}

void AstVisitor::VisitNumberAst(NumberAst *numberAst) {
  numberAst->printSpace();
  std::cout << "NumberAst <> " << numberAst->value;
}
void AstVisitor::VisitDecl(DeclAst *decl_ast) {
  decl_ast->printSpace();
  std::cout << "DeclAst <> \n";
  decl_ast->decl->setSpaces(decl_ast->spaces + 1);
  decl_ast->decl->accept(this);
}
void AstVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  const_decl_ast->printSpace();
  std::cout << "ConstDeclAst <> const ";
  const_decl_ast->data_type->accept(this);
  const_decl_ast->const_def_list->setSpaces(const_decl_ast->spaces + 1);
  const_decl_ast->const_def_list->accept(this);

}

void AstVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
  const_def_list_ast->printSpace();
  std::cout << "ConstDefListAst <>\n";
  if (const_def_list_ast->const_def_list) {
	const_def_list_ast->const_def_list->setSpaces(const_def_list_ast->spaces + 1);
	const_def_list_ast->const_def_list->accept(this);
  }
  const_def_list_ast->const_def->setSpaces(const_def_list_ast->spaces + 1);
  const_def_list_ast->const_def->accept(this);
}

void AstVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  const_def_ast->printSpace();
  std::cout << "ConstDefAst <> \n";
  const_def_ast->ident->setSpaces(const_def_ast->spaces + 1);
  const_def_ast->ident->accept(this);
  if (const_def_ast->array_expr_list){
	const_def_ast->array_expr_list->setSpaces(const_def_ast->spaces+1);
	const_def_ast->array_expr_list->accept(this);
  }
  const_def_ast->const_val->setSpaces(const_def_ast->spaces + 1);
  const_def_ast->const_val->accept(this);
  std::cout << "\n";
}
void AstVisitor::VisitLVal(LValAst *l_val_ast) {
  l_val_ast->printSpace();
  std::cout << "LValAst <> \n";
  l_val_ast->l_val->setSpaces(l_val_ast->spaces + 1);
  l_val_ast->l_val->accept(this);
  if (l_val_ast->array_expr_list){
	l_val_ast->array_expr_list->setSpaces(l_val_ast->spaces+1);
	l_val_ast->array_expr_list->accept(this);
  }

}
void AstVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  var_decl_ast->printSpace();
  std::cout << "VarDeclAst <>  ";
  var_decl_ast->dataType->setSpaces(var_decl_ast->spaces + 1);
  var_decl_ast->dataType->accept(this);
  var_decl_ast->var_def_list->setSpaces(var_decl_ast->spaces + 1);
  var_decl_ast->var_def_list->accept(this);
}

void AstVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
  var_def_list_ast->printSpace();
  std::cout << "VarDefListAst <> \n";
  if (var_def_list_ast->varDefList) {
    var_def_list_ast->varDefList->setSpaces(var_def_list_ast->spaces + 1);
    var_def_list_ast->varDefList->accept(this);
  }
  var_def_list_ast->varDef->setSpaces(var_def_list_ast->spaces + 1);
  var_def_list_ast->varDef->accept(this);
}

void AstVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  var_def_ast->printSpace();
  std::cout << "VarDefAst <> \n";
  var_def_ast->ident->setSpaces(var_def_ast->spaces + 1);
  var_def_ast->ident->accept(this);
  if (var_def_ast->array_expr_list){
	var_def_ast->array_expr_list->setSpaces(var_def_ast->spaces+1);
	var_def_ast->array_expr_list->accept(this);
  }
  if (var_def_ast->var_expr) {
	var_def_ast->var_expr->setSpaces(var_def_ast->spaces + 1);
	var_def_ast->var_expr->accept(this);
  }
  std::cout << "\n";
}
void AstVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
  if_stmt_ast->expr->setSpaces(if_stmt_ast->spaces + 1);
  if_stmt_ast->expr->accept(this);
  std::cout << "\n";
  if_stmt_ast->stmt->setSpaces(if_stmt_ast->spaces + 1);
  if_stmt_ast->stmt->accept(this);
  if (if_stmt_ast->elseStmt) {
	if_stmt_ast->elseStmt->setSpaces(if_stmt_ast->spaces+1);
	if_stmt_ast->elseStmt->accept(this);
  }
  //  std::cout << "\n";
}
void AstVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
  while_stmt_ast->expr->setSpaces(while_stmt_ast->spaces+1);
  while_stmt_ast->expr->accept(this);
  std::cout <<"\n";
  while_stmt_ast->stmt->setSpaces(while_stmt_ast->spaces+1);
  while_stmt_ast->stmt->accept(this);
}
void AstVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
  func_f_param_ast->printSpace();
  std::cout << "FuncFParamAst <> \n";
  func_f_param_ast->funcType->setSpaces(func_f_param_ast->spaces+1);
  func_f_param_ast->funcType->accept(this);
  func_f_param_ast->ident->setSpaces(func_f_param_ast->spaces+1);
  func_f_param_ast->ident->accept(this);
}

void AstVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_ast) {
  func_r_param_ast->printSpace();
  std::cout << "FuncRParamListAst <> \n";
  func_r_param_ast->expr->accept(this);
}
void AstVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  array_expr_list_ast->printSpace();
  std::cout << "ArrayExprListAst <> []\n";
  if (array_expr_list_ast->array_expr_list){
	array_expr_list_ast->array_expr_list->setSpaces(array_expr_list_ast->spaces+1);
	array_expr_list_ast->array_expr_list->accept(this);
  }
  array_expr_list_ast->array_expr->setSpaces(array_expr_list_ast->spaces+1);
  array_expr_list_ast->array_expr->accept(this);
  std::cout << "\n";
}
void AstVisitor::VisitInitVal(InitValAst *init_val_ast) {
  init_val_ast->printSpace();
  std::cout << "InitValAst <> \n";
  if (init_val_ast->init_val){
	init_val_ast->init_val->setSpaces(init_val_ast->spaces+1);
	init_val_ast->init_val->accept(this);
  }
  init_val_ast->init_val_list->setSpaces(init_val_ast->spaces+1);
  init_val_ast->init_val_list->accept(this);
  std::cout<<"\n";
}
void AstVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
  init_val_list_ast->printSpace();
  std::cout << "InitValListAst <>  ";
  auto expr = dynamic_cast<InitValAst*>(init_val_list_ast->expr_init_val.get());
  if (expr||init_val_list_ast->expr_init_val== nullptr){
	std::cout << "{ }"<< "\n";
	if (expr){
	  expr->setSpaces(init_val_list_ast->spaces+1);
	  expr->accept(this);
	}
  } else{
	std::cout << "\n";
	init_val_list_ast->expr_init_val->setSpaces(init_val_list_ast->spaces+1);
	init_val_list_ast->expr_init_val->accept(this);
  }
}
void AstVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {
  if (func_f_param_list_ast->funcFParamList){
	func_f_param_list_ast->funcFParamList->accept(this);
  }
  func_f_param_list_ast->funcFParam->accept(this);
}
