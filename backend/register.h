//
// Created by linfeng on 2022/6/26.
//

#ifndef GODCC_REGISTER_H
#define GODCC_REGISTER_H
#include <unordered_map>
#include <deque>
#include <iostream>
#include <algorithm>
#include "../tools/log.h"

// 寄存器分配类
// 功能:负责分配mips32的寄存器给目标代码生成模块
// 寄存器分配针对每一个函数
class RegisterAllocator{
 private:
  std::unordered_map<int,int> virtualRegMap; //虚拟寄存器与实际寄存器的对应关系
  int regNum = 16; // 寄存器数量
//  int unusedReg[16] = {0};
  std::deque<int> unusedReg; // 未使用的寄存器
  std::vector<int> allReg; // 所有的寄存器
 public:
  RegisterAllocator();
  int getReg(int virtualReg); // 获取一个寄存器
  int getTempReg(); // 获取一个寄存器,这种寄存器会马上被回收
  void freeReg(int reg); // 释放一个寄存器
  void freeTempReg(int reg); // 释放一个临时寄存器
  void addVirtualReg(int virtualReg,int reg); // 添加一个虚拟寄存器与实际寄存器的对应关系
  std::vector<int> getUsedReg(); // 获取所有已使用的寄存器
};


#endif//GODCC_REGISTER_H
