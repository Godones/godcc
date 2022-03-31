//
// Created by linfeng on 2022/3/31.
//

#ifndef GODCC_BACKEND_ASM_H_
#define GODCC_BACKEND_ASM_H_
#include "../IR/irvisitor.h"

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

#endif//GODCC_BACKEND_ASM_H_
