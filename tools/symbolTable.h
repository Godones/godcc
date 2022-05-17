//
// Created by linfeng on 2022/5/1.
//

#ifndef GODCC_SYMBOLTABLE_H
#define GODCC_SYMBOLTABLE_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <iomanip>
#include <queue>
enum DataType {
  kNone,
  kVoid,
  kInt,//当前仅支持
  kFloat,
  kConstInt,
  kFunc,//函数
  kArray,//数组
};

std::string_view DataTypeToString(DataType type);

//符号信息定义
struct SymbolInfo{
	DataType type;
	int value;
	bool have_value = false;//是否有值
	void *ptr = nullptr;//指针 指向额外的信息存储位置
	std::string_view name; //名称
	void dump();
};
// 额外信息数组
struct ArrayInfo{
  	DataType type; //数组类型
	//维度信息
	int dim[10] = {0};
	//维度数量
	int dim_num = 0;
	//数组大小
	int size = 0;
	//数组指针,有初始化时使用
	void *ptr = nullptr;
	void dump();
};
struct FuncInfo{
  // 函数参数
  std::vector<SymbolInfo> params;
  // 函数返回值
  DataType ret_type;
  bool has_param(DataType type, std::string_view name);
  void dump();
};


// 符号表
struct SymbolTable{
  std::unordered_map<std::string, SymbolInfo> table;
  std::vector<std::string> key_list;
  std::vector<SymbolTable*> child_list; //子表
  SymbolTable *parent=nullptr;
  void add_symbol(const std::string& key, const SymbolInfo& info);
  SymbolTable *enter_scope();
  SymbolTable *exit_scope() const;
  bool has_symbol(const std::string& key);
  SymbolInfo* get_symbol(const std::string& key);
  void dump(int depth=0);
  void delete_symbol(const std::string& key);
};



#endif//GODCC_SYMBOLTABLE_H
