//
// Created by linfeng on 2022/5/3.
//

#include "semantic.h"

void SemanticVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  ast->comp_unit->accept(this);
}
void SemanticVisitor::VisitCompUnitAst(CompUnitAst *comp_unit_ast) {
  if (comp_unit_ast->comp_unit){
	comp_unit_ast->comp_unit->accept(this);
  }
  comp_unit_ast->comp_unit_Item->accept(this);
}
void SemanticVisitor::VisitFuncDefAst(FuncDefAst *func_def_ast) {
  auto type = dynamic_cast<FuncTypeAst*>(func_def_ast->funcType.get());
  auto ident = dynamic_cast<IdentifierAst*>(func_def_ast->ident.get());
  //在符号表建立信息
  auto func_info = new FuncInfo();
  func_info->ret_type = getFuncType(*type); //返回值类型
  if( globalSymbolTable->has_symbol(ident->name)){
	//函数重定义
	ERROR("address:%d-%d, function:%s has been defined", ident->line, ident->column, ident->name);
	// 将函数的信息删除
	globalSymbolTable->delete_symbol(ident->name);
  }
  globalSymbolTable->add_symbol(ident->name, {DataType::kFunc,0, false,(void *)func_info});
  if (func_def_ast->funcParamList){
	//建立参数表
	func_def_ast->funcParamList->accept(this);
  }
  func_def_ast->block->accept(this);
}
void SemanticVisitor::VisitFuncTypeAst(FuncTypeAst *) {}

void SemanticVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {
  if (func_f_param_list_ast->funcFParamList){
	func_f_param_list_ast->funcFParamList->accept(this);
  }
  func_f_param_list_ast->funcFParam->accept(this);
}

void SemanticVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
  auto type = dynamic_cast<FuncTypeAst*>(func_f_param_ast->funcType.get());
  auto ident = dynamic_cast<IdentifierAst*>(func_f_param_ast->ident.get());
  //在符号表建立信息
  // 此时函数信息位于符号表的最后一个
  auto item = globalSymbolTable->get_symbol(globalSymbolTable->key_list.back());
  assert(item);
  auto param_info = (FuncInfo*)(item->ptr);
  auto param_type = getFuncType(*type);
  if(param_info->has_param(param_type,ident->name)){
	//参数重定义
	ERROR("address:%d-%d, %s has been defined", ident->line, ident->column, ident->name);
  }
  param_info->params.emplace_back(SymbolInfo{param_type,0, false, nullptr,ident->name});//参数类型
  //数组暂时不管
  bool first = false;
  if(func_f_param_ast->first_no_dim){
	first = true;
  }
  if (func_f_param_ast->array_expr_list){
	func_f_param_ast->array_expr_list->accept(this);
  }
}

void SemanticVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (func_r_param_list_ast){
	list.push(func_r_param_list_ast->expr);
	func_r_param_list_ast = dynamic_cast<FuncRParamListAst *>((func_r_param_list_ast->funcRParamListAst).get());
  }
  while (!list.empty()){
	list.top()->accept(this);
	list.pop();
  }
}
void SemanticVisitor::VisitBlockAst(BlockAst *block_ast) {
  // 遇到{}时，进入新的作用域
  globalSymbolTable = globalSymbolTable->enter_scope();
  block_ast->block_item_list->accept(this);
  globalSymbolTable = globalSymbolTable->exit_scope();
}

void SemanticVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
  if (block_item_list_ast->block_item_list){
	block_item_list_ast->block_item_list->accept(this);
  }
  block_item_list_ast->block_item->accept(this);
}

void SemanticVisitor::VisitBlockItem(BlockItemAst *block_item_ast) {
  block_item_ast->item->accept(this);
}

