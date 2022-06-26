//
// Created by linfeng on 2022/6/26.
//

#ifndef GODCC_REGISTER_H
#define GODCC_REGISTER_H
#include <unordered_map>
#include <queue>
#include <iostream>


// 寄存器分配类
// 功能:负责分配risc-v的寄存器给目标代码生成模块
// 寄存器分配针对每一个函数
class RegisterAllocator{
 private:
  std::unordered_map<int,std::string > reg_var_map; //寄存器到变量的映射
  std::unordered_map<std::string,int> var_reg_map; // 变量到寄存器的映射
  std::queue<int> unused_reg; // 未使用的寄存器
 public:
  RegisterAllocator();
  void add_param_reg(int params); // 添加参数寄存器
//  void flush(int params); // 删除参数寄存器
};


#endif//GODCC_REGISTER_H
