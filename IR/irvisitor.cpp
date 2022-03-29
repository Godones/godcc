//
// Created by linfeng on 2022/3/13.
//
#include "irvisitor.h"

#include "../log/log.h"

void IrVisitorDefault::VisitProgram(Program *program) {
  for (auto &func : program->functions) {
	func.accept(this);
  }
  std::cout << "\n";
}

void IrVisitorDefault::VisitFunction(Function *function) {
  std::cout << "fun @" << function->name << ":" << toString(function->retType) << "{\n";
  for (auto &block : function->blocks) {
	block.accept(this);
  }
  std::cout << "}";
}

void IrVisitorDefault::VisitBaseBlock(BaseBlock *block) {
  std::cout << block->blockName << ":\n";
  for (auto &ins : block->instructions) {
	ins.accept(this);
  }
}

void IrVisitorDefault::VisitInstruction(Instruction *instruction) {
  // 根据指令类型进行输出
  switch (instruction->instructionType) {
	case Integer:
	  std::cout <<"%"<<instruction->target_register<<" = ";
	  if (instruction->operand1.isreg)
	  	std::cout <<"%"<<instruction->operand1.operand.reg;
	  else
		std::cout << instruction->operand1.operand.number;
	  break;
	case Return:
	  std::cout<<"ret " <<"%"<< instruction->operand1.operand.reg;
	  break;
	case Binary:
	  std::cout << "%" << instruction->target_register << " = ";
	  std::cout << toString(instruction->binaryOp);
	  if (instruction->operand1.isreg) {
	  std::cout << "%"<<instruction->operand1.operand.reg;
	  } else {
	  std::cout << instruction->operand1.operand.number;
	  }
	  if (instruction->operand2.isreg) {
	  std::cout << " %"<<instruction->operand2.operand.reg;
	  } else {
	  std::cout << instruction->operand2.operand.number;
	  }
	default:
	  break;
  }
  std::cout << "\n";
}

CodeGenVisitor::CodeGenVisitor() {
  out_file.open("../riscv/a.s");
  if (!out_file.is_open()) {
	std::cout << "file a.s can't open\n";
	exit(-1);
  }
}

CodeGenVisitor::CodeGenVisitor(const char *outfile) {
  out_file.open(outfile);
  if (!out_file.is_open()) {
	std::cout << "file"<<outfile<< "can't open\n";
	exit(-1);
  }
}

void CodeGenVisitor::VisitProgram(Program *program) {
  out_file << "\t.text\n";
  out_file << "\t.global main\n";
  for (auto &func : program->functions) {
	func.accept(this);
  }
}

void CodeGenVisitor::VisitFunction(Function *function) {
  out_file << function->name << ":\n";
  for (auto &block : function->blocks) {
	block.accept(this);
  }
}

void CodeGenVisitor::VisitBaseBlock(BaseBlock *baseBlock) {
  for (auto &ins : baseBlock->instructions) {
	ins.accept(this);
  }
}


// 根据指令生成代码
// todo!(代码生成)
void CodeGenVisitor::VisitInstruction(Instruction *instruction) {
  switch (instruction->instructionType) {
	case Integer:
	  //todo!(需要修改立即数的加载和寄存器数的加载)
	  out_file << "	li  "
			   << "t" << instruction->target_register << ",";
	  if (instruction->operand1.isreg)
		out_file << "t" << instruction->operand1.operand.reg;
	  else
		out_file << instruction->operand1.operand.number;
	  out_file<<"\n";
	  break;
	case Return:
	  out_file << "	mv	 "
			   << "a0, "
			   << "t" << instruction->operand1.operand.reg;
	  out_file << "\n";
	  out_file << "	ret  ";
	  out_file<<"\n";
	  break;
	case Binary:
	  if (instruction->binaryOp == BinaryOp::Eq) {
		// 生成相等的指令
		out_file << "	xor  ";
		if (instruction->operand2.isreg) {
		  out_file << "t" << instruction->operand2.operand.reg << ", ";
		  out_file << "t" << instruction->operand2.operand.reg << ", ";
		} else {
		  out_file << instruction->operand2.operand.number << ",";
		  out_file << instruction->operand2.operand.number << ",";
		}
		out_file << "x0";
		out_file <<"\n";
		out_file << "	seqz  ";
		out_file << "t" << instruction->target_register<<", ";
		out_file << "t" << instruction->operand2.operand.reg;
		out_file<<"\n";
	  } else {
		out_file << "	" << toString(instruction->binaryOp) << " ";
		out_file << "t" << instruction->target_register << ", ";
		out_file << "x0, ";
		out_file << "t" << instruction->operand2.operand.reg ;
		out_file<<"\n";
	  }
	default:
	  break;
  }
}
