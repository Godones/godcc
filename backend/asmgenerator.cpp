//
// Created by linfeng on 2022/6/26.
//

#include "asmgenerator.h"
AsmGenerator::AsmGenerator(const char *filename) {
  out.open(filename);
  if (!out.is_open()) {
	std::cout << "file" << filename << "can't open\n";
	exit(-1);
  }
}

void AsmGenerator::genRet(Instruction *instruction) {
  //生成return的目标代码
  if (instruction->operand1.type==OperandType::kInteger) {
	out << "\tli $v0, " << instruction->operand1.operand.number << "\n";
  } else if (instruction->operand1.type==OperandType::kNumber) {
	out << "\tmove $v0, "<< "$" << registerAllocator.getReg(instruction->operand1.operand.number) << "\n";
  }
  genFunctionEnd();
  out << "\tjr $ra\n";
  out << "\tnop\n";
}

void AsmGenerator::genProgram(Program *program ){
  // todo!生成全局变量
  out << "\t.text\n";
  out << "init:\n";
  out << "\tjal "<< "main"<< "\n";
  out << "\tli $v0, 10\n";
  out << "\tsyscall\n";
  genMars();
}
void AsmGenerator::genFunction(Function *function) {
  out<< function->name << ":\n";
  currentFunction = function->name;
  initFrameStack(function);
}
void AsmGenerator::genFunctionEnd() {
  // 当遇到return 指令时需要恢复寄存器相关内容
  out << "\tmove $sp, $fp\n";
  out << "\tlw $ra, " << frameStack.get_offset("$ra") << "($sp)\n";
  out << "\tlw $fp, " << frameStack.get_offset("$fp") << "($sp)\n";
  out << "\taddi $sp, $sp, " << frameStack.get_size() << "\n";
}
void AsmGenerator::initFrameStack(Function *function) {
  // todo!初始化栈帧结构
  // 遍历所有基本块中的指令和函数的参数，计算需要的栈空间
  for (const auto& param : function->params) {
	assert(param.instructionType == InstructionType::FuncArgRef);
	frameStack.push(param.name.data(), 4);
  }
  frameStack.push("$fp", 4);
  frameStack.push("$ra", 4);
  for(int i=8;i<=15;i++){
	// 保留临时寄存器的区域
	frameStack.push("$" + std::to_string(i), 4);
  }
  frameStack.push("$24", 4);
  frameStack.push("$25", 4);
  frameStack.push("$3",4);
  frameStack.push("$6",4);
  frameStack.push("$7",4);
  for (const auto& block : function->blocks) {
	for (const auto& instruction : block.instructions) {
	  if (instruction.instructionType == InstructionType::Alloc) {
		// alloc 可能是数组，也可能是变量
		if(!instruction.array_dim.empty()){
		  // 数组
		  int size = 1;
		  for (const auto& dim : instruction.array_dim) {
			size *= dim;
		  }
		  frameStack.push(instruction.operand1.operand.symbol, size*4);
		} else {
		  frameStack.push(instruction.operand1.operand.symbol, 4);
		}
	  }
	}
  }
  // 初始化栈帧结构
  out << "\taddi $sp, $sp, -" << frameStack.get_size() << "\n";
  // 保存参数
  int t = 0;
  for (const auto& param : function->params) {
	out << "\tsw " << "$a" << t << ", " << t*4 <<"($sp)\n";
	t++;
  }
  // 保存fp指针
  out << "\tsw $fp, " << t*4 <<"($sp)\n";
  t++;
  // 保存ra指针
  out << "\tsw $ra, " << t*4 <<"($sp)\n";
  t++;
  out << "\tmove $fp, $sp\n";
}

