//
// Created by linfeng on 2022/6/26.
//

#ifndef GODCC_ASMGENERATOR_H
#define GODCC_ASMGENERATOR_H
#include <iostream>
#include "IR.h"
#include "register.h"
#include "framestack.h"


class AsmGenerator {
 private:
  std::ofstream out;
  RegisterAllocator registerAllocator;
  FrameStack frameStack;
  std::string_view currentFunction;
 private:
  void initFrameStack(Function *func);
 public:
  explicit AsmGenerator(const char *filename);
  void reset();
  void genRet(Instruction* );
  void genProgram(Program*);
  void genFunction(Function*);
  void genFunctionEnd();
  void genBinary(Instruction*);
  void genAlloc(Instruction*);
  void genStore(Instruction*);
  void genLoad(Instruction*);
  void genCall(Instruction*);
  void genMars();
  void genBaseBlock(BaseBlock*);
  void genJump(Instruction*);
  void genBranch(Instruction*);
  void genGetElementPtr(Instruction*);
  void genGlobalString(Instruction* pInstruction);
  void genGloblData();
  void genGlobalAlloc(Instruction* pInstruction);
};

#endif//GODCC_ASMGENERATOR_H
