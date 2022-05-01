//
// Created by linfeng on 2022/4/8.
//

#include "ast_to_ir.h"

// 生成程序主体
void IRGeneratorVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  programIr = std::make_shared<Program>();
  ast->comp_unit->accept(this);
}
void IRGeneratorVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
  DEBUG("IRGeneratorVisitor::VisitCompUnitAst");
  std::stack<std::shared_ptr<Ast>> comp_unit_list;
  while (compUnitAst){
	comp_unit_list.push(compUnitAst->comp_unit_Item);
	compUnitAst = dynamic_cast<CompUnitAst *>((compUnitAst->comp_unit).get());
  }
  while (!comp_unit_list.empty()){
	comp_unit_list.top()->accept(this);
	comp_unit_list.pop();
  }
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
  blockAst->block_item_list->accept(this);
}
void IRGeneratorVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
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
void IRGeneratorVisitor::VisitBlockItem(BlockItemAst *blockItemAst) {
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
  switch (stmtAst->type) {
	case StmtType::kReturn:{
	  stmtAst->expr->accept(this);
	  // 建立一个ret指令
	  DEBUG("block_len: %d", block.instructions.size());
	  auto last_instruction = block.instructions.back();
	  Instruction instruction{};
	  instruction.operand1.operand.reg = last_instruction.target_register;
	  instruction.instructionType = InstructionType::Return;
	  // return 语句只使用第一个操作数
	  block.instructions.emplace_back(instruction);
	}
	default:break;
  }

}

void IRGeneratorVisitor::VisitExp(ExpAst *expAst) {
  expAst->realExpr->accept(this);
}

// 生成二元表达式的中间表示
void IRGeneratorVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  // 左节点存在，则一定会有右节点
  if (binary_expr_ast->left){
	// 先解析左子树，可以在发生错误时提前退出
	binary_expr_ast->left->accept(this);
	// 建立一个binary指令
	auto &function = programIr->functions.back();
	auto &block = function.blocks.back();
	// 记录左表达式解析出来后的指令位置
	// 后面形成指令需要使用
	unsigned int record_index = block.instructions.size() - 1;
	binary_expr_ast->right->accept(this);
	// 形式为AddExp ("+" | "-") MulExp 需要一条新指令
	auto last_r_instruction = block.instructions.back();
	auto last_l_instruction = block.instructions[record_index];
	Instruction instruction{};
	instruction.instructionType = InstructionType::Binary;
	instruction.operand1.operand.reg = last_l_instruction.target_register;
	instruction.operand2.operand.reg = last_r_instruction.target_register;
	instruction.operand1.isreg = true;
	instruction.operand2.isreg = true;
	instruction.binaryOp = to_BinaryOp(binary_expr_ast->op);
	// 设置目标寄存器为第一个操作数的寄存器
	instruction.target_register = last_l_instruction.target_register;
	block.instructions.emplace_back(instruction);
  }else{
	assert(binary_expr_ast->right);
	binary_expr_ast->right->accept(this);
  }
}

// 生成一元表达式
void IRGeneratorVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
  // 获得最后一个base_block
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  switch (unaryExprAst->unaryType) {
	case UnaryType::kPrimary: {
	  unaryExprAst->unaryExpr->accept(this);
	  break;
	};
	case UnaryType::kUnary: {
	  unaryExprAst->unaryExpr->accept(this);
	  // 构建指令
	  Instruction instruction{};
	  // 所有的一元运算转换为二元运算
	  Instruction last_instruction = block.instructions.back();
	  // 对于一元运算符，需要生成一个指令
	  // 如 -5 / -(?)
	  // 先解析符号后面的表达式
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
	};
	case UnaryType::kCall: break;
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

void IRGeneratorVisitor::VisitDecl(DeclAst *decl_ast) {
  decl_ast->decl->accept(this);
}
void IRGeneratorVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  // 常量定义，需要在编译器求出其值

}
void IRGeneratorVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
}
void IRGeneratorVisitor::VisitLVal(LValAst *l_val_ast) {
}
void IRGeneratorVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
}
void IRGeneratorVisitor::VisitVarDef(VarDefAst *var_def_ast) {
}
void IRGeneratorVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
}
void IRGeneratorVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
}
void IRGeneratorVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {
}
void IRGeneratorVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
}
void IRGeneratorVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_list_ast) {
}

void IRGeneratorVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
}
void IRGeneratorVisitor::VisitInitVal(InitValAst *init_val_ast) {
}
void IRGeneratorVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
}
void IRGeneratorVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {
}

void IRGeneratorVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
}
