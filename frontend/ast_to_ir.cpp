//
// Created by linfeng on 2022/4/8.
//

#include "ast_to_ir.h"

// 生成程序主体
void IRGeneratorVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  programIr = std::make_shared<Program>();
  programIr->global_block = new BaseBlock();
  ast->comp_unit->accept(this);
}
void IRGeneratorVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
  if (compUnitAst->comp_unit) {
	compUnitAst->comp_unit->accept(this);
  }
  compUnitAst->comp_unit_Item->accept(this);
}

// 生成函数定义
void IRGeneratorVisitor::VisitFuncDefAst(FuncDefAst *funcDefAst) {
  // 在进入函数后需要重置label_record、number_record
  // todo!(将语义分析得到的符号表中的函数定义复制到中间代码的符号表中)

  label_record = 0;
  number_record = 0;
  auto ident = dynamic_cast<IdentifierAst *>(funcDefAst->ident.get());
  //在m_symbolTable中找到函数定义的条目
  auto item = m_symbolTable->get_symbol(ident->name);
  //拷贝到中间代码的符号表中
  globalSymbolTable->add_symbol(ident->name, *item);
  Function function;
  function.blocks.reserve(100);
  function.name = ident->name;
  assert(item->type == DataType::kFunc);
  auto func_item = static_cast<FuncInfo *>(item->ptr);
  function.retType = func_item->ret_type;

  //提前进入block
  globalSymbolTable = globalSymbolTable->new_scope();
  m_symbolTable = m_symbolTable->enter_scope();
  for (auto &param : func_item->params) {
	Instruction instruction;
	instruction.instructionType = InstructionType::FuncArgRef;
	instruction.dataType = param.type;
	function.params.emplace_back(instruction);
	globalSymbolTable->add_symbol(param.name, param);
  }
  BaseBlock baseBlock(label_record++);//进入函数体 创建一个基本块
  function.blocks.emplace_back(baseBlock);
  programIr->functions.emplace_back(function);
  auto block = dynamic_cast<BlockAst *>(funcDefAst->block.get());
  auto block_item_list = dynamic_cast<BlockItemListAst *>(block->block_item_list.get());
  block_item_list->accept(this);
  globalSymbolTable = globalSymbolTable->exit_scope();
  m_symbolTable = m_symbolTable->exit_scope();
}

void IRGeneratorVisitor::VisitFuncTypeAst(FuncTypeAst *funcTypeAst) {
}

