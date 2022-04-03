#include "visitor.h"

BinaryOp to_BinaryOp(const std::string_view &op) {
  if (op == "+") return BinaryOp::Add;
  if (op == "-") return BinaryOp::Sub;
  if (op == "*") return BinaryOp::Mul;
  if (op == "/") return BinaryOp::Div;
  if (op == "%") return BinaryOp::Mod;
  if (op == "==") return BinaryOp::Eq;
  if (op == "!=") return BinaryOp::Ne;
  if (op == "<") return BinaryOp::Lt;
  if (op == "<=") return BinaryOp::Le;
  if (op == ">") return BinaryOp::Gt;
  if (op == ">=") return BinaryOp::Ge;
  if (op == "&&") return BinaryOp::And;
  if (op == "||") return BinaryOp::Or;
  return BinaryOp::Invalid;
}

void AstVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
  compUnitAst->printSpace();
  std::cout << "CompUnitAST <> \n";
  compUnitAst->funcDef->setSpaces(compUnitAst->spaces + 1);
  compUnitAst->funcDef->accept(this);
}

void AstVisitor::VisitFuncDefAst(FuncDefAst *funcDefAst) {
  funcDefAst->printSpace();
  std::cout << "FuncDefAST <> ";
  funcDefAst->funcType->accept(this);
  funcDefAst->ident->setSpaces(funcDefAst->spaces + 1);
  funcDefAst->ident->accept(this);
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
  for(auto &item: blockAst->blockItems) {
	item->setSpaces(blockAst->spaces + 1);
	item->accept(this);
  }
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
  if (stmtAst->type==StmtType::kDecl) {
	stmtAst->l_val->setSpaces(stmtAst->spaces + 1);
	stmtAst->l_val->accept(this);
  }
  stmtAst->expr->setSpaces(stmtAst->spaces + 1);
  stmtAst->expr->accept(this);
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
  std::cout << "BinaryExprAst <> ";
  // 如果存在左子树
  if (binary_expr_ast->is_two_op) {
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
  std::cout << "UnaryExpAst <> ";
  if (unaryExprAst->unaryType == UnaryExprAst::UnaryType::UNARY) {
	unaryExprAst->unaryOp->accept(this);//一元运算符号
	std::cout << "\n";
	unaryExprAst->unaryExpr->setSpaces(unaryExprAst->spaces + 1);
	unaryExprAst->unaryExpr->accept(this);
  } else {
	std::cout << "\n";
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
  std::cout << const_decl_ast->dataType << "\n";
  for (auto &constDef:const_decl_ast->constDefs) {
	constDef->setSpaces(const_decl_ast->spaces + 1);
	constDef->accept(this);
  }
}
void AstVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  const_def_ast->printSpace();
  std::cout << "ConstDefAst <> \n";
  const_def_ast->ident->setSpaces(const_def_ast->spaces + 1);
  const_def_ast->ident->accept(this);
  const_def_ast->const_val->setSpaces(const_def_ast->spaces + 1);
  const_def_ast->const_val->accept(this);
  std::cout << "\n";
}
void AstVisitor::VisitLVal(LValAst *l_val_ast) {
  l_val_ast->printSpace();
  std::cout << "LValAst <> \n";
  l_val_ast->l_val->setSpaces(l_val_ast->spaces + 1);
  l_val_ast->l_val->accept(this);

}
void AstVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  var_decl_ast->printSpace();
  std::cout << "VarDeclAst <>  ";
  std::cout << var_decl_ast->dataType << "\n";
  for (auto &varDef:var_decl_ast->varDefs) {
	varDef->setSpaces(var_decl_ast->spaces + 1);
	varDef->accept(this);
  }

}
void AstVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  var_def_ast->printSpace();
  std::cout << "VarDefAst <> \n";
  var_def_ast->ident->setSpaces(var_def_ast->spaces + 1);
  var_def_ast->ident->accept(this);
  if (var_def_ast->is_expr) {
	var_def_ast->var_expr->setSpaces(var_def_ast->spaces + 1);
	var_def_ast->var_expr->accept(this);
  }
  std::cout << "\n";
}

// 生成json文件输出图形化显示
void AstViewVisitor::VisitCompUnitAst(CompUnitAst *comp_unit_ast) {
  j_son_.BeganWrite("CompUnit");
  comp_unit_ast->funcDef->accept(this);
  j_son_.EndWrite();
  j_son_.close();
}

