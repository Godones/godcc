//
// Created by linfeng on 2022/3/13.
//

#ifndef GODCC_IR_H
#define GODCC_IR_H
#include <iostream>
#include <vector>
#include "irvisitor.h"

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
    Branch,
    Jump,
    Return,
    Call,
};
enum BinaryOp {
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Shl,
    Shr,
    And,
    Or,
    Xor,
};

enum DataType {
    Void,
    Int, //当前仅支持
    Float,
    Double,
    Pointer,
};

class IRBase{
    virtual void accept(IrVisitor*)=0;
};
// 程序定义
class Program:public IRBase{
public:
    std::vector<Function> functions;
    void accept(IrVisitor *visitor);
};

// 程序由函数和全局指令组成
class Function:public IRBase{
public:
    std::string name;
    DataType retType;
    std::vector<BaseBlock> blocks;
    void accept(IrVisitor *visitor);
};

// 函数由基本块组成
class BaseBlock:public IRBase{
public:
    std::string blockName;
    std::vector<Instruction> instructions;
    void accept(IrVisitor *visitor);
};

// 指令定义,包括全局指令、局部指令
// 全局指令: 全局变量声明、全局函数声明
// 局部指令: 局部变量声明、局部函数声明

class Instruction:public IRBase{
public:
    // 指令类型
    InstructionType instructionType;
    // 指令类型对应的操作数
    int operand;
    void accept(IrVisitor *visitor);
};

std::string toString(const InstructionType& type);
std::string toString(const DataType& op);

#endif //GODCC_IR_H