void IRGeneratorVisitor::VisitBlockAst(BlockAst *blockAst) {
  // 需要进入新的作用域
  // 获取最后一个函数体
  auto &function = programIr->functions.back();
  m_symbolTable = m_symbolTable->enter_scope();//进入新的作用域
  globalSymbolTable = globalSymbolTable->new_scope();
  blockAst->block_item_list->accept(this);
  globalSymbolTable = globalSymbolTable->exit_scope();
  m_symbolTable = m_symbolTable->exit_scope();//退出作用域
}
void IRGeneratorVisitor::VisitBlockItemListAst(BlockItemListAst *block_item_list_ast) {
  if (block_item_list_ast->block_item_list) {
	block_item_list_ast->block_item_list->accept(this);
  }
  block_item_list_ast->block_item->accept(this);
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
  switch (stmtAst->type) {
	case StmtType::kReturn: {
	  // 建立一个ret指令
	  auto expr = dynamic_cast<ExpAst *>(stmtAst->expr.get());
	  Instruction instruction{};
	  instruction.instructionType = InstructionType::Return;

	  auto f_set = [&](OperandType type, int number) {
		instruction.operand1.type = type;
		instruction.operand1.operand.number = number;
	  };
	  if (expr) {
		if (expr->have_value) {
		  f_set(OperandType::kInteger, expr->value);
		} else {
		  expr->accept(this);
		  //获取上一条四元式的标号
		  auto last_instruction = block.instructions.back();
		  f_set(OperandType::kNumber, last_instruction.m_number);
		}
	  } else {
		//返回空值
		// 将第一个操作数设置为kstring作为标记
		f_set(OperandType::kString, 0);
	  }
	  // return 语句只使用第一个操作数
	  block.instructions.emplace_back(instruction);
	  break;
	}
	case StmtType::kAssign: {
	  // 赋值语句
	  auto l_val = dynamic_cast<LValAst *>(stmtAst->l_val.get());
	  auto ident = dynamic_cast<IdentifierAst *>(l_val->l_val.get());

	  //	  auto item = globalSymbolTable->get_symbol(ident->name);

	  auto item_with_level = m_symbolTable->get_symbol_with_level(ident->name);
	  auto item = item_with_level.second;
	  auto expr = dynamic_cast<ExpAst *>(stmtAst->expr.get());

	  if (expr->have_value) {
		// 如果是数字，则直接生成一个指令
		Instruction instruction = {
			.instructionType = InstructionType::Store,
			.dataType = item->type,
			.operand1 = {.operand = {.number = expr->value}, .type = OperandType::kInteger},
			.operand2 = {.operand = {
							 .symbol = makeSymbolWithLevel(ident->name, item_with_level.first)->c_str()},
						 .type = OperandType::kString},
		};
		block.instructions.emplace_back(instruction);
	  } else {
		stmtAst->expr->accept(this);
		// 获取上一条四元式的标号
		auto last_instruction = block.instructions.back();
		Instruction instruction = {
			.instructionType = InstructionType::Store,
			.dataType = item->type,
			.operand1 = {.operand = {.number = last_instruction.m_number}, .type = OperandType::kNumber},
			.operand2 = {.operand = {.symbol = makeSymbolWithLevel(ident->name, item_with_level.first)->c_str()},
						 .type = OperandType::kString},
		};
		block.instructions.emplace_back(instruction);
	  }
	  //已经保证了l_val是可以赋值的
	  break;
	}
	case StmtType::kExpr: {
	  if (stmtAst->expr) {
		stmtAst->expr->accept(this);
	  }
	  break;
	}
	case StmtType::kBlock: {
	  stmtAst->expr->accept(this);
	  break;
	}
	case StmtType::kWhile: {
	  // while 语句
	  stmtAst->expr->accept(this);
	  break;
	}
	case StmtType::kIf: {
	  // if语句
	  stmtAst->expr->accept(this);
	  break;
	}
	case StmtType::kBreak: {
	  // break语句
	  Instruction instruction = make_jump(-1);
	  block.instructions.emplace_back(instruction);
	  // 记录当前的block_index,instruction_index
	  break_instruction.emplace_back(function.blocks.size() - 1, block.instructions.size() - 1);
	  break;
	}
	case StmtType::kContinue: {
	  // continue语句
	  Instruction instruction = make_jump(while_begin_label.top());
	  block.instructions.emplace_back(instruction);
	  break;
	}
	default: break;
  }
}

void IRGeneratorVisitor::VisitExp(ExpAst *expAst) {
  expAst->realExpr->accept(this);
}

// 生成二元表达式的中间表示
void IRGeneratorVisitor::VisitBinaryExpAst(BinaryExprAst *binary_expr_ast) {
  // 左节点存在，则一定会有右节点
  if (binary_expr_ast->left) {
	// 如果左右节点的值均已经求出，则不会进入此节点
	// 只有左节点或者右节点没有求出，才会进入此节点
	auto left_expr = dynamic_cast<BinaryExprAst *>(binary_expr_ast->left.get());
	Instruction instruction{};
	instruction.instructionType = InstructionType::Binary;
	instruction.binaryOp = to_BinaryOp(binary_expr_ast->op);
	auto set_operand1 = [&](OperandType type, int number) {
	  instruction.operand1.type = type;
	  instruction.operand1.operand.number = number;
	};
	auto set_operand2 = [&](OperandType type, int number) {
	  instruction.operand2.type = type;
	  instruction.operand2.operand.number = number;
	};
	if (left_expr->have_value) {
	  set_operand1(OperandType::kInteger, left_expr->value);
	} else {
	  //  	2+a
	  // 上面的二元表达式节点生成的中间代码形式为
	  //  %2 = load i32, i32* %a
	  //  %3 = add i32 2,i32 %2
	  left_expr->accept(this);
	  auto last_instruction = programIr->functions.back().blocks.back().instructions.back();
	  set_operand1(OperandType::kNumber, last_instruction.m_number);
	}
	if (binary_expr_ast->type != BinaryType::kMul) {
	  auto right_expr = dynamic_cast<BinaryExprAst *>(binary_expr_ast->right.get());
	  if (right_expr->have_value) {
		set_operand2(OperandType::kInteger, right_expr->value);
	  } else {
		right_expr->accept(this);
		auto last_instruction = programIr->functions.back().blocks.back().instructions.back();
		set_operand2(OperandType::kNumber, last_instruction.m_number);
	  }
	} else {
	  auto right_expr = dynamic_cast<UnaryExprAst *>(binary_expr_ast->right.get());
	  if (right_expr->have_value) {
		set_operand2(OperandType::kInteger, right_expr->value);
	  } else {
		right_expr->accept(this);
		auto last_instruction = programIr->functions.back().blocks.back().instructions.back();
		set_operand2(OperandType::kNumber, last_instruction.m_number);
	  }
	}
	instruction.m_number = number_record++;// 产生当前四元式的标号
	programIr->functions.back().blocks.back().instructions.emplace_back(instruction);
  } else {
	// 只有右节点的情况下，需要进入到一元表达式部分进行处理
	assert(binary_expr_ast->right);
	binary_expr_ast->right->accept(this);
  }
}

