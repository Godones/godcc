//
// Created by linfeng on 2022/3/13.
//
#include "irvisitor.h"

#include "tools/log.h"

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
	case Unary:
	  std::cout <<"%"<<instruction->target_register<<" = ";
	  std::cout << toString(instruction->binaryOp);
	  std::cout << instruction->operand1.operand.number;
	  assert(instruction->operand2.isreg);
	  std::cout <<" %" <<instruction->operand2.operand.reg;
	  break;
	case Binary:
	  std::cout << "%" << instruction->target_register << " = ";
	  assert(instruction->operand1.isreg);
	  assert(instruction->operand2.isreg);
	  std::cout << toString(instruction->binaryOp);
	  std::cout << "%"<<instruction->operand1.operand.reg;
	  std::cout << " %"<<instruction->operand2.operand.reg;
	  break ;
	default:
	  break;
  }
  std::cout << "\n";
}

