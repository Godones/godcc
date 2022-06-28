//
// Created by linfeng on 2022/4/8.
//

#include "ast_to_ir.h"

// 生成程序主体
void IRGeneratorVisitor::VisitTranslationUnit(TranslationUnitAst *ast) {
  add_library_function();
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
  label_record = 0;
  number_record = 0;
  auto ident = dynamic_cast<IdentifierAst *>(funcDefAst->ident.get());
  //在m_symbolTable中找到函数定义的条目
  auto item = m_symbolTable->get_symbol(ident->name);
  //拷贝到中间代码的符号表中
  globalSymbolTable->add_symbol(ident->name, *item);
  Function function;
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
	instruction.name = makeSymbolWithLevel(param.name.c_str(),m_symbolTable->level)->c_str();
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
  if (blockAst->block_item_list) {
	blockAst->block_item_list->accept(this);
  }
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
		  f_set(OperandType::kInteger, getInt(expr->value));
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
	  auto item_with_level = globalSymbolTable->get_symbol_with_level(ident->name);
	  auto item = item_with_level.second;
	  auto expr = dynamic_cast<ExpAst *>(stmtAst->expr.get());
	  auto symbol= makeSymbolWithLevel(ident->name, item_with_level.first);

	  Instruction instruction = {
		  .instructionType = InstructionType::Store,
		  .dataType = item->type,
		  .operand2 = {.operand = {.symbol = symbol->c_str()},.type=OperandType::kString},
	  };
	  if (l_val->array_expr_list){
		//处理数组
		array_name = *symbol;
		pre_array_name = ident->name;
		l_val->array_expr_list->accept(this);
		instruction.operand2.type = OperandType::kNumber;
		instruction.operand2.operand.number = function.blocks.back().instructions.back().m_number; //加载数组的getelementptr指令的标号
	  }

	  if (expr->have_value) {
		// 如果是数字，则直接生成一个指令
		instruction.operand1.type = OperandType::kInteger;
		instruction.operand1.operand.number = getInt(expr->value);
	  } else {
		stmtAst->expr->accept(this);
		// 获取上一条四元式的标号
		auto last_instruction = block.instructions.back();
		instruction.operand1.type = OperandType::kNumber;
		instruction.operand1.operand.number = last_instruction.m_number;
	  }
	  block.instructions.emplace_back(instruction);
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
	case StmtType::kFor:{
	  // for 语句
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
	  set_operand1(OperandType::kInteger, getInt(left_expr->value));
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
		set_operand2(OperandType::kInteger, getInt(right_expr->value));
	  } else {
		right_expr->accept(this);
		auto last_instruction = programIr->functions.back().blocks.back().instructions.back();
		set_operand2(OperandType::kNumber, last_instruction.m_number);
	  }
	} else {
	  auto right_expr = dynamic_cast<UnaryExprAst *>(binary_expr_ast->right.get());
	  if (right_expr->have_value) {
		set_operand2(OperandType::kInteger, getInt(right_expr->value));
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
	case UnaryType::kPostfix: {
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
		  .operand2 = {.operand = {.number = last_instruction.m_number}, .type = OperandType::kNumber},
		  .m_number = number_record++,
	  };
	  block.instructions.emplace_back(instruction);
	  unaryExprAst->unaryOp->accept(this);// 设置二元符号
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
	  break ;
	}
  }
}

