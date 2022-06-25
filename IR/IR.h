//
// Created by linfeng on 2022/3/13.
//

#ifndef GODCC_IR_H
#define GODCC_IR_H

#include <iostream>
#include <string_view>
#include <vector>

#include "irvisitor.h"
#include "tools/log.h"
#include "tools/symbolTable.h"

struct Program;
struct Function;
struct BaseBlock;
struct Instruction;
struct IrVisitor;

// 指令类型
enum class InstructionType {
  Integer, // 整数
  ZeroInit,// 初始化为0
  FuncArgRef,
  Aggregate,    //由于数组的初始化
  Alloc,        //局部变量
  GlobalAlloc,  //全局变量
  Load,         // 加载数
  Store,        // 存储数
  GetPtr,       // 指针，用于数组
  GetElementPtr,// 数组元素
  Binary,       // 二元运算表达式
  Branch,       //分支
  Jump,         // 跳转 --> 分支
  Return,       // 返回语句   return lvalue|number|symbol|null
  Call,         //函数调用语句 call <symbol>
  Move,         //移动语句
};
enum class BinaryOp {
  Add ,//+
  Sub,//-
  Mul,//*
  Div,///
  Mod,//%
  And,//&&
  Or, //||
  Ne, //!=
  Le, //<=
  Ge, //>=
  Lt, //<
  Gt, //>
  Eq, //==
  Invalid
};

struct IRBase {
 public:
  IRBase() = default;
  virtual void accept(IrVisitor *) = 0;
};

// 程序定义
struct Program {
 public:
  std::vector<Function> functions;//函数列表
  BaseBlock *global_block;        //全局变量列表
  Program() = default;
  void accept(IrVisitor *visitor);
};

// 程序由函数和全局指令组成
struct Function {
 public:
  std::string_view name;          //函数名称
  DataType retType;               // 返回值类型
  std::vector<BaseBlock> blocks;  //基本块列表
  std::vector<Instruction> params;//函数参数
  Function() = default;
  void accept(IrVisitor *visitor);
};

// 函数由基本块组成
struct BaseBlock {
 public:
  int blkId = 0;
  std::vector<Instruction> instructions{};//指令列表
  BaseBlock() = default;
  BaseBlock(int id);
  void accept(IrVisitor *visitor);
};

// 四元式操作数定义
// 操作数类型
enum class OperandType {
  kString, // 符号字符串-->函数
  kNumber, // 指令虚拟寄存器号
  kInteger,// 常数
  kLabel,  //基本块编号
};
struct Operand {
  union {
	int number;        // 整数
	const char *symbol;// 字符串
  } operand;           // 操作数
  OperandType type;
};

// 指令定义,包括全局指令、局部指令
// 全局指令: 全局变量声明、全局函数声明
// 局部指令: 局部变量声明、局部函数声明
struct Instruction {
 public:
  InstructionType instructionType;// 指令类型
  DataType dataType;              //数据类型
  BinaryOp binaryOp;              //二元运算符
  Operand operand1{};             //操作数1
  Operand operand2{};             //操作数2
  Operand operand3{};             //操作数3 //只有在branch会使用三个 操作数
  int m_number;                   //指令的值所用虚拟寄存器编号
  std::string_view name;          // 保存变量名称或者函数名称
  std::vector<Instruction> extra; // 额外信息，在函数参数中使用
  std::vector<int>array_dim;	  // 数组维度+数组元素
  struct Instruction *next = nullptr;//指向下一条指令,
  void accept(IrVisitor *visitor);
};

std::string_view toString(const InstructionType &type);
std::string_view toString(const DataType &op);
std::string_view toString(const BinaryOp &binary_op);

#endif//GODCC_IR_H