// 生成一元表达式
void IRGeneratorVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
  // 获得最后一个base_block
  auto &function = programIr->functions.back();

  switch (unaryExprAst->unaryType) {
	case UnaryType::kPrimary: {
	  unaryExprAst->unaryExpr->accept(this);
	  break;
	};
	case UnaryType::kUnary: {
	  // 所有的一元运算转换为二元运算
	  // 如 -5 / -(?)
	  // 先解析符号后面的表达式
	  // 只有操作数无法求值时才会进入到这里
	  assert(!unaryExprAst->have_value);
	  unaryExprAst->unaryExpr->accept(this);
	  auto &block = function.blocks.back();
	  auto last_instruction = block.instructions.back();
	  Instruction instruction = {
		  .instructionType = InstructionType::Binary,
		  .operand1 = {.operand = {.number = 0}, .type = OperandType::kInteger},
		  .operand2 = {.operand = {.number = last_instruction.m_number}, .type = OperandType::kInteger},
		  .m_number = number_record++,
	  };
	  unaryExprAst->unaryOp->accept(this);// 设置二元符号
	  block.instructions.emplace_back(instruction);
	  break;
	};
	case UnaryType::kCall: {
	  // 函数调用
	  // 函数调用的情况下，需要生成一个函数调用指令
	  // 先生成参数
	  // 再生成函数调用指令
	  auto ident = dynamic_cast<IdentifierAst *>(unaryExprAst->unaryOp.get());
	  auto item = globalSymbolTable->get_symbol(ident->name);
	  assert(item);
	  auto func_info = (FuncInfo *)item->ptr;
	  Instruction instruction = {
		  .instructionType = InstructionType::Call,
		  .name = ident->name,
	  };
	  // 检查参数是否为空
	  if (unaryExprAst->unaryExpr) {
		unaryExprAst->unaryExpr->accept(this);
		// 获取参数
		for (auto &fp : func_param) {
		  instruction.extra.emplace_back(fp);
		}
		func_param.clear();
	  }
	  if (func_info->ret_type != DataType::kVoid) {
		// 如果返回值不为空
		instruction.m_number = number_record++;
	  } else {
		instruction.m_number = -1;//标志返回值为空
	  }
	  //插入函数调用
	  auto &block = function.blocks.back();
	  block.instructions.emplace_back(instruction);
	}
  }
}

void IRGeneratorVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_list_ast) {
  std::stack<std::shared_ptr<Ast>> list;
  while (func_r_param_list_ast) {
	list.push(func_r_param_list_ast->expr);
	func_r_param_list_ast = dynamic_cast<FuncRParamListAst *>((func_r_param_list_ast->funcRParamListAst).get());
  }
  while (!list.empty()) {
	auto top = list.top();
	list.pop();
	auto expr = dynamic_cast<ExpAst *>(top.get());//判断是否是常数
	if (expr->have_value) {
	  // 常数直接生成一个指令
	  Instruction instruction = {
		  .operand1 = {.operand = {.number = expr->value}, .type = OperandType::kInteger},
	  };
	  func_param.emplace_back(instruction);
	} else {
	  // 变量需要去求出其值
	  expr->accept(this);
	  auto last_instruction = programIr->functions.back().blocks.back().instructions.back();
	  Instruction instruction = {
		  .operand1 = {.operand = {.number = last_instruction.m_number}, .type = OperandType::kNumber},
	  };
	  func_param.emplace_back(instruction);
	}
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
  // (Exp) | number |LValue
  // 只有当此节点为 (Exp) | Lvalue时有意义
  primaryExprAst->primaryExpr->accept(this);
}

void IRGeneratorVisitor::VisitDecl(DeclAst *decl_ast) {
  decl_ast->decl->accept(this);
}
void IRGeneratorVisitor::VisitConstDecl(ConstDeclAst *const_decl_ast) {
  // 常量定义
  const_decl_ast->const_def_list->accept(this);
}
void IRGeneratorVisitor::VisitConstDefList(ConstDefListAst *const_def_list_ast) {
  if (const_def_list_ast->const_def_list) {
	const_def_list_ast->const_def_list->accept(this);
  }
  const_def_list_ast->const_def->accept(this);
}

void IRGeneratorVisitor::VisitConstDef(ConstDefAst *const_def_ast) {
  // 常量声明,其值保证已经被求出
  // 不管是变量还是数组都不用继续遍历
  // 常量定义不用管
}

void IRGeneratorVisitor::VisitInitVal(InitValAst *init_val_ast) {
  if (init_val_ast->init_val) {
	init_val_ast->init_val->accept(this);
  }
  init_val_ast->init_val_list->accept(this);
}
void IRGeneratorVisitor::VisitInitValList(InitValListAst *init_val_list_ast) {
  auto expr = dynamic_cast<InitValAst *>(init_val_list_ast->expr_init_val.get());
  if (expr || init_val_list_ast->expr_init_val == nullptr) {
	if (expr)
	  expr->accept(this);
  } else {
	init_val_list_ast->expr_init_val->accept(this);
  }
}

void IRGeneratorVisitor::VisitLVal(LValAst *l_val_ast) {
  // 读取变量a的值  load @a
  auto ident = dynamic_cast<IdentifierAst *>(l_val_ast->l_val.get());
  auto item_level = globalSymbolTable->get_symbol_with_level(ident->name);
  //  auto item = m_symbolTable->get_symbol_with_level(ident->name);
  auto item = item_level.second;
  assert(item);
  auto symbol = makeSymbolWithLevel(ident->name, item_level.first);
  Instruction instruction = {
	  .instructionType = InstructionType::Load,
	  .dataType = item->type,
	  .operand1 = {.operand = {.symbol = symbol->c_str()}, .type = OperandType::kString},
	  .m_number = number_record++,
  };
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  block.instructions.emplace_back(instruction);
}
void IRGeneratorVisitor::VisitVarDecl(VarDeclAst *var_decl_ast) {
  var_decl_ast->var_def_list->accept(this);
}
void IRGeneratorVisitor::VisitVarDefList(VarDefListAst *var_def_list_ast) {
  if (var_def_list_ast->varDefList) {
	var_def_list_ast->varDefList->accept(this);
  }
  var_def_list_ast->varDef->accept(this);
}
void IRGeneratorVisitor::VisitVarDef(VarDefAst *var_def_ast) {
  auto ident = dynamic_cast<IdentifierAst *>(var_def_ast->ident.get());
  auto item = m_symbolTable->get_symbol(ident->name);
  Instruction instruction = {
	  .instructionType = InstructionType::GlobalAlloc,
	  .dataType = item->type,
	  .operand1 = {
		  .operand = {
			  .symbol = makeSymbolWithLevel(ident->name, globalSymbolTable->level)->c_str(),
		  },
		  .type = OperandType::kString,
	  },
  };
  auto *block = programIr->global_block;
  if (m_symbolTable->level != 0) {
	// 非全局变量
	instruction.instructionType = InstructionType::Alloc;
	auto &function = programIr->functions.back();
	block = &function.blocks.back();
  }
  // 如果有初值
  if (var_def_ast->var_expr) {
	Instruction instruction1 = {
		.instructionType = InstructionType::Store,
		.dataType = instruction.dataType,
		.operand2 = {
			.operand = {.symbol = instruction.operand1.operand.symbol},
			.type = OperandType::kString,
		},//第二个操作数是变量的符号
	};
	auto expr = dynamic_cast<InitValListAst *>(var_def_ast->var_expr.get());
	if (!expr->values.empty()) {
	  //其值已知
	  if (m_symbolTable->level != 0) {
		instruction1.operand1.operand.number = expr->values[0];
		instruction1.operand1.type = OperandType::kInteger;
	  } else {
		instruction.operand2.operand.number = expr->values[0];
		instruction.operand2.type = OperandType::kInteger;
	  }
	} else {
	  //其初始值未知
	  expr->accept(this);                                              //先产生求初始值的指令
	  instruction1.operand1.type = OperandType::kNumber;               //操作数1类型为虚拟寄存器编号
	  auto last_instruction = block->instructions.back();              //获取初始值指令的最后一条
	  instruction1.operand1.operand.number = last_instruction.m_number;//取出其虚拟寄存器编号
	}
	block->instructions.emplace_back(instruction);
	if (m_symbolTable->level != 0) {
	  // 非全局变量
	  block->instructions.emplace_back(instruction1);
	}
  } else {
	if (m_symbolTable->level == 0) {
	  // 非全局变量
	  instruction.operand2.operand.number = 0;
	  instruction.operand2.type = OperandType::kInteger;
	}
	block->instructions.emplace_back(instruction);
  }
  globalSymbolTable->add_symbol(ident->name, *item);
  // 如果没有初值
}

void IRGeneratorVisitor::VisitIfStmt(IfStmtAst *if_stmt_ast) {
  //生成if相关代码
  //如果已知条件的值，可以确定分支的代码
  auto expr = dynamic_cast<ExpAst *>(if_stmt_ast->expr.get());
  if (expr->have_value) {
	if (expr->value) {
	  if_stmt_ast->stmt->accept(this);
	} else {
	  //条件为假 并且存在if语句
	  if (if_stmt_ast->elseStmt) {
		if_stmt_ast->elseStmt->accept(this);
	  }
	}
  } else {
	//无法判断条件的真假值
	if_stmt_ast->expr->accept(this);
	//记住当前这个block
	auto &function = programIr->functions.back();
	int index = function.blocks.size() - 1;
	//创建一个分支
	function.blocks.emplace_back(label_record++);
	auto block_if_first_index = function.blocks.size() - 1;//返填
	if_stmt_ast->stmt->accept(this);
	int block_if_last_index = function.blocks.size() - 1;// if块内的最后一个block

	//在第一个分支添加的最后一个指令是无条件跳转指令 jmp
	if (if_stmt_ast->elseStmt) {
	  //存在else
	  function.blocks.emplace_back(label_record++);
	  auto block_else_first_index = function.blocks.size() - 1;//返填
	  if_stmt_ast->elseStmt->accept(this);
	  int block_else_last_index = function.blocks.size() - 1;//else 块内的最后一个block

	  // 创建一个跳转指令
	  auto instruction = make_jump(label_record);//跳转到if else 结束后的位置

	  auto &block_if = function.blocks.at(block_if_first_index);
	  auto &block_else_if = function.blocks.at(block_else_first_index);

	  auto &last_if_block = function.blocks.at(block_if_last_index);
	  auto &last_else_block = function.blocks.at(block_else_last_index);

	  last_if_block.instructions.emplace_back(instruction);
	  last_else_block.instructions.emplace_back(instruction);
	  // 创建一个br指令
	  auto &block_condition = function.blocks.at(index);
	  auto &last_instruction = block_condition.instructions.at(block_condition.instructions.size() - 1);//获取条件表达式的最后一条指令编码
	  instruction = make_branch(last_instruction.m_number, block_if.blkId, block_else_if.blkId);
	  block_condition.instructions.emplace_back(instruction);
	} else {
	  // 不存在else分支
	  // 创建一个jmp跳转指令
	  auto instruction = make_jump(label_record);
	  auto &block_if = function.blocks.at(block_if_first_index);

	  auto &last_if_block = function.blocks.at(block_if_last_index);
	  last_if_block.instructions.emplace_back(instruction);

	  auto &block_condition = function.blocks.at(index);
	  auto &last_instruction = block_condition.instructions.at(block_condition.instructions.size() - 1);//获取条件表达式的最后一条指令编码
	  instruction = make_branch(last_instruction.m_number, block_if.blkId, label_record);
	  block_condition.instructions.emplace_back(instruction);
	}
	function.blocks.emplace_back(label_record++);
  }
}
void IRGeneratorVisitor::VisitWhileStmt(WhileStmtAst *while_stmt_ast) {
  // while语句翻译
  // 如果条件的值是已知且为0，则直接跳出循环
  // 否则
  // 在当前块内加入一条jmp指令
  // 在while语句块内加入一条br指令
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  auto set_break = [&](int next_label) {
	if (break_instruction.empty()) return;
	for (auto &break_index : break_instruction) {
	  function.blocks[break_index.first].instructions[break_index.second].operand1.operand.number = next_label;
	}
	break_instruction.clear();
  };

  Instruction instruction = make_jump(label_record);
  block.instructions.emplace_back(instruction);
  //新建一个block
  function.blocks.emplace_back(label_record++);
  auto block_while_first_index = function.blocks.size() - 1;//返填
  while_begin_label.push(block_while_first_index);          // -----
  auto expr = dynamic_cast<ExpAst *>(while_stmt_ast->expr.get());
  if (expr->have_value) {
	if (expr->value <= 0) return;
	else {
	  //死循环
	  while_stmt_ast->stmt->accept(this);
	  // while 语句块内的最后一个block
	  auto &block_while_last = function.blocks.back();
	  // 创建一个跳转指令 ,跳转到while 第一个block
	  auto &block_while_condition = function.blocks.at(block_while_first_index);
	  instruction = make_jump(block_while_condition.blkId);
	  block_while_last.instructions.emplace_back(instruction);
	  set_break(label_record);
	}
  } else {
	expr->accept(this);                                     //条件的中间代码生成
	auto blk_condition_index = function.blocks.size() - 1;  //条件中间代码的block索引
	function.blocks.emplace_back(label_record++);           // 创建一个block 用于while块内代码生成
	auto blk_while_first_index = function.blocks.size() - 1;//while块内的第一个block索引
	while_stmt_ast->stmt->accept(this);                     //while块内代码生成
	auto &blk_while_last = function.blocks.back();          //while块内的最后一个block索引
	auto &blk_condition = function.blocks.at(blk_condition_index);
	// 创建jump指令
	auto instruction1 = make_jump(blk_condition.blkId);
	blk_while_last.instructions.emplace_back(instruction1);
	// 创建br指令
	// 先获取条件表达式的最后一条指令，在获取while块内的第一个block
	Instruction last_instruction = blk_condition.instructions.back();
	auto &blk_while_first = function.blocks.at(blk_while_first_index);
	auto instruction_br = make_branch(last_instruction.m_number, blk_while_first.blkId, label_record);
	blk_condition.instructions.emplace_back(instruction_br);
	set_break(label_record);
  }
  while_begin_label.pop();// -----
  function.blocks.emplace_back(label_record++);
}
void IRGeneratorVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {}
void IRGeneratorVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {}

void IRGeneratorVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
}