void SemanticVisitor::VisitStmtAst(StmtAst *stmt_ast) {
  switch (stmt_ast->type) {
	case StmtType::kReturn: {
	  if (stmt_ast->expr){
		// 进行求值，后续可以直接使用
		stmt_ast->expr->accept(this);
	  }
	  break;
	};
	case StmtType::kAssign: {
	  stmt_ast->l_val->accept(this);
	  stmt_ast->expr->accept(this);
	  // 重新赋值
	  auto l_val = dynamic_cast<LValAst*>(stmt_ast->l_val.get());
	  auto ident = dynamic_cast<IdentifierAst*>(l_val->l_val.get());
	  auto expr = dynamic_cast<ExpAst*>(stmt_ast->expr.get());
	  //已经保证了l_val是可以赋值的
	  auto item = globalSymbolTable->get_symbol(ident->name);
	  if (item){
		if (expr->have_value){
		  item->value = expr->value;
		  item->have_value = true;
		}
	  }
	  break;
	};
	case StmtType::kBlock: {
	  stmt_ast->expr->accept(this);
	  break;
	};
	case StmtType::kExpr: {
//	  if (stmt_ast->expr)
//		stmt_ast->expr->accept(this);
		//空表达式不用管
	  break;
	};
	case StmtType::kIf: {
	  stmt_ast->expr->accept(this);
	  break;
	};
	case StmtType::kWhile: {
	  stmt_ast->expr->accept(this);
	  break;
	};
	case StmtType::kBreak: {
	  //需要保证在循环中 需要一个标志标明当前处于while循环中
	  if(!while_flag){
		ERROR("address:%d-%d :break must be in while loop", stmt_ast->line, stmt_ast->column);
	  }
	  break;
	};
	case StmtType::kContinue: {
	  //需要保证在循环中
	  if(!while_flag){
		ERROR("address:%d-%d :continue must be in while loop", stmt_ast->line, stmt_ast->column);
	  }
	  // 语义检查不处理其它内容
	  break;
	};
  }
}
void SemanticVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
  // 处理if语句
  if_stmt_ast->expr->accept(this);
  //保证条件可以求出值
  auto expr = dynamic_cast<ExpAst*>(if_stmt_ast->expr.get());
  if (!expr->have_value){
	ERROR("address:%d-%d, if语句条件不能求值", if_stmt_ast->line, if_stmt_ast->column);
  }
  if_stmt_ast->stmt->accept(this);
  if (if_stmt_ast->elseStmt) {
	if_stmt_ast->elseStmt->accept(this);
  }
}
void SemanticVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
  while_stmt_ast->expr->accept(this);
  auto expr = dynamic_cast<ExpAst*>(while_stmt_ast->expr.get());
  if (!expr->have_value){
	ERROR("address:%d-%d, while语句条件不能求值", while_stmt_ast->line, while_stmt_ast->column);
  }
  // 在while语句中，需要一个标志标明当前处于while循环中
  // 保存当前的while_flag
  auto old_while_flag = while_flag;
  while_flag = true; //标志当前处于while循环中
  while_stmt_ast->stmt->accept(this);
  while_flag = false; //标志当前不再处于while循环中
  // 恢复之前的while_flag
  while_flag = old_while_flag;
}
void SemanticVisitor::VisitExp(ExpAst *exp_ast) {
  exp_ast->realExpr->accept(this);
  auto expr = dynamic_cast<BinaryExprAst*>(exp_ast->realExpr.get());
  assert(expr); //表达式下面肯定是二元表达式
  if (expr->have_value) {
	exp_ast->have_value = true;
	exp_ast->value = expr->value;
  }
}
void SemanticVisitor::VisitDecl(DeclAst *decl_ast) {
  decl_ast->decl->accept(this);
}

void SemanticVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  type_current = DataType::kConstInt; //标明当前的类型
  const_decl_ast->const_def_list->accept(this);//访问常量定义列表
}

void SemanticVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
  if (const_def_list_ast->const_def_list){
	const_def_list_ast->const_def_list->accept(this);
  }
  const_def_list_ast->const_def->accept(this);
}
void SemanticVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  auto ident = dynamic_cast<IdentifierAst*>(const_def_ast->ident.get());
  if(globalSymbolTable->has_symbol(ident->name)){
	// 重复定义
	ERROR("address:%d-%d type:ES02 %s duplicate definition",const_def_ast->line,const_def_ast->column,ident->name);
	return ;
  }
  globalSymbolTable->add_symbol(ident->name, {type_current,}); //填类型
  //记录当前的常量
  auto item = globalSymbolTable->get_symbol(ident->name);
  if (const_def_ast->array_expr_list){
	const_def_ast->array_expr_list->accept(this);
  }
  // 这里假设还没有数组
  const_def_ast->const_val->accept(this); //求值
  auto val = dynamic_cast<InitValListAst*>(const_def_ast->const_val.get());
//  DEBUG("value number: %d", val->values.size());
  if (val->values.empty()) {
	ERROR("address:%d-%d, no value for const", ident->line, ident->column);
  } else {
	// 填入常量表
	if (val->values.size() != 1) {
	  WARNING("address:%d-%d excess elements in scalar initializer", const_def_ast->line, const_def_ast->column);
	}
	(*item).have_value = true;
	(*item).value = val->values[0];
  }
}

void SemanticVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  type_current = DataType::kInt; //标明当前的类型
  var_decl_ast->var_def_list->accept(this);
}

void SemanticVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
  if(var_def_list_ast->varDefList){
	var_def_list_ast->varDefList->accept(this);
  }
  var_def_list_ast->varDef->accept(this);
}
void SemanticVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  auto ident = dynamic_cast<IdentifierAst*>(var_def_ast->ident.get());
  if(globalSymbolTable->has_symbol(ident->name)){
	// 重复定义
	ERROR("address:%d-%d type:ES02 %s duplicate definition",var_def_ast->line,var_def_ast->column,ident->name);
	return ;
  }
  globalSymbolTable->add_symbol(ident->name, {type_current,}); //填类型
  //记录当前的变量
  auto item = globalSymbolTable->get_symbol(ident->name);
  if (var_def_ast->array_expr_list){
	var_def_ast->array_expr_list->accept(this);
  }
  // 这里假设还没有数组
  if(var_def_ast->var_expr){ //如果有初始化
	var_def_ast->var_expr->accept(this); //求值
	auto val = dynamic_cast<InitValListAst*>(var_def_ast->var_expr.get());
	  // 填入常量表
//	DEBUG("value:%d", val->values.size());
	if (val->values.size() > 1) {
	  //如果不是数组但是使用了数组初始化
	  WARNING("address:%d-%d excess elements in scalar initializer", var_def_ast->line, var_def_ast->column);
	}
	if (!val->values.empty()) {
	  // 初始化不为空就取第一个值
	  (*item).have_value = true;
	  (*item).value = val->values[0];
	}
  }
}
void SemanticVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (array_expr_list_ast){
	list.push(array_expr_list_ast->array_expr);
	array_expr_list_ast = dynamic_cast<ArrayExprListAst *>((array_expr_list_ast->array_expr_list).get());
  }
  while (!list.empty()){
	list.top()->accept(this);
	list.pop();
  }
}
void SemanticVisitor::VisitInitVal(InitValAst *init_val_ast) {
  if (init_val_ast->init_val){
	init_val_ast->init_val->accept(this);
	auto init_val = dynamic_cast<InitValAst*>(init_val_ast->init_val.get());
	init_val_ast->values = init_val->values;
  }
  init_val_ast->init_val_list->accept(this);
  // 继承属性
  auto init_val_list = dynamic_cast<InitValListAst*>(init_val_ast->init_val_list.get());
  for(auto &val : init_val_list->values){
	init_val_ast->values.push_back(val);
  }
}
void SemanticVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
  auto expr = dynamic_cast<InitValAst*>(init_val_list_ast->expr_init_val.get());
  if (expr||init_val_list_ast->expr_init_val== nullptr) {
	// {initval} /{ }数组初始化
	if (expr) {
	  expr->accept(this);
	  init_val_list_ast->values = expr->values;
	}
  } else{
	//表达式 expr
	init_val_list_ast->expr_init_val->accept(this); //对表达式求值
	auto expr_ = dynamic_cast<ExpAst*>(init_val_list_ast->expr_init_val.get());
	if(expr_->have_value){
	  //存入值
	  init_val_list_ast->values.emplace_back(expr_->value);
	}
  }
}
int calculate(int left,int right,std::string_view op){
  if (op=="+"){
	return left+right;
  } else if (op=="-"){
	return left-right;
  } else if (op=="*"){
	return left*right;
  } else if (op=="/"){
	return left/right;
  } else if (op=="%"){
	return left%right;
  } else if (op=="&&"){
	return left&&right;
  } else if (op=="||"){
	return left||right;
  } else if (op=="=="){
	return left==right;
  } else if (op=="!="){
	return left!=right;
  } else if (op==">"){
	return left>right;
  } else if (op=="<"){
	return left < right;
  } else if (op==">="){
	return left >= right;
  } else if (op=="<="){
	return left <= right;
  } else if (op=="!"){
	return !right; //针对一元表达式的!
  }else{
	assert(false);
  }
}

void SemanticVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  //二元表达式求值重点
  if (binary_expr_ast->left) {
	// 有左节点 必定包含右节点
	// 除了乘除法节点外，其它的都是BinaryExpAst
	binary_expr_ast->left->accept(this);
	binary_expr_ast->right->accept(this);
	auto left = dynamic_cast<BinaryExprAst *>(binary_expr_ast->left.get());
	if (binary_expr_ast->type != BinaryType::kMul) {
	  auto right = dynamic_cast<BinaryExprAst *>(binary_expr_ast->right.get());
	  if (left->have_value && right->have_value) {
		binary_expr_ast->value = calculate(left->value, right->value, binary_expr_ast->op);
		binary_expr_ast->have_value = true;
	  }
	} else {
	  // 乘法节点的右表达式是unary表达式
	  auto right = dynamic_cast<UnaryExprAst *>(binary_expr_ast->right.get());
	  if (left->have_value && right->have_value) {
		binary_expr_ast->value = calculate(left->value, right->value, binary_expr_ast->op);
		binary_expr_ast->have_value = true;
	  }
	}
  }
  else{
	binary_expr_ast->right->accept(this);
	auto right = dynamic_cast<BinaryExprAst *>(binary_expr_ast->right.get());
	if (right) {
	  //右节点可能不是二元表达式，可能是乘法节点处的一元表达式
	  if (right->have_value) {
		binary_expr_ast->value = right->value;
		binary_expr_ast->have_value = true;
	  }
	} else {
	  auto right_ = dynamic_cast<UnaryExprAst *>(binary_expr_ast->right.get());
	  assert(right_);//保证是一元表达式
	  if (right_->have_value) {
		binary_expr_ast->value = right_->value;
		binary_expr_ast->have_value = true;
	  }
	}
  }

}
void SemanticVisitor::VisitUnaryExpAst(UnaryExprAst *unary_expr_ast) {
  switch (unary_expr_ast->unaryType) {
	case UnaryType::kPrimary: {
	  unary_expr_ast->unaryExpr->accept(this);
	  // 基本表达式
	  auto primary = dynamic_cast<PrimaryExprAst*>(unary_expr_ast->unaryExpr.get());
	  if (primary->have_value){
		unary_expr_ast->value = primary->value;
		unary_expr_ast->have_value = true;
	  }
	  break;
	}
	case UnaryType::kUnary: {
	  auto op = dynamic_cast<UnaryOpAst*>(unary_expr_ast->unaryOp.get());
	  unary_expr_ast->unaryExpr->accept(this);
	  auto unary = dynamic_cast<UnaryExprAst*>(unary_expr_ast->unaryExpr.get());
	  if (unary->have_value){
		unary_expr_ast->value = calculate(0, unary->value, op->op);
		unary_expr_ast->have_value = true;
	  }
	  break;
	};
	case UnaryType::kCall: {
	  //函数调用，暂不处理
	  unary_expr_ast->unaryOp->accept(this);
	  if (unary_expr_ast->unaryExpr){
		unary_expr_ast->unaryExpr->accept(this);
	  }
	  break;
	};
  }
}
void SemanticVisitor::VisitPrimaryExpAst(PrimaryExprAst *primary_expr_ast) {
  switch (primary_expr_ast->primaryType) {
	case PrimaryType::EXP:{
	  primary_expr_ast->primaryExpr->accept(this);//表达式先求值
	  auto exp = dynamic_cast<ExpAst*>(primary_expr_ast->primaryExpr.get());
	  if (exp->have_value){
		primary_expr_ast->have_value = true;
		primary_expr_ast->value = exp->value;
	  }
	  break;
	}
	case PrimaryType::NUMBER: {
	  auto number = dynamic_cast<NumberAst*>(primary_expr_ast->primaryExpr.get());
	  primary_expr_ast->have_value = true;
	  primary_expr_ast->value = number->value;
	  break ;
	};
	case PrimaryType::IDENTIFIER: {
	  // 左值，需要查找符号表是否有对应的符号存在
	  primary_expr_ast->primaryExpr->accept(this);//左值节点
	  auto l_val = dynamic_cast<LValAst*>(primary_expr_ast->primaryExpr.get());
	  if(l_val->have_value){
		primary_expr_ast->have_value = true;
		primary_expr_ast->value = l_val->value;
	  }
	};
  }
}
void SemanticVisitor::VisitLVal(LValAst *l_val_ast) {
  auto ident = dynamic_cast<IdentifierAst*>(l_val_ast->l_val.get());
  assert(ident);
  auto symbol = globalSymbolTable->get_symbol(ident->name);
  if(!symbol){
	//符号不存在
	ERROR("address:%d-%d undefined variable: %s",l_val_ast->line,l_val_ast->column,ident->name);
  }else{
	if(symbol->have_value){
	  l_val_ast->have_value = true;
	  l_val_ast->value = symbol->value;
	}
  }
  if (l_val_ast->array_expr_list){
	//数组暂时不管
	l_val_ast->array_expr_list->accept(this);
  }
}
void SemanticVisitor::VisitNumberAst(NumberAst *number_ast) {}
void SemanticVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {}
void SemanticVisitor::VisitUnaryOpAst(UnaryOpAst *) {
}
SemanticVisitor::SemanticVisitor() {
  globalSymbolTable = new SymbolTable();
}
SemanticVisitor::~SemanticVisitor() {
  delete globalSymbolTable;
}
