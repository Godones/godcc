//
// Created by linfeng on 2022/3/13.
//

#ifndef GODCC_IR_H
#define GODCC_IR_H

#include "irvisitor.h"
#include <iostream>
#include <string_view>
#include <vector>
#include "tools/log.h"

class Program;
class Function;
class BaseBlock;
class Instruction;
class IrVisitor;
enum InstructionType {
  Integer,
  ZeroInit,
  FuncArgRef,
  Alloc,
  GlobalAlloc,
  Load,
  Store,
  GetPtr,
  GetElementPtr,
  Binary,
  Unary,
  Branch,
  Jump,
  Return,
  Call,
};
enum BinaryOp {
  Add,//+
  Sub,//-
  Mul,//*
  Div,///
  Mod,//%
  Shl,//<<
  Shr,//>>
  And,//&&
  Or,//||
  Ne,//!=
  Le,//<=
  Ge,//>=
  Lt,//<
  Gt,//>
  Eq, //==
  Invalid
};

enum DataType {
  Void,
  Int,//当前仅支持
  Float,
  Double,
  Pointer,
};

class IRBase {
 public:
  IRBase() = default;
  virtual void accept(IrVisitor *) = 0;
};

// 程序定义
class Program : public IRBase {
 public:
  std::vector<Function> functions;
  Program() = default;
  void accept(IrVisitor *visitor);
};

// 程序由函数和全局指令组成
class Function : public IRBase {
 public:
  std::string name;
  DataType retType;
  std::vector<BaseBlock> blocks;
  Function() = default;
  void accept(IrVisitor *visitor);
};

// 函数由基本块组成
class BaseBlock : public IRBase {
 public:
  std::string blockName;
  std::vector<Instruction> instructions;
  BaseBlock() = default;
  void accept(IrVisitor *visitor);
};

// 指令定义,包括全局指令、局部指令
// 全局指令: 全局变量声明、全局函数声明
// 局部指令: 局部变量声明、局部函数声明

class Instruction : public IRBase {
 public:
  // 指令类型
  InstructionType instructionType;
  // 指令类型对应的操作数
  // 操作数可以是立即数
  // 也可以是寄存器的名字
  BinaryOp binaryOp;
  typedef struct {
	union {
	  int number;
	  unsigned int reg;
	}operand;
	bool isreg;
	} Operand;

  Operand operand1;
  Operand operand2;
  unsigned int target_register;
  Instruction() = default;
  void accept(IrVisitor *visitor);
};

std::string_view toString(const InstructionType &type);
std::string_view toString(const DataType &op);
std::string_view toString(const BinaryOp&binary_op);

#endif//GODCC_IR_H