void AstViewVisitor::VisitFuncDefAst(FuncDefAst *func_def_ast) {
  j_son_.BeganWrite("FuncDef");
  func_def_ast->funcType->accept(this);
  func_def_ast->ident->accept(this);
  func_def_ast->block->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitFuncTypeAst(FuncTypeAst *func_type_ast) {
  j_son_.BeganWrite("FuncType");
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
  stmt_ast->expr->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitExp(ExpAst *exp_ast) {
  j_son_.BeganWrite("Expr");
  exp_ast->realExpr->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitUnaryExpAst(UnaryExprAst *unary_expr_ast) {
  j_son_.BeganWrite("UnaryExp");
  if (unary_expr_ast->unaryType == UnaryExprAst::UnaryType::UNARY) {
	unary_expr_ast->unaryOp->accept(this);//一元运算符号
  }
  unary_expr_ast->unaryExpr->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitUnaryOpAst(UnaryOpAst *unary_op_ast) {
  j_son_.BeganWrite("UnaryOp");
  j_son_.BeganWrite(unary_op_ast->op);
  j_son_.EndWrite();
  j_son_.EndWrite();
}
void AstViewVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  j_son_.BeganWrite("BinaryExp");
  if (binary_expr_ast->is_two_op) {
	binary_expr_ast->left->accept(this);
	j_son_.BeganWrite(binary_expr_ast->op);
	j_son_.EndWrite();
  }
  binary_expr_ast->right->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitPrimaryExpAst(PrimaryExprAst *primary_expr_ast) {
  j_son_.BeganWrite("PrimaryExp");
  if (primary_expr_ast->primaryType == PrimaryExprAst::PrimaryType::EXP) {
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
  j_son_.BeganWrite("=");
  j_son_.EndWrite();
  const_def_ast->const_val->accept(this);
  j_son_.EndWrite();
}

void AstViewVisitor::VisitLVal(LValAst *l_val_ast) {
  j_son_.BeganWrite("LVal");
  l_val_ast->l_val->accept(this);
  j_son_.EndWrite();
}
void AstViewVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  j_son_.BeganWrite("VarDecl");
  j_son_.BeganWrite(var_decl_ast->dataType);
  j_son_.EndWrite();
  for (auto& var_def :var_decl_ast->varDefs) {
	var_def->accept(this);
  }
  j_son_.EndWrite();
}
void AstViewVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  j_son_.BeganWrite("VarDef");
  var_def_ast->ident->accept(this);
  if (var_def_ast->is_expr){
	j_son_.BeganWrite("=");
	j_son_.EndWrite();
	var_def_ast->var_expr->accept(this);
  }
  j_son_.EndWrite();
}

// 生成程序主体
void IRGeneratorVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
  DEBUG("IRGeneratorVisitor::VisitCompUnitAst");
  programIr = std::make_shared<Program>();
  compUnitAst->funcDef->accept(this);
}

// 生成函数定义
void IRGeneratorVisitor::VisitFuncDefAst(FuncDefAst *funcDefAst) {
  DEBUG("IRGeneratorVisitor::VisitFuncDefAst");
  Function function;
  programIr->functions.emplace_back(function);
  funcDefAst->ident->accept(this);
  funcDefAst->funcType->accept(this);
  funcDefAst->block->accept(this);
}

// 设置函数返回类型
void IRGeneratorVisitor::VisitFuncTypeAst(FuncTypeAst *funcTypeAst) {
  auto &function = programIr->functions.back();
  if (funcTypeAst->type == "int") {
	function.retType = DataType::Int;
  } else if (funcTypeAst->type == "void") {
	function.retType = DataType::Void;
  }
  DEBUG("IRGeneratorVisitor::VisitFuncTypeAst");
}

// 生成函数体
void IRGeneratorVisitor::VisitBlockAst(BlockAst *blockAst) {
  // 获取最后一个函数体
  auto &function = programIr->functions.back();
  BaseBlock block;
  block.blockName = "%entry";
  function.blocks.emplace_back(block);//相当于第一个baseblock
  DEBUG("IRGeneratorVisitor::VisitBlockAst");
  for (auto &item: blockAst->blockItems) {
	item->accept(this);
  }
  DEBUG("IRGeneratorVisitor::VisitBlockAst");
}

void IRGeneratorVisitor::VisitBlockItem(BlockItemAst *blockItemAst) {
  DEBUG("IRGeneratorVisitor::VisitBlockItem");
  blockItemAst->item->accept(this);
}

// 生成函数语句
void IRGeneratorVisitor::VisitStmtAst(StmtAst *stmtAst) {
  //当前只支持return，因此这里不需要对其进行判断，支持其它语句时这里需要修改
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  // 如果是return语句，则生成一个ret指令
  // 第一步 解析return语句中的表达式
  DEBUG("IRGenerator::Stmt");
  stmtAst->expr->accept(this);
  // 建立一个ret指令
  auto last_instruction = block.instructions.back();
  Instruction instruction;
  instruction.operand1.operand.reg = last_instruction.target_register;
  instruction.instructionType = InstructionType::Return;
  // return 语句只使用第一个操作数
  block.instructions.emplace_back(instruction);
}

void IRGeneratorVisitor::VisitExp(ExpAst *expAst) {
  expAst->realExpr->accept(this);
}

// 生成二元表达式的中间表示
void IRGeneratorVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  //解析右表达式
  binary_expr_ast->right->accept(this);
  unsigned int record_index = block.instructions.size() - 1;
  // 记录右表达式解析出来后的指令位置
  // 后面形成指令需要使用

  //如果有左表达式 解析左表达式
  if (binary_expr_ast->is_two_op) {
	// 形式为AddExp ("+" | "-") MulExp 需要一条新指令
	binary_expr_ast->left->accept(this);
	auto last_f_instruction = block.instructions.back();
	auto last_s_instruction = block.instructions[record_index];
	Instruction instruction{};
	instruction.instructionType = InstructionType::Binary;
	instruction.operand1.operand.reg = last_f_instruction.target_register;
	instruction.operand2.operand.reg = last_s_instruction.target_register;
	instruction.operand1.isreg = true;
	instruction.operand2.isreg = true;
	instruction.binaryOp = to_BinaryOp(binary_expr_ast->op);
	// 设置目标寄存器为第一个操作数的寄存器
	instruction.target_register = last_s_instruction.target_register;
	block.instructions.emplace_back(instruction);
  }
}

// 生成一元表达式
void IRGeneratorVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
  // 获得最后一个base_block
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  unaryExprAst->unaryExpr->accept(this);
  // 构建指令
  Instruction instruction{};
  // 所有的一元运算转换为二元运算
  Instruction last_instruction = block.instructions.back();
  // 对于一元运算符，需要生成一个指令
  // 如 -5 / -(?)
  // 先解析符号后面的表达式
  if (unaryExprAst->unaryType == UnaryExprAst::UnaryType::UNARY) {
	instruction.instructionType = InstructionType::Unary;
	instruction.operand1.operand.number = 0;
	instruction.operand2.operand.reg = last_instruction.target_register;
	instruction.operand1.isreg = false;
	instruction.operand2.isreg = true;
	//设置目标寄存器
	instruction.target_register = last_instruction.target_register;
	// 放入最后一条指令
	block.instructions.emplace_back(instruction);
	// 设置运算类型
	unaryExprAst->unaryOp->accept(this);
  }
}

