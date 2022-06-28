//
// Created by linfeng on 2022/3/31.
//

#include "asm.h"
CodeGenVisitor::CodeGenVisitor() : asmGenerator("../riscv/a.asm"){}

CodeGenVisitor::CodeGenVisitor(const char *outfile): asmGenerator(outfile){}

void CodeGenVisitor::VisitProgram(Program *program) {
  asmGenerator.genGloblData();
  for (auto & instruction : program->global_block->instructions) {
	instruction.accept(this);
  }
  asmGenerator.genProgram(program);
  for (auto &func : program->functions) {
	asmGenerator.reset();
	func.accept(this);
  }
}

void CodeGenVisitor::VisitFunction(Function *function) {
  asmGenerator.genFunction(function);
  for (auto &block : function->blocks) {
	block.accept(this);
  }
}

void CodeGenVisitor::VisitBaseBlock(BaseBlock *baseBlock) {
  asmGenerator.genBaseBlock(baseBlock);
  for (auto &ins : baseBlock->instructions) {
	ins.accept(this);
  }
}

// 根据指令生成代码
// todo!(代码生成)
void CodeGenVisitor::VisitInstruction(Instruction *instruction) {
  switch (instruction->instructionType) {
	case InstructionType::Integer:
	  //todo!(需要修改立即数的加载和寄存器数的加载)
	  break;
	case InstructionType::Return:
	  asmGenerator.genRet(instruction);
	  break;
	case InstructionType::Binary:
	  // 二元运算+一元运算
	  asmGenerator.genBinary(instruction);
	  break;
	case InstructionType::Alloc:
	  asmGenerator.genAlloc(instruction);
	  break;
	case InstructionType::Load:
	  asmGenerator.genLoad(instruction);
	  break;
	case InstructionType::Store:
	  asmGenerator.genStore(instruction);
	  break;
	case InstructionType::Call: {
	  asmGenerator.genCall(instruction);
	  break;
	}
	case InstructionType::Jump :{
	  asmGenerator.genJump(instruction);
	  break;
	}
	case InstructionType::Branch:{
	  asmGenerator.genBranch(instruction);
	}
	case InstructionType::GetElementPtr:
	  asmGenerator.genGetElementPtr(instruction);
	  break;
	case InstructionType::GlobalString:{
	  asmGenerator.genGlobalString(instruction);
	  break;
	}
	case InstructionType::GlobalAlloc:
	  asmGenerator.genGlobalAlloc(instruction);
	  break;
	default:
	  break;
  }
}
