//
// Created by linfeng on 2022/4/13.
//

#include "ast_text_view.h"

void AstVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  auto j = json.top();
  (*j)["_type"] = "Program";
  (*j)["address"] = {{"line", ast->line}, {"col", ast->column}};
  json.pop();
  json.push(&(*j)["declarator"]);
  ast->comp_unit->accept(this);
  std::ofstream outfile("./ast.json");
  outfile << j->dump(4);
  //  std::cout<<j->dump(4)<<std::endl;
}
void AstVisitor::VisitCompUnitAst(CompUnitAst *comp_unit_ast) {
  assert(!json.empty());
  auto j = json.top();
  json.pop();
  (*j)["_type"] = "CompUnitList";
  (*j)["address"] = {{"line", comp_unit_ast->line}, {"col", comp_unit_ast->column}};
  std::stack<std::shared_ptr<Ast>> comp_unit_list;
  while (comp_unit_ast) {
	comp_unit_list.push(comp_unit_ast->comp_unit_Item);
	comp_unit_ast = dynamic_cast<CompUnitAst *>((comp_unit_ast->comp_unit).get());
  }
  int count1 = 0;
  while (!comp_unit_list.empty()) {
	json.push(&(*j)["declarator"][count1++]);//使用列表将函数与全局变量装起来
	comp_unit_list.top()->accept(this);
	comp_unit_list.pop();
	json.pop();
  }
}
void AstVisitor::VisitFuncDefAst(FuncDefAst *func_def_ast) {
  auto type = dynamic_cast<FuncTypeAst *>(func_def_ast->funcType.get());
  assert(type);
  auto ident = dynamic_cast<IdentifierAst *>(func_def_ast->ident.get());
  assert(ident);
  auto j = json.top();
  (*j)["address"] = {{"line", func_def_ast->line}, {"col", func_def_ast->column}};
  (*j)["_returnType"] = type->type;
  (*j)["_funcName"] = ident->name;
  (*j)["_type"] = "funcDef";
  if (func_def_ast->funcParamList) {
	func_def_ast->funcParamList->accept(this);
  }
  func_def_ast->block->accept(this);
}
void AstVisitor::VisitFuncTypeAst(FuncTypeAst *) {}
void AstVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {
  auto j = json.top();
  int count2 = 0;
  std::stack<std::shared_ptr<Ast>> list;
  while (func_f_param_list_ast) {
	list.push(func_f_param_list_ast->funcFParam);
	func_f_param_list_ast = dynamic_cast<FuncFParamListAst *>((func_f_param_list_ast->funcFParamList).get());
  }
  while (!list.empty()) {
	json.push(&(*j)["_fparamList"][count2++]);
	list.top()->accept(this);
	list.pop();
	json.pop();
  }
}
void AstVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
  auto type = dynamic_cast<FuncTypeAst *>(func_f_param_ast->funcType.get());
  auto ident = dynamic_cast<IdentifierAst *>(func_f_param_ast->ident.get());
  bool first = false;
  auto j = json.top();
  (*j)["_type"] = "funcParam";
  (*j)["address"] = {{"line", func_f_param_ast->line}, {"col", func_f_param_ast->column}};
  (*j)["_paramName"] = ident->name;
  if (func_f_param_ast->first_no_dim) {
	first = true;
  }
  // 只显示是否是数组类型
  if (first) {
	(*j)["_paramType"] = std::string(type->type) + "array";//int array
  } else {
	(*j)["_paramType"] = type->type;
  }
}

void AstVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  auto j = json.top();

  int count3 = 0;
  while (func_r_param_list_ast) {
	list.push(func_r_param_list_ast->expr);
	func_r_param_list_ast = dynamic_cast<FuncRParamListAst *>((func_r_param_list_ast->funcRParamListAst).get());
  }
  while (!list.empty()) {
	json.push(&(*j)["paramList"][count3++]);
	list.top()->accept(this);
	list.pop();
	json.pop();
  }
}
void AstVisitor::VisitBlockAst(BlockAst *block_ast) {
  if (block_ast->block_item_list) {
	block_ast->block_item_list->accept(this);
  }
}
void AstVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
  auto j = json.top();
  int count4 = 0;

  std::stack<std::shared_ptr<Ast>> list;
  while (block_item_list_ast) {
	list.push(block_item_list_ast->block_item);
	block_item_list_ast = dynamic_cast<BlockItemListAst *>((block_item_list_ast->block_item_list).get());
  }
  while (!list.empty()) {
	json.push(&(*j)["blockItemList"][count4++]);
	list.top()->accept(this);
	list.pop();
	json.pop();
  }
}
void AstVisitor::VisitBlockItem(BlockItemAst *block_item_ast) {
  block_item_ast->item->accept(this);
}
void AstVisitor::VisitStmtAst(StmtAst *stmt_ast) {
  auto j = json.top();
  (*j)["address"] = {{"line", stmt_ast->line}, {"col", stmt_ast->column}};
  switch (stmt_ast->type) {
	case StmtType::kReturn: {
	  (*j)["_type"] = "return";
	  json.push(&(*j)["returnExpr"]);
	  if (stmt_ast->expr) {
		stmt_ast->expr->accept(this);
	  }
	  json.pop();
	  break;
	};
	case StmtType::kAssign: {
	  (*j)["_type"] = "assign";
	  json.push(&(*j)["assignLvalue"]);
	  stmt_ast->l_val->accept(this);
	  json.pop();
	  json.push(&(*j)["assignExpr"]);
	  stmt_ast->expr->accept(this);
	  json.pop();
	  break;
	};
	case StmtType::kBlock: {
	  stmt_ast->expr->accept(this);
	  break;
	};
	case StmtType::kExpr: {
	  (*j)["_type"] = "expr";
	  json.push(&(*j)["expr"]);
	  if (stmt_ast->expr)
		stmt_ast->expr->accept(this);
	  json.pop();
	  break;
	};
	case StmtType::kIf: {
	  stmt_ast->expr->accept(this);
	  break;
	}
	case StmtType::kWhile: {
	  stmt_ast->expr->accept(this);
	  break;
	};
	case StmtType::kBreak: {
	  (*j)["_type"] = "break";
	  break;
	};
	case StmtType::kContinue: {
	  (*j)["_type"] = "continue";
	  break;
	};
  }
}
void AstVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
  auto j = json.top();
  (*j)["_type"] = "ifStmt";
  json.push(&(*j)["condition"]);
  if_stmt_ast->expr->accept(this);
  json.pop();
  json.push(&(*j)["thenStmt"]);
  if_stmt_ast->stmt->accept(this);
  json.pop();
  if (if_stmt_ast->elseStmt) {
	json.push(&(*j)["elseStmt"]);
	if_stmt_ast->elseStmt->accept(this);
	json.pop();
  }
}
void AstVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
  auto j = json.top();
  (*j)["_type"] = "whileStmt";
  json.push(&(*j)["condition"]);
  while_stmt_ast->expr->accept(this);
  json.pop();
  json.push(&(*j)["stmt"]);
  while_stmt_ast->stmt->accept(this);
  json.pop();
}
void AstVisitor::VisitExp(ExpAst *exp_ast) {
  exp_ast->realExpr->accept(this);
}
void AstVisitor::VisitDecl(DeclAst *decl_ast) {
  decl_ast->decl->accept(this);
}
void AstVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  auto type = dynamic_cast<FuncTypeAst *>(const_decl_ast->data_type.get());
  assert(type);
  auto j = json.top();
  (*j)["_type"] = "constDecl";
  (*j)["dataType"] = type->type;
  const_decl_ast->const_def_list->accept(this);
}
void AstVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
  auto j = json.top();
  int count5 = 0;
  std::stack<std::shared_ptr<Ast>> list;
  while (const_def_list_ast) {
	list.push(const_def_list_ast->const_def);
	const_def_list_ast = dynamic_cast<ConstDefListAst *>((const_def_list_ast->const_def_list).get());
  }
  while (!list.empty()) {
	json.push(&(*j)["constDefList"][count5++]);
	list.top()->accept(this);
	list.pop();
	json.pop();
  }
}
void AstVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  auto j = json.top();
  (*j)["_type"] = "constDef";
  auto ident = dynamic_cast<IdentifierAst *>(const_def_ast->ident.get());
  (*j)["name"] = ident->name;//会有 (*j)["name"] = "";
  if (const_def_ast->array_expr_list) {
	json.push(&(*j)["arrayExprList"]);
	const_def_ast->array_expr_list->accept(this);
	json.pop();
  }
  json.push(&(*j)["constValue"]);
  const_def_ast->const_val->accept(this);
  json.pop();
}
void AstVisitor::VisitLVal(LValAst *l_val_ast) {
  auto ident = dynamic_cast<IdentifierAst *>(l_val_ast->l_val.get());
  assert(ident);
  auto j = json.top();
  (*j)["_type"] = "lVal";
  (*j)["name"] = ident->name;
  if (l_val_ast->array_expr_list) {
	json.push(&(*j)["arrayExprList"]);
	l_val_ast->array_expr_list->accept(this);
	json.pop();
  }
}
void AstVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  auto type = dynamic_cast<FuncTypeAst *>(var_decl_ast->dataType.get());
  assert(type);
  auto j = json.top();
  (*j)["_type"] = "VarDecl";
  (*j)["dataType"] = type->type;
  var_decl_ast->var_def_list->accept(this);
}

void AstVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
  auto j = json.top();
  int count6 = 0;
  std::stack<std::shared_ptr<Ast>> list;
  while (var_def_list_ast) {
	list.push(var_def_list_ast->varDef);
	var_def_list_ast = dynamic_cast<VarDefListAst *>((var_def_list_ast->varDefList).get());
  }
  while (!list.empty()) {
	json.push(&(*j)["varDefList"][count6++]);
	list.top()->accept(this);
	list.pop();
	json.pop();
  }
}
void AstVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  auto j = json.top();
  (*j)["_type"] = "varDef";
  auto ident = dynamic_cast<IdentifierAst *>(var_def_ast->ident.get());
  (*j)["_name"] = ident->name;
  if (var_def_ast->array_expr_list) {
	json.push(&(*j)["arrayExprList"]);
	var_def_ast->array_expr_list->accept(this);
	json.pop();
  }
  if (var_def_ast->var_expr) {
	json.push(&(*j)["initValue"]);
	var_def_ast->var_expr->accept(this);
	json.pop();
  }
}
void AstVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  auto j = json.top();
  int count7 = 0;
  std::stack<std::shared_ptr<Ast>> list;
  while (array_expr_list_ast) {
	list.push(array_expr_list_ast->array_expr);
	array_expr_list_ast = dynamic_cast<ArrayExprListAst *>((array_expr_list_ast->array_expr_list).get());
  }
  while (!list.empty()) {
	json.push(&(*j)["dim"][count7++]);
	list.top()->accept(this);
	list.pop();
	json.pop();
  }
}

void AstVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
  auto j = json.top();
  auto expr = dynamic_cast<InitValAst *>(init_val_list_ast->expr_init_val.get());
  if (expr || init_val_list_ast->expr_init_val == nullptr) {
	(*j)["_type"] = "arrayInitVal";
	if (expr)
	  expr->accept(this);
  } else {
	(*j)["_type"] = "singleVal";
	init_val_list_ast->expr_init_val->accept(this);
  }
}
void AstVisitor::VisitInitVal(InitValAst *init_val_ast) {
  auto j = json.top();
  int count = 0;
  std::stack<std::shared_ptr<Ast>> list;
  while (init_val_ast) {
	list.push(init_val_ast->init_val_list);
	init_val_ast = dynamic_cast<InitValAst *>((init_val_ast->init_val).get());
  }
  while (!list.empty()) {
	json.push(&(*j)["value"][count++]);
	list.top()->accept(this);
	list.pop();
	json.pop();
  }
}

void AstVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  if (binary_expr_ast->left) {
	auto j = json.top();
	(*j)["_type"] = "BinaryExpr";
	(*j)["op"] = binary_expr_ast->op;
	json.push(&(*j)["left"]);
	binary_expr_ast->left->accept(this);
	json.pop();
	json.push(&(*j)["right"]);
	binary_expr_ast->right->accept(this);
	json.pop();
  } else {
	binary_expr_ast->right->accept(this);
  }
}
void AstVisitor::VisitUnaryExpAst(UnaryExprAst *unary_expr_ast) {
  auto j = json.top();
  switch (unary_expr_ast->unaryType) {
	case UnaryType::kPostfix: {
	  unary_expr_ast->unaryExpr->accept(this);
	  break;
	}
	case UnaryType::kUnary: {
	  (*j)["_type"] = "UnaryExpr";
	  auto op = dynamic_cast<UnaryOpAst *>(unary_expr_ast->unaryOp.get());
	  (*j)["op"] = op->op;
	  json.push(&(*j)["unaryExpr"]);
	  unary_expr_ast->unaryExpr->accept(this);
	  json.pop();
	  break;
	}
	case UnaryType::kCall: {
	  (*j)["_type"] = "CallExpr";
	  auto ident = dynamic_cast<IdentifierAst *>(unary_expr_ast->unaryOp.get());
	  (*j)["funcName"] = ident->name;
	  json.push(&(*j)["argList"]);
	  if (unary_expr_ast->unaryExpr) {
		unary_expr_ast->unaryExpr->accept(this);
	  }
	  json.pop();
	  break;
	};
  }
}
void AstVisitor::VisitUnaryOpAst(UnaryOpAst *unary_op_ast) {
}
void AstVisitor::VisitPrimaryExpAst(PrimaryExprAst *primary_expr_ast) {
  primary_expr_ast->primaryExpr->accept(this);
}
void AstVisitor::VisitNumberAst(NumberAst *number_ast) {
  auto j = json.top();
  (*j)["_type"] = "Number";
  (*j)["value"] = getInt(number_ast->value);
  (*j)["address"] = {{"line", number_ast->line}, {"col", number_ast->column}};
}
void AstVisitor::VisitStringAst(StringAst *stringAst) {
  auto j = json.top();
  (*j)["_type"] = "String";
  (*j)["value"] = getString(stringAst->value);
  (*j)["address"] = {{"line", stringAst->line}, {"col", stringAst->column}};
}

void AstVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {
  auto j = json.top();
  (*j)["_type"] = "Identifier";
  (*j)["name"] = identifier_ast->name;
  (*j)["address"] = {{"line", identifier_ast->line}, {"col", identifier_ast->column}};
}
AstVisitor::AstVisitor() {
  nlohmann::json *j = new nlohmann::json;
  json.push(j);
}
void AstVisitor::VisitForStmt(ForStmtAst *) {
  //
}
void AstVisitor::VisitPostfixExprAst(PostfixExprAst *) {
  //
}