void IRGeneratorVisitor::VisitPostfixExprAst(PostfixExprAst *postfixExprAst) {
  // 处理 a++/a--/primaryExpr 的情况
  postfixExprAst->postfixExpr->accept(this);
  if (postfixExprAst->postfixType == PostfixType::kPrimary) {
	return;
  }
  auto &block = programIr->functions.back().blocks.back();
  auto last_instruction = block.instructions.back();
  Instruction instruction = {
	  .instructionType = InstructionType::Binary,
	  .operand1 = {.operand = {.number = 1}, .type = OperandType::kInteger},
	  .operand2 = {.operand = {.number = last_instruction.m_number}, .type = OperandType::kNumber},
	  .m_number = number_record++,
  };
  switch (postfixExprAst->postfixType) {
	case PostfixType::kBDec: {
	  instruction.binaryOp = BinaryOp::Sub;
	  auto temp = instruction.operand1;
	  instruction.operand1 = instruction.operand2;
	  instruction.operand2 = temp;
	  break;
	}
	case PostfixType::kBInc: {
	  instruction.binaryOp = BinaryOp::Add;
	  break;
	}
	default: break;
  }
  block.instructions.emplace_back(instruction);
  Instruction instruction1 = {
	  .instructionType= InstructionType::Store,
	  .dataType = last_instruction.dataType,
	  .operand1 = {.operand = {.number = instruction.m_number}, .type = OperandType::kNumber},
	  .operand2 = {.operand = {.symbol = last_instruction.operand1.operand.symbol}, .type = OperandType::kString},
  };
  //额外的一条指令
  Instruction instruction2 = {
	  .instructionType = InstructionType::Move,
	  .operand1 = {.operand = {.number = last_instruction.m_number}, .type = OperandType::kNumber},
	  .operand2 = {.operand = {.number = last_instruction.m_number}, .type = OperandType::kNumber},
	  .m_number = last_instruction.m_number,
  };
  block.instructions.emplace_back(instruction1);
  block.instructions.emplace_back(instruction2);
}



