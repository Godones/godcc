//
// Created by linfeng on 2022/4/8.
//

#include "ast_to_ir.h"
// 生成程序主体
void IRGeneratorVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
  DEBUG("IRGeneratorVisitor::VisitCompUnitAst");
  programIr = std::make_shared<Program>();
  if (compUnitAst->comp_unit){
	compUnitAst->comp_unit->accept(this);
  }
  compUnitAst->comp_unit_Item->accept(this);

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
  blockAst->block_item_list->accept(this);
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
  if (binary_expr_ast->left) {
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
  if (unaryExprAst->unaryType == UnaryType::kUnary) {
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
void IRGeneratorVisitor::VisitIfStmt(IfStmtAst *) {
}
void IRGeneratorVisitor::VisitWhileStmt(WhileStmtAst *) {
}
void IRGeneratorVisitor::VisitFuncFParamAst(FuncFParamAst *) {
}
void IRGeneratorVisitor::VisitVarDefList(VarDefListAst *) {
}
void IRGeneratorVisitor::VisitFuncRParamListAst(FuncRParamListAst *) {
}
void IRGeneratorVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
}
void IRGeneratorVisitor::VisitArrayExprList(ArrayExprListAst *) {
}
void IRGeneratorVisitor::VisitInitVal(InitValAst *) {
}
void IRGeneratorVisitor::VisitInitValList(InitValListAst *) {
}
void IRGeneratorVisitor::VisitFuncFParamListAst(FuncFParamListAst *) {
}
void IRGeneratorVisitor::VisitBlockItemListAst(BlockItemListAst *) {
}
void IRGeneratorVisitor::VisitConstDefList(ConstDefListAst *) {
}