void IRGeneratorVisitor::VisitNumberAst(NumberAst *numberAst) {}
void IRGeneratorVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {}

IRGeneratorVisitor::IRGeneratorVisitor(SymbolTable *symbolTable) {
  m_symbolTable = symbolTable;
  globalSymbolTable = new SymbolTable;
}
std::string *IRGeneratorVisitor::makeSymbolWithLevel(const char *name, int level) {
  // 根据符号和层级生成一个新的符号
  std::string t = std::string(name) + "_" + std::to_string(level);
  std::string *s = new std::string(t);
  return s;
}
IRGeneratorVisitor::~IRGeneratorVisitor() {
  delete globalSymbolTable;
}
Instruction IRGeneratorVisitor::make_jump(int label) {
  Instruction instruction = {
	  .instructionType = InstructionType::Jump,
	  .operand1 = {
		  .operand = {.number = label},
		  .type = OperandType::kLabel,
	  },
  };
  return instruction;
}
Instruction IRGeneratorVisitor::make_branch(int condition, int label1, int label2) {
  // 创建br指令
  Instruction instruction = {
	  .instructionType = InstructionType::Branch,
	  .operand1 = {
		  .operand = {.number = condition},
		  .type = OperandType::kNumber,
	  },
	  .operand2 = {
		  .operand = {
			  .number = label1,
		  },
		  .type = OperandType::kLabel,
	  },
	  .operand3 = {
		  .operand = {
			  .number = label2,
		  },
		  .type = OperandType::kLabel,
	  },
  };
  return instruction;
}