void IRGeneratorVisitor::VisitUnaryOpAst(UnaryOpAst *unaryOpAst) {
  // 所有的一元运算符可以转化为二元运算符
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  auto &instruction = block.instructions.back();
  std::string_view op = unaryOpAst->op;
  if (op == "+") {
	instruction.binaryOp = BinaryOp::Add;
  } else if (op == "-") {
	instruction.binaryOp = BinaryOp::Sub;
  } else if (op == "!") {
	instruction.binaryOp = BinaryOp::Eq;
  } else {
	// 引发错误
	// todo!(一元运算符异常)
	exit(-1);
  }
}

void IRGeneratorVisitor::VisitPrimaryExpAst(PrimaryExprAst *primaryExprAst) {
  // (Exp) number
  // todo!(如果是常数，不需要单独放入寄存器中)
  primaryExprAst->primaryExpr->accept(this);
}

void IRGeneratorVisitor::VisitNumberAst(NumberAst *numberAst) {
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  Instruction instruction{};
  instruction.instructionType = InstructionType::Integer;
  instruction.operand1.operand.number = numberAst->value;
  instruction.target_register = register_num_++;
  block.instructions.emplace_back(instruction);
}

void IRGeneratorVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {
  //标识符
  auto &function = programIr->functions.back();
  function.name = identifier_ast->name;
}

void IRGeneratorVisitor::VisitDecl(DeclAst *) {
}
void IRGeneratorVisitor::VisitConstDecl(ConstDeclAst *) {
}
void IRGeneratorVisitor::VisitConstDef(ConstDefAst *) {
}
void IRGeneratorVisitor::VisitLVal(LValAst *) {
}
void IRGeneratorVisitor::VisitVarDecl(VarDeclAst *) {
}
void IRGeneratorVisitor::VisitVarDef(VarDefAst *) {
}