void IRGeneratorVisitor::VisitFuncRParamListAst(FuncRParamListAst *func_r_param_list_ast) {
  //todo!(函数调用，这里处理字符串的出现)
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
		  .operand1 = {.operand = {.number = 0}, .type = OperandType::kInteger},
	  };
	  if (expr->data_type==DataType::kString){
		//字符串需要放到全局区域
		auto str = new std::string (getString(expr->value));
		Instruction instruction1 = {
			.instructionType = InstructionType::GlobalString,
			.operand1 = {.operand = {.symbol = makeSymbolWithLevel("str",str_record++)->c_str()}, .type = OperandType::kString},
			.operand2 = {
				.operand = {.symbol = str->data()},
				.type = OperandType::kString},
		};
		// 将数组放到全局区域中
		programIr->global_block->instructions.emplace_back(instruction1);
		instruction.operand1.operand.symbol = instruction1.operand1.operand.symbol;
		instruction.operand1.type = OperandType::kString;
	  }else{
		instruction.operand1.operand.number = getInt(expr->value);
	  }
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
  }else if (op == "--") {
	instruction.binaryOp = BinaryOp::Sub;
	Operand temp = instruction.operand2;
	instruction.operand2 = {.operand = {.number = 1}, .type = OperandType::kInteger};
	instruction.operand1 = temp;
  } else if (op == "++") {
	instruction.binaryOp = BinaryOp::Add;
	instruction.operand1.operand.number = 1;
  }else {
	// 引发错误
	exit(-1);
  }
  if (op=="--"||op=="++") {
	auto last_instruction = block.instructions[block.instructions.size() - 2];
	Instruction instruction1 = {
		.instructionType= InstructionType::Store,
		.dataType = last_instruction.dataType,
		.operand1 = {.operand = {.number = instruction.m_number}, .type = OperandType::kNumber},
		.operand2 = {.operand = {.symbol = last_instruction.operand1.operand.symbol}, .type = OperandType::kString},

	};
	//额外的一条指令
	Instruction instruction2 = {
		.instructionType = InstructionType::Move,
		.operand1 = {.operand = {.number = instruction.m_number}, .type = OperandType::kNumber},
		.operand2 = {.operand = {.number = instruction.m_number}, .type = OperandType::kNumber},
		.m_number = instruction.m_number,
	};
	block.instructions.emplace_back(instruction1);
	block.instructions.emplace_back(instruction2);
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
  auto ident = dynamic_cast<IdentifierAst *>(const_def_ast->ident.get());
  auto item = m_symbolTable->get_symbol(ident->name);
  assert(item);
  globalSymbolTable->add_symbol(ident->name,*item);
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
  // 读取变量a的值  load @a /load %x
  auto &function = programIr->functions.back();
  auto ident = dynamic_cast<IdentifierAst *>(l_val_ast->l_val.get());
  auto item_val = globalSymbolTable->get_symbol_with_level(ident->name);
  //  auto item = m_symbolTable->get_symbol_with_level(ident->name);
  assert(item_val.second);
  auto symbol = makeSymbolWithLevel(ident->name, item_val.first);
  Instruction instruction = {
	  .instructionType = InstructionType::Load,
	  .dataType = item_val.second->type,
	  .operand1 = {.operand = {.symbol = symbol->c_str()}, .type = OperandType::kString},
  };

  if (l_val_ast->array_expr_list){
	//处理数组相关内容
	array_name = symbol->c_str();
	pre_array_name = ident->name;
//	DEBUG("Lval_array_name:%s", array_name.c_str());
	l_val_ast->array_expr_list->accept(this);
	instruction.operand1.operand.number = function.blocks.back().instructions.back().m_number;
	instruction.operand1.type = OperandType::kNumber;
  }
  instruction.m_number = number_record++;

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
		  .operand = {.symbol = makeSymbolWithLevel(ident->name, globalSymbolTable->level)->c_str(),},
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
  // 处理数组
  bool is_array = false;
  if (var_def_ast->array_expr_list) {
	auto array_expr_list = dynamic_cast<ArrayExprListAst *>(var_def_ast->array_expr_list.get());
	array_expr_list->accept(this); // 处理数组
	instruction.array_dim = array_expr_list->array_num;// 记录数组维度
	auto array_info = (ArrayInfo*)item->ptr;
	instruction.dataType =  DataType::kInt;// 记录数组类型
	is_array = true;
  }
  Instruction instruction1 = {
	  .instructionType = InstructionType::Store,
	  .dataType = instruction.dataType,
	  .operand2 = {
		  .operand = {.symbol = instruction.operand1.operand.symbol},
		  .type = OperandType::kString,
	  },//第二个操作数是变量的符号
  };
  // 如果有初值
  if (var_def_ast->var_expr) {
	auto expr = dynamic_cast<InitValListAst *>(var_def_ast->var_expr.get());
	if (!expr->values.empty()) {
	  //其值已知
	  instruction1.array_dim = expr->values; //复用array_dim字段
	  if (is_array) {
		// 数组
		instruction1.instructionType = InstructionType::Aggregate;
	  } else {
		// 基本类型
		instruction1.operand1.type = OperandType::kInteger;
		instruction1.operand1.operand.number = expr->values.front();
	  }
	} else {
	  //其初始值未知
	  expr->accept(this);                                              //先产生求初始值的指令
	  instruction1.operand1.type = OperandType::kNumber;               //操作数1类型为虚拟寄存器编号
	  auto last_instruction = block->instructions.back();              //获取初始值指令的最后一条
	  instruction1.operand1.operand.number = last_instruction.m_number;//取出其虚拟寄存器编号
	}
	// 存入变量
	if (m_symbolTable->level == 0) {
	  instruction.next = new Instruction(instruction1);
	  block->instructions.emplace_back(instruction);
	}else{
	  if (is_array){
		instruction.next = new Instruction(instruction1);
		block->instructions.emplace_back(instruction);
	  } else {
		block->instructions.emplace_back(instruction);
		block->instructions.emplace_back(instruction1);
	  }
	}// 如果是全局变量，则第二条指令存放于next
  } else {
	// 没有初值,全局变量默认初始化为0，局部变量不用管
	if(m_symbolTable->level==0){
	  instruction1.array_dim.emplace_back(0);
	  instruction.next = new Instruction(instruction1);
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
	if (getInt(expr->value)) {
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
  // 如果条件的值是已知且为0，则直接跳出循环 否则
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
	if (getInt(expr->value) <= 0) return;
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
void IRGeneratorVisitor::VisitForStmt(ForStmtAst *forStmtAst) {
  // 生成for循环的中间代码
  // for(expr1;cond;expr3) stmt
  // 需要四部分基本块，第一部分基本块的最后一条语句跳转到第二部分基本块的开头
  // 第二部分基本块的最后进行分支跳转到第三部分开头或者第五部分基本块，
  // 第三部分无条件跳转到第四部分，第四部分无条件跳转到第二部分
  auto &function = programIr->functions.back();
  auto set_break = [&](int next_label) {
	if (break_instruction.empty()) return;
	for (auto &break_index : break_instruction) {
	  function.blocks[break_index.first].instructions[break_index.second].operand1.operand.number = next_label;
	}
	break_instruction.clear();
  };
  m_symbolTable = m_symbolTable->enter_scope(); //进入for()作用域
  globalSymbolTable = globalSymbolTable->new_scope();
  forStmtAst->expr1->accept(this); //生成expr1的中间代码
  Instruction instruction = make_jump(label_record); //jump
  function.blocks.back().instructions.emplace_back(instruction);
  //新建一个block，第二部分基本块
  function.blocks.emplace_back(label_record++);
  // 生成条件表达式的中间代码,在完成第三部分和第四部分基本块后，需要回到这里填入br 语句
  auto for_condition_first_index = function.blocks.size() - 1;//第二部分基本块开始索引
  forStmtAst->expr2->accept(this);
  auto for_condition_last_index = function.blocks.size() - 1;//第二部分基本块的最后一个索引
  // 语句块生成
  function.blocks.emplace_back(label_record++);
  auto for_stmt_first_index = function.blocks.size()-1;
  forStmtAst->stmt->accept(this);
  function.blocks.back().instructions.emplace_back(make_jump(label_record));

  // 第三个表达式生成
  function.blocks.emplace_back(label_record++);
  auto for_expr3_first_index = function.blocks.size()-1;
  if (forStmtAst->expr3){forStmtAst->expr3->accept(this);};
  auto label = function.blocks.at(for_condition_first_index).blkId; //label
  function.blocks.back().instructions.emplace_back(make_jump(label));

  // 开始返填条件部分的br语句
  label = function.blocks.at(for_stmt_first_index).blkId;//label
  auto &block = function.blocks.at(for_condition_last_index);
  if (block.instructions.size()==0){//说明此时条件为空，则直接jump到下一个基本块
	block.instructions.emplace_back(make_jump(label));
  }else{
	auto condition_last_ins = block.instructions.back();
	block.instructions.emplace_back(make_branch(condition_last_ins.m_number,label,label_record));
  }

  set_break(label_record);
  // 开启新的block
  function.blocks.emplace_back(label_record++);
  m_symbolTable = m_symbolTable->exit_scope(); //退出for()作用域
  globalSymbolTable = globalSymbolTable->exit_scope();
}



void IRGeneratorVisitor::VisitFuncFParamListAst(FuncFParamListAst *func_f_param_list_ast) {}
void IRGeneratorVisitor::VisitFuncFParamAst(FuncFParamAst *func_f_param_ast) {}

void IRGeneratorVisitor::VisitArrayExprList(ArrayExprListAst *array_expr_list_ast) {
  // 生成数组相关的代码
  if (array_name.empty()) {
	return ;
  }
//  DEBUG("array_name:%s", array_name.c_str());
  auto &function = programIr->functions.back();
  auto &block = function.blocks.back();
  std::stack<std::shared_ptr<Ast>> list;
  auto record = array_expr_list_ast;
  while (array_expr_list_ast) {
	list.push(array_expr_list_ast->array_expr);
	array_expr_list_ast = dynamic_cast<ArrayExprListAst *>((array_expr_list_ast->array_expr_list).get());
  }
  //获取数组的信息
  auto item = globalSymbolTable->get_symbol(pre_array_name);
  assert(item->ptr);
  auto array_info = (ArrayInfo *)item->ptr;
  int size = array_info->get_size();
//  DEBUG("array_info->dim:%d size:%d", array_info->dim.size(), size);
  //语义分析中已经部分求值，这里则需要对那些没有求值的进行继续求值
  int t =0,number = 0;
  while (!list.empty()) {
	auto expr = dynamic_cast<ExpAst*>(list.top().get());
	auto symbol = new std::string (array_name);
	Instruction instruction = {
		.instructionType = InstructionType::GetElementPtr,
		.operand1 = {.operand = {.symbol = symbol->c_str()},.type = OperandType::kString},
		.operand3 = {.operand = {.number = size = (size/array_info->dim[t])},.type = OperandType::kInteger},
	};
	if (t==0){
	  instruction.operand1.operand.symbol = symbol->c_str();
	}else{
	  instruction.operand1.operand.number = number;
	  instruction.operand1.type = OperandType::kNumber;
	}
	t++;
	if (expr->have_value){
	  // %ptr = getelemptr @arr, 1(偏移)
	  instruction.operand2.operand.number = getInt(expr->value);
	  instruction.operand2.type = OperandType::kInteger;
	} else{
	  expr->accept(this);
	  // %ptr = getelemptr @arr, %0(偏移)
	  auto last_ins = block.instructions.back();
	  instruction.operand2.operand.number = last_ins.m_number;
	  instruction.operand2.type = OperandType::kNumber;
	}
	number = number_record;
	instruction.m_number = number_record++;
	block.instructions.emplace_back(instruction);
	list.pop();
  }

  array_name = "";
}
void IRGeneratorVisitor::VisitStringAst(StringAst *) {}
void IRGeneratorVisitor::VisitNumberAst(NumberAst *numberAst) {}
void IRGeneratorVisitor::VisitIdentifierAst(IdentifierAst *identifier_ast) {}

IRGeneratorVisitor::IRGeneratorVisitor(SymbolTable *symbolTable) {
  m_symbolTable = symbolTable;
  globalSymbolTable = new SymbolTable();
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
		  .operand = {.number = label1,},
		  .type = OperandType::kLabel,
	  },
	  .operand3 = {
		  .operand = {.number = label2,},
		  .type = OperandType::kLabel,
	  },
  };
  return instruction;
}
void IRGeneratorVisitor::add_library_function() {
  //将库函数加入符号表中
  //Mars_PrintStr  Mars_GetInt   Mars_PrintInt
  FuncInfo  funcInfo1 =  FuncInfo();
  SymbolInfo symbolInfo1 = SymbolInfo();
  symbolInfo1.type = DataType::kFunc;
  symbolInfo1. name= "Mars_PrintStr";
  funcInfo1.ret_type = DataType::kVoid;
  funcInfo1.params.emplace_back(SymbolInfo{.type = DataType::kString});
  symbolInfo1.ptr = new FuncInfo(funcInfo1);
  globalSymbolTable->add_symbol("Mars_PrintStr",symbolInfo1);
//  INFO("add Mars_PrintStr");

  funcInfo1.ret_type = DataType::kInt;
  funcInfo1.params.clear();
  symbolInfo1.name = "Mars_GetInt";
  symbolInfo1.ptr = new FuncInfo(funcInfo1);
  globalSymbolTable->add_symbol("Mars_GetInt",symbolInfo1);
//  INFO("add Mars_GetInt");

  funcInfo1.ret_type = DataType::kVoid;
  funcInfo1.params.emplace_back(SymbolInfo{.type = DataType::kInt});
  symbolInfo1.name = "Mars_PrintInt";
  symbolInfo1.ptr = new FuncInfo(funcInfo1);
  globalSymbolTable->add_symbol("Mars_PrintInt",symbolInfo1);
//  INFO("add Mars_PrintInt");
}

