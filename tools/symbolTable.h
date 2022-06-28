//
// Created by linfeng on 2022/5/1.
//

#ifndef GODCC_SYMBOLTABLE_H
#define GODCC_SYMBOLTABLE_H
#include <cassert>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "log.h"
enum DataType {
  kNone,
  kVoid,//函数返回类型
  kInt, //当前支持
  kFloat,
  kConstInt,//当前支持
  kFunc,    //函数
  kArray,   //数组
  kString,  //字符串
};
std::string DataTypeToString(DataType type);

//符号信息定义
struct SymbolInfo {
  DataType type;             //类型
  int value;                 //如果是常量，则存储常量值
  bool have_value = false;   //是否有值
  void *ptr = nullptr;       //指针 指向额外的信息存储位置
  std::string name;          //名称
  void *stored_ptr = nullptr;//存储地址
  void dump();
};
// 额外信息数组
struct ArrayInfo {
  DataType type;      //数组类型
  std::vector<int>dim;  //维度信息
  int size = 0;       //数组大小
  void *ptr = nullptr;//数组指针,有初始化时使用
  void dump();
  int get_size();

};
struct FuncInfo {
  std::vector<SymbolInfo> params;// 函数参数
  DataType ret_type;             // 函数返回值
  void dump();
};

// 符号表
struct SymbolTable {
  std::unordered_map<std::string, SymbolInfo> table;//hash表,存储符号信息
  std::vector<std::string> key_list;                //键值列表,按照插入顺序排序
  std::vector<SymbolTable *> child_list;            //子表
  SymbolTable *parent = nullptr;                    //父表

  int index = 0;                                                             //子表索引
  int level = 0;                                                             //层级
  void add_symbol(const std::string &key, const SymbolInfo &info);           //添加符号
  std::pair<int, SymbolInfo *> get_symbol_with_level(const std::string &key);//获取符号信息
  SymbolTable *enter_scope();                                                //进入子表
  SymbolTable *new_scope();                                                  //进入子表
  SymbolTable *exit_scope() const;                                           //退出子表
  bool has_symbol(const std::string &key);                                   //是否存在符号
  SymbolInfo *get_symbol(const std::string &key);                            //获取符号信息
  void dump(int depth = 0);                                                  //打印符号表
};

#endif//GODCC_SYMBOLTABLE_H
