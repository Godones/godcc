//
// Created by linfeng on 2022/3/13.
//

#include "IR.h"

std::string toString(const InstructionType &type) {
  switch (type) {
  case InstructionType::Return:return "ret";
  default:return "";
  }
}

std::string toString(const DataType &dataType) {
  switch (dataType) {
  case DataType::Int:return "i32";
  default:return "";
  }
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
