//
// Created by linfeng on 2022/6/26.
//

#ifndef GODCC_ASMGENERATOR_H
#define GODCC_ASMGENERATOR_H
#include <iostream>
#include "IR.h"
class AsmGenerator {
 private:
  std::ofstream out;
 public:
  explicit AsmGenerator(const char *filename);
  void genRet(Instruction* );
  void genProgram(Program*);
  void genFunction(Function*);
  void genBinary(Instruction*);
};

#endif//GODCC_ASMGENERATOR_H
