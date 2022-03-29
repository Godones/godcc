//
// Created by linfeng on 2022/3/13.
//

#ifndef GODCC_IRVISITOR_H
#define GODCC_IRVISITOR_H

#include "IR.h"
#include <fstream>
#include <cassert>
class Program;
class Function;
class BaseBlock;
class Instruction;

class IrVisitor {
 public:
  virtual void VisitProgram(Program *) = 0;

  virtual void VisitFunction(Function *) = 0;

  virtual void VisitBaseBlock(BaseBlock *) = 0;

  virtual void VisitInstruction(Instruction *) = 0;
};

// 查看中间代码形式
class IrVisitorDefault : public IrVisitor {
 public:
  void VisitProgram(Program *) override;

  void VisitFunction(Function *) override;

  void VisitBaseBlock(BaseBlock *) override;

  void VisitInstruction(Instruction *) override;
};

//汇编代码生成
class CodeGenVisitor : public IrVisitor {
 public:
  std::ofstream out_file;
  int a = 0;

 public:
  CodeGenVisitor();

  explicit CodeGenVisitor(const char *outfile);

  void VisitProgram(Program *) override;

  void VisitFunction(Function *) override;

  void VisitBaseBlock(BaseBlock *) override;

  void VisitInstruction(Instruction *) override;
};

#endif//GODCC_IRVISITOR_H
