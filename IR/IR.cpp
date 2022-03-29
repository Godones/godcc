//
// Created by linfeng on 2022/3/13.
//

#include "IR.h"

std::string_view toString(const InstructionType &type) {
  switch (type) {
	case InstructionType::Return: return "ret";
	case InstructionType::Call: return "call";
	case InstructionType::Binary: return "binary";
	default: exit(-1);
  }
}

std::string_view toString(const DataType &dataType) {
  switch (dataType) {
	case DataType::Int: return "i32";
	default: return "";
  }
}

std::string_view toString(const BinaryOp&binary_op){
  switch (binary_op) {
	case Add: return "add ";
	case Sub: return "sub ";
	case Mul: return "mul ";
	case Div: return "div ";
	case Mod: return "mod ";
	case Shl: return "shl ";
	case Shr: return "shr ";
	case And: return "and ";
	case Or: return "or ";
	case Xor: return "xor " ;
	case Eq: return "eq ";
  }
  //todo!(符号错误)
  exit(-1);
}

void Program::accept(IrVisitor *visitor) {
  visitor->VisitProgram(this);
}

void Function::accept(IrVisitor *visitor) {
  visitor->VisitFunction(this);
}

void BaseBlock::accept(IrVisitor *visitor) {
  visitor->VisitBaseBlock(this);
}

void Instruction::accept(IrVisitor *visitor) {
  visitor->VisitInstruction(this);
}