void AsmGenerator::genBinary(Instruction *instruction) {
  // 所有的二元运算都需要判断两个操作数类型
  int reg[3]={-1,-1,-1};
  reg[0] = registerAllocator.getReg(instruction->m_number);
  auto sameDeal = [&]()->int {
	if (instruction->operand1.type==OperandType::kNumber&&instruction->operand2.type==OperandType::kNumber) {
	  //两个寄存器数
	  reg[1]=registerAllocator.getReg(instruction->operand1.operand.number);
	  reg[2]=registerAllocator.getReg(instruction->operand2.operand.number);
	  return 0;
	}
	assert(instruction->operand1.type==OperandType::kNumber||instruction->operand2.type==OperandType::kNumber);
	if(instruction->operand1.type==OperandType::kInteger) {
	  //add 4, %x,左边为立即数
	  reg[1] = registerAllocator.getReg(instruction->operand2.operand.number);
	  return -1;
	}
	if(instruction->operand2.type==OperandType::kInteger) {
	  //add %x, 4,右边为立即数
	  reg[1] = registerAllocator.getReg(instruction->operand1.operand.number);
	  return 1;
	}
  };
  auto samePre = [&](const char *ins) {
  	out <<	"\t" << ins << " ";
  };
  auto sameMid = [&](){
	out << '$' <<reg[0] << ", " << '$' << reg[1] << ", ";
  };
  auto sameBackInt = [&](int number){
	out << number << "\n";
  };
  auto sameBackReg = [&](int reg){
	out << '$' << reg << "\n";
  };

  int pre = sameDeal();
  // slt /slti单独处理
  if (instruction->binaryOp==BinaryOp::Lt) {
	if (pre == 0) {
	  samePre("slt");sameMid();sameBackReg(reg[2]);
	  registerAllocator.freeReg(instruction->operand1.operand.number);
	  registerAllocator.freeReg(instruction->operand2.operand.number);
	} else if (pre == -1) {
	  samePre("slti");sameMid();sameBackInt(instruction->operand1.operand.number);
	  registerAllocator.freeReg(instruction->operand2.operand.number);
	} else {
	  samePre("slti");sameMid();sameBackInt(instruction->operand2.operand.number);
	  registerAllocator.freeReg(instruction->operand1.operand.number);
	}
	return ;
  }
  if(instruction->binaryOp==BinaryOp::Sub) {
	if (pre == 0) {
	  samePre("sub");sameMid();sameBackReg(reg[2]);
	  registerAllocator.freeReg(instruction->operand2.operand.number); //释放掉右边的寄存器
	  registerAllocator.freeReg(instruction->operand1.operand.number); //释放掉左边的寄存器
	} else if (pre == -1) {
	  //sub 4, %x,左边为立即数
	  //需要申请一个临时寄存器
	  int reg_tmp = registerAllocator.getTempReg();
	  reg[1] = reg_tmp;
	  reg[2] = registerAllocator.getReg(instruction->operand2.operand.number);
	  assert(reg[0]!=reg[1]&&reg[0]!=reg[2]&&reg[1]!=reg[2]);
	  out << "\tli $" << reg_tmp << ", " << instruction->operand1.operand.number << "\n";
	  samePre("sub");sameMid();sameBackReg(reg[2]);
	  registerAllocator.freeTempReg(reg_tmp);
	  registerAllocator.freeReg(instruction->operand2.operand.number); //释放掉右边的寄存器
	} else{
	  //sub %x, 4,右边为立即数
	  samePre("sub");sameMid();sameBackInt(instruction->operand2.operand.number);
	  registerAllocator.freeReg(instruction->operand1.operand.number); //释放掉左边的寄存器
	}
	return ;
  }


  switch (instruction->binaryOp) {
	case BinaryOp::Add:{
	  // 二元运算中包含了一元运算，对于一元运算来说，第一个数为0，第二个为寄存器数
	  // 而真正的二元运算第一个和第二个操作数可能为寄存器数或者立即数，但不可能同时为立即数
	  samePre("add");break ;
	}
	case BinaryOp::Mul: {
	  samePre("mul");break;
	}
	case BinaryOp::Div: {
	  samePre("div");break;
	}
	case BinaryOp::Mod: {
	  samePre("rem");break;
	}
	case BinaryOp::And: {
	  samePre("and");break;
	}
	case BinaryOp::Or: {
	  samePre("or");break;
	}
	case BinaryOp::Ne: {
	  samePre("sne");break;
	}
	case BinaryOp::Le: {
	  samePre("sle");break;
	}
	case BinaryOp::Ge: {
	  samePre("sge");break;
	}
	case BinaryOp::Gt: {
	  samePre("sgt");break;
	}
	case BinaryOp::Eq: {
	  samePre("seq");break;
	}
	default: break;
  }
  sameMid();
  if (pre==0) {
	sameBackReg(reg[2]);
	registerAllocator.freeReg(instruction->operand2.operand.number);
	registerAllocator.freeReg(instruction->operand1.operand.number);
  } else if (pre==-1) {
	sameBackInt(instruction->operand1.operand.number);
	registerAllocator.freeReg(instruction->operand2.operand.number);
  } else {
	sameBackInt(instruction->operand2.operand.number);
	registerAllocator.freeReg(instruction->operand1.operand.number);
  }

}
void AsmGenerator::genAlloc(Instruction *instruction) {
  // 这里主要针对数组的初始化操作，在构建栈帧的过程中，所有的非数组变量已经申请了空间
  // 而非数组变量有单独的初始化操作store,但是数组的并没有
  // 因此需要对数组进行单独的处理
  // todo! 处理数组的alloc
}
void AsmGenerator::genStore(Instruction *instruction) {
  // 写回内存
  // 第一个操作数可能是立即数/寄存器数
  // 第二个操作数可能是符号/寄存器地址(数组)
  int reg = -1;
  bool imm = false;
  if (instruction->operand1.type==OperandType::kInteger){
	reg = registerAllocator.getTempReg();
	out << "\tli " << "$" << reg << ", " << instruction->operand1.operand.number << "\n";
	imm = true;
  } else {
	reg = registerAllocator.getReg(instruction->operand1.operand.number);
  }

  if (instruction->operand2.type==OperandType::kString){
	// 从栈帧中获取偏移量
	// 全局变量需要从另一个表中获得地址
	bool global = frameStack.has_name(instruction->operand2.operand.symbol);
	if (!global){
	  //全局变量,加载符号地址
//	  INFO("store global");
	  out << "\tsw " << "$" << reg << ", " << instruction->operand2.operand.symbol <<"\n";
	}else {
	  int offset = frameStack.get_offset(instruction->operand2.operand.symbol);
	  out << "\tsw " << "$" << reg << ", "<<offset << "($fp)\n";
	}
  } else {
	int second_reg = registerAllocator.getReg(instruction->operand2.operand.number);
	out << "\tsw " << "$" << reg << ", "<<"($" << second_reg << ")\n";
	registerAllocator.freeReg(instruction->operand2.operand.number);
  }
  if (imm) {
	registerAllocator.freeTempReg(reg);
  }else {
	registerAllocator.freeReg(instruction->operand1.operand.number);
  }

}
void AsmGenerator::genLoad(Instruction *instruction) {
  // 从内存中加载数
  // 第一个操作数可能是符号/寄存器
  int reg = registerAllocator.getReg(instruction->m_number);
  if(instruction->operand1.type==OperandType::kString){
	bool global = frameStack.has_name(instruction->operand1.operand.symbol);
	if (!global){
//	  INFO("load global var");
	  //全局变量,加载符号地址
	  out << "\tlw "
		  << "$" << reg << ", "
		  << instruction->operand1.operand.symbol << "\n";
	}else{
	  int offset = frameStack.get_offset(instruction->operand1.operand.symbol);
	  out << "\tlw " << "$" << reg << ", "<< offset << "($fp)\n";
	}
  }else{
	int address = registerAllocator.getReg(instruction->operand1.operand.number);
	out << "\tlw " << "$" << reg << ", "<<"($" << address << ")\n";
	registerAllocator.freeReg(instruction->operand1.operand.number);
  }
}
void AsmGenerator::reset() {
  // 重置栈帧管理器和寄存器管理器
  registerAllocator = RegisterAllocator();
  frameStack = FrameStack();
}
void AsmGenerator::genCall(Instruction *instruction) {
  // 生成函数调用指令
  // 将各个参数以此放入$a0-$a3中
  // 如果有返回值，则将返回值放在一个寄存器中
  //先保存已经被使用的临时寄存器
  auto usedReg = registerAllocator.getUsedReg();
  for (auto &x :usedReg){
	out << "\tsw " << "$"<< x <<", " << frameStack.get_offset("$"+std::to_string(x)) << "($fp)\n";
  }
  int param = 0;
  for (auto &fp : instruction->extra) {
	if (fp.operand1.type == OperandType::kInteger) {
	  out << "\tli "
		  << "$a" << param << ", " << fp.operand1.operand.number << "\n";
	} else if (fp.operand1.type == OperandType::kNumber) {
	  out << "\tmove "
		  << "$a" << param << ", "
		  << "$" << registerAllocator.getReg(fp.operand1.operand.number) << "\n";
	} else if (fp.operand1.type == OperandType::kString) {
	  // 将字符串的地址放入$a0中
	  out << "\tla " << "$a" << param << ", " << fp.operand1.operand.symbol << "\n";
	}
	param++;
  }
  out << "\tjal " << instruction->name << "\n";
  if (instruction->m_number != -1) {
	int ans_reg = registerAllocator.getReg(instruction->m_number);
	out << "\tmove " << "$" << ans_reg << ", $v0\n";
  }
  for (auto &x :usedReg){
	out << "\tlw " << "$"<< x <<", " << frameStack.get_offset("$"+std::to_string(x)) << "($fp)\n";
  }
  out << "\tnop\n";
}
void AsmGenerator::genMars() {
  // 生成mars系统调用函数
  out << "Mars_PrintInt:\n"
		 "\tli $v0, 1\n"
		 "\tsyscall\n"
		 "\tjr $ra\n";

  out << "Mars_GetInt:\n"
		 "\tli $v0, 5\n"
		 "\tsyscall\n"
		 "\tjr $ra\n";

  out << "Mars_PrintStr:\n"
		 "\tli $v0, 4\n"
		 "\tsyscall\n"
		 "\tjr $ra\n";
}

