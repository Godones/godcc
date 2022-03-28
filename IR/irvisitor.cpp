//
// Created by linfeng on 2022/3/13.
//
#include "../log/log.h"
#include "irvisitor.h"

void IrVisitorDefault::VisitProgram(Program *program) {
  std::cout << "Program <> \n";
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
  std::cout << toString(instruction->instructionType) << " ";
//  std::cout << instruction->operand1;
  std::cout << "\n";
}

CodeGenVisitor::CodeGenVisitor() {
  out_file.open("a.s");
  if (!out_file.is_open()) {
    std::cout << "file can't open\n";
  }
}

CodeGenVisitor::CodeGenVisitor(const char *outfile) {
  out_file.open(outfile);
  if (!out_file.is_open()) {
    std::cout << "file can't open\n";
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

void CodeGenVisitor::VisitInstruction(Instruction *instruction) {
  switch (instruction->instructionType) {
  case InstructionType::Return: {
//    out_file << "\tli a0," << instruction->operand1 << "\n";
    out_file << "\tret\n";
  }
  default:break;
  }
}
