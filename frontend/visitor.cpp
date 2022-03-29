#include "visitor.h"

BinaryOp to_BinaryOp(const std::string_view &op){
  if (op=="+") return BinaryOp::Add;
  if (op=="-") return BinaryOp::Sub;
  if (op=="*") return BinaryOp::Mul;
  if (op=="/") return BinaryOp::Div;
  if (op=="%") return BinaryOp::Mod;
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
  std::cout << funcDefAst->ident << "\n";
  funcDefAst->block->setSpaces(funcDefAst->spaces + 1);
  funcDefAst->block->accept(this);
}

void AstVisitor::VisitFuncTypeAst(FuncTypeAst *funcTypeAst) {
  std::cout << funcTypeAst->type << " ";
}

void AstVisitor::VisitBlockAst(BlockAst *blockAst) {
  blockAst->printSpace();
  std::cout << "BlockAst <>\n";
  blockAst->stmts->setSpaces(blockAst->spaces + 1);
  blockAst->stmts->accept(this);
}

void AstVisitor::VisitStmtAst(StmtAst *stmtAst) {
  stmtAst->printSpace();
  std::cout << "StmtAst <>\n";
  stmtAst->expr->setSpaces(stmtAst->spaces + 1);
  stmtAst->expr->accept(this);
}

void AstVisitor::VisitIdentifierAst(IdentifierAst *identifierAst) {
  identifierAst->printSpace();
  std::cout << "IdentifierAst:\n ";
  std::cout << identifierAst->name;
}

void AstVisitor::VisitExp(ExpAst *expAst) {
  expAst->printSpace();
  std::cout << "ExpAst <>\n";
  expAst->realExpr->setSpaces(expAst->spaces + 1);
  expAst->realExpr->accept(this);

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

void AstVisitor::VisitAddExpAst(AddExprAst *add_expr_ast){
  add_expr_ast->printSpace();
  std::cout << "AddExpAst <> ";
  // 如果存在左子树
  if (add_expr_ast->is_add){
	std::cout << add_expr_ast->op <<"\n";
	add_expr_ast->left->setSpaces(add_expr_ast->spaces + 1);
	add_expr_ast->left->accept(this);
  }
  // 右子树
  std::cout<<"\n";
  add_expr_ast->right->setSpaces(add_expr_ast->spaces + 1);
  add_expr_ast->right->accept(this);
}
void AstVisitor::VisitMulExpAst(MulExprAst *mul_expr_ast) {
  mul_expr_ast->printSpace();
  std::cout << "MulExpAst <> ";
  // 如果存在左子树
  if (mul_expr_ast->is_mul) {
	std::cout << mul_expr_ast->op <<" \n";
	mul_expr_ast->left->setSpaces(mul_expr_ast->spaces + 1);
	mul_expr_ast->left->accept(this);

  }
  // 右子树
  std::cout<<"\n";
  mul_expr_ast->right->setSpaces(mul_expr_ast->spaces + 1);
  mul_expr_ast->right->accept(this);
}
void AstVisitor::VisitUnaryOpAst(UnaryOpAst *unaryOpAst) {
  std::cout << unaryOpAst->op;
}

void AstVisitor::VisitPrimaryExpAst(PrimaryExprAst *primaryExprAst) {
  primaryExprAst->printSpace();
  if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::EXP) {
	std::cout << "PrimaryExpAst <> ()\n";
	primaryExprAst->primaryExpr->setSpaces(primaryExprAst->spaces + 1);
	primaryExprAst->primaryExpr->accept(this);
  } else if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::NUMBER) {

	std::cout << "PrimaryExpAst <>\n";
	primaryExprAst->primaryExpr->setSpaces(primaryExprAst->spaces + 1);
	primaryExprAst->primaryExpr->accept(this);
  }
}

void AstVisitor::VisitNumberAst(NumberAst *numberAst) {
  numberAst->printSpace();
  std::cout << "NumberAst <> " << numberAst->value;
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
  function.name = funcDefAst->ident;
  programIr->functions.emplace_back(function);
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
  blockAst->stmts->accept(this);
  DEBUG("IRGeneratorVisitor::VisitBlockAst");
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

//生成 加减法的中间代码
void IRGeneratorVisitor::VisitAddExpAst(AddExprAst *add_expr_ast) {
	auto& function = programIr->functions.back();
	auto& block = function.blocks.back();
	//解析右表达式
	add_expr_ast->right->accept(this);
	unsigned int record_index = block.instructions.size()-1;
	// 记录右表达式解析出来后的指令位置
	// 后面形成指令需要使用

	//如果有左表达式 解析左表达式
	if (add_expr_ast->is_add){
	  // 形式为AddExp ("+" | "-") MulExp 需要一条新指令
	  add_expr_ast->left->accept(this);
	  auto last_f_instruction = block.instructions.back();
	  auto last_s_instruction = block.instructions[record_index];
	  Instruction instruction{};
	  instruction.instructionType = InstructionType::Binary;
	  instruction.operand1.operand.reg = last_f_instruction.target_register;
	  instruction.operand2.operand.reg = last_s_instruction.target_register;
	  instruction.operand1.isreg = true;
	  instruction.operand2.isreg = true;
	  instruction.binaryOp = to_BinaryOp(add_expr_ast->op);
	  instruction.target_register = register_num_ ++;
	  block.instructions.emplace_back(instruction);
	}
}

// 生成 乘除模的中间代码
void IRGeneratorVisitor::VisitMulExpAst(MulExprAst *mul_expr_ast) {
  auto& function = programIr->functions.back();
  auto& block = function.blocks.back();
  //解析右表达式
  mul_expr_ast->right->accept(this);
  unsigned int record_index = block.instructions.size()-1;
  // 记录右表达式解析出来后的指令位置
  // 后面形成指令需要使用

  //如果有左表达式 解析左表达式
  if (mul_expr_ast->is_mul){
	// 形式为AddExp ("+" | "-") MulExp 需要一条新指令
	mul_expr_ast->left->accept(this);
	auto last_f_instruction = block.instructions.back();
	auto last_s_instruction = block.instructions[record_index];
	Instruction instruction{};
	instruction.instructionType = InstructionType::Binary;
	instruction.operand1.operand.reg = last_f_instruction.target_register;
	instruction.operand2.operand.reg = last_s_instruction.target_register;
	instruction.operand1.isreg = true;
	instruction.operand2.isreg = true;
	instruction.binaryOp = to_BinaryOp(mul_expr_ast->op);
	instruction.target_register = register_num_ ++;
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
  if (unaryExprAst->unaryType == UnaryExprAst::UnaryType::UNARY){
	instruction.instructionType = InstructionType::Binary;
	instruction.operand1.operand.number = 0;
	instruction.operand2.operand.reg = last_instruction.target_register;
	instruction.operand1.isreg = false;
	instruction.operand2.isreg = true;
	instruction.target_register = register_num_++;//设置目标寄存器
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
  if (op == "+"){
	instruction.binaryOp = BinaryOp::Add;
  }else if (op=="-"){
	instruction.binaryOp = BinaryOp::Sub;
  } else if (op=="!"){
	instruction.binaryOp = BinaryOp::Eq;
  } else{
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

void IRGeneratorVisitor::VisitIdentifierAst(IdentifierAst *) {
  //标识符，这里暂时不需要
}