void AsmGenerator::genBaseBlock(BaseBlock *baseBlock) {
  out << currentFunction << baseBlock->blkId << ":\n";
}
void AsmGenerator::genJump(Instruction *instruction) {
  // 无条件跳转
  out << "\tj " << currentFunction <<instruction->operand1.operand.number << "\n";
}
void AsmGenerator::genBranch(Instruction *instruction) {
  // 检查条件是否 > 0
  // 如果是，则跳转到第一个目标块
  // 如果不是，则跳转到第二个目标块
  int reg = registerAllocator.getReg(instruction->operand1.operand.number);
  out << "\tbgtz " << "$" << reg << ", " << currentFunction << instruction->operand2.operand.number << "\n";
  out << "\tj " << currentFunction <<instruction->operand3.operand.number << "\n";
  registerAllocator.freeReg(instruction->operand1.operand.number);
}
void AsmGenerator::genGetElementPtr(Instruction *instruction) {
  // 访问数组的目标代码
  // 第一个操作数可能为符号/寄存器(存放地址)
  // 第二个操作数可能为立即数/寄存器(存放下标)
  // 第三个操作数是立即数
  int target_reg = registerAllocator.getReg(instruction->m_number);
  if (instruction->operand1.type == OperandType::kString) {
	bool global = frameStack.has_name(instruction->operand1.operand.symbol);
	if (!global){
	  //全局变量,加载符号地址
//	  DEBUG("global array variable");
	  out << "\tla "
		  << "$" << target_reg << ", " << instruction->operand1.operand.symbol << "\n";
	}else {
	  int offset = frameStack.get_offset(instruction->operand1.operand.symbol);
	  // 获取到偏移地址
	  out << "\tadd "
		  << "$" << target_reg << ", "
		  << "$zero"
		  << ", "
		  << "$fp"
		  << "\n";//栈基址
	  out << "\tadd "
		  << "$" << target_reg << ", "
		  << "$" << target_reg << ", " << offset << "\n";// +数组偏移地址
	}
  } else {
	int reg = registerAllocator.getReg(instruction->operand1.operand.number);
	out << "\tmove " << "$" << target_reg << ", $" << reg << "\n";
	registerAllocator.freeReg(instruction->operand1.operand.number);
  }
  if (instruction->operand2.type == OperandType::kInteger) {
	int index = instruction->operand2.operand.number;
	// 将下标与第三个操作数相乘
	int temp_reg = registerAllocator.getTempReg();
	out << "\tli " << "$" << temp_reg << ", " << index << "\n";
	out << "\tmul " << "$" << temp_reg << ", " << "$" << temp_reg << "," << instruction->operand3.operand.number << "\n";
	out << "\tmul " << "$" << temp_reg << ", " << "$" << temp_reg << ",4\n";
	out << "\tadd " << "$" << target_reg << ", " << "$" << target_reg << ", " << "$" << temp_reg << "\n";
	registerAllocator.freeTempReg(temp_reg);
  } else {
	int reg = registerAllocator.getReg(instruction->operand2.operand.number);
	out << "\tmul " << "$" << reg << ", " << "$" << reg << "," << instruction->operand3.operand.number << "\n";
	out << "\tmul " << "$" << reg << ", " << "$" << reg << ",4\n";
	out << "\tadd " << "$" << target_reg << ", " << "$" << target_reg << ", $" << reg << "\n";
	registerAllocator.freeReg(instruction->operand2.operand.number);//释放这个不用的寄存器
  }
}
void AsmGenerator::genGlobalString(Instruction *pInstruction) {
  // 构建数据段的字符串
  out << pInstruction->operand1.operand.symbol << ": " <<".asciiz " << pInstruction->operand2.operand.symbol << "\n";
}
void AsmGenerator::genGloblData() {
  // 构建数据段的数据
  out << "\t.data\n";
}
void AsmGenerator::genGlobalAlloc(Instruction *pInstruction) {
  // 构建数据段的数据
  // 需要判断是数组还是变量
  auto next = pInstruction->next;
  if (!pInstruction->array_dim.empty()) {
	// 数组变量
	int size = 1;
	for (int i : pInstruction->array_dim) {
	  size *= i;
	}
	out << pInstruction->operand1.operand.symbol << ": ";
	if (next->array_dim.size()==1&&next->array_dim[0]==0) {
	  // 数组变量的初始化
	  out << ".space " << size * 4 << "\n";
	}else{
	  out << ".word ";
	  for(int i=0;i<size-1;i++) {
		out << next->array_dim[i] << ", ";
	  }
	  out << next->array_dim[size-1] << "\n";
	  if (next->array_dim.size()!=size){
		out << ".space " << (size-next->array_dim.size())*4 << "\n";
	  }
	}
  } else {
	// 变量
	out << pInstruction->operand1.operand.symbol << ": ";
	out << ".word " << next->array_dim[0] << "\n";
  }
}
