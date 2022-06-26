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
	out << "\t li a0, " << instruction->operand1.operand.number << "\n";
  } else if (instruction->operand1.type==OperandType::kNumber) {
	out << "\t add a0, zero, " << instruction->operand1.operand.number << "\n";
  }
  out << "\t ret\n";
}

void AsmGenerator::genProgram(Program *program ){
  // todo!生成全局变量
  out << "\t.text\n";
  out << "\t.global main\n";
}
void AsmGenerator::genFunction(Function *function) {
  out<< "\t" << function->name << ":\n";
}
void AsmGenerator::genBinary(Instruction *instruction) {
  switch (instruction->binaryOp) {
	case BinaryOp::Add:{
	  break ;
	}
	case BinaryOp::Sub: break;
	case BinaryOp::Mul: break;
	case BinaryOp::Div: break;
	case BinaryOp::Mod: break;
	case BinaryOp::And: break;
	case BinaryOp::Or: break;
	case BinaryOp::Ne: break;
	case BinaryOp::Le: break;
	case BinaryOp::Ge: break;
	case BinaryOp::Lt: break;
	case BinaryOp::Gt: break;
	case BinaryOp::Eq: break;
	case BinaryOp::Invalid: break;
  }
}
