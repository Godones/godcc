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
	case DataType::kInt: return "i32";
	case DataType::kConstInt : return "i32";
	default: return "";
  }
}

std::string_view toString(const BinaryOp&binary_op){
  switch (binary_op) {
	case BinaryOp::Add: return "add ";
	case BinaryOp::Sub: return "sub ";
	case BinaryOp::Mul: return "mul ";
	case BinaryOp::Div: return "div ";
	case BinaryOp::Mod: return "rem ";
	case BinaryOp::And: return "and ";
	case BinaryOp::Or: return "or ";
	case BinaryOp::Lt: return "lt ";
	case BinaryOp::Gt: return "gt ";
	case BinaryOp::Le: return "le ";
	case BinaryOp::Ge: return "ge ";
	case BinaryOp::Eq: return "eq ";
	case BinaryOp::Ne: return "ne ";
	default: break;
  }
  //todo!(符号错误)
  INFO("\n符号错误");
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
BaseBlock::BaseBlock(int id):blkId(id){}

void Instruction::accept(IrVisitor *visitor) {
  visitor->VisitInstruction(this);
}
