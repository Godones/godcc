//
// Created by linfeng on 2022/5/1.
//

#include "symbolTable.h"

#include <iomanip>

std::string_view DataTypeToString(DataType type){
  switch (type) {

	case kNone: {
	  return "null";
	};
	case kVoid: {
	  return "void";
	};
	case kInt: {
	  return "int";
	};
	case kFloat: {
	  return "float";
	};
	case kConstInt: {
	  return "const int";
	};
	case kFunc: {
	  return "func";
	}
	default:
	  return "unknown";
  }
}
void SymbolTable::add_symbol(const std::string& key, const SymbolInfo& info) {
  //添加符号时只需要查找当前的符号表，如果找到了就报错
  if (table.find(key) != table.end()) {
	  std::cerr << "Error: " << key << " has been defined." << std::endl;
	  exit(1);
  }
  table[key] = info;
  key_list.emplace_back(key);
}

SymbolTable* SymbolTable::enter_scope() {
  SymbolTable *new_table = new SymbolTable();
  child_list.emplace_back(new_table);
  new_table->parent = this;
  return new_table; //返回新的符号表
}
SymbolTable* SymbolTable::exit_scope() const{
  assert(parent != nullptr);
  // 退出当前作用域，返回父作用域
  return parent;
}
SymbolInfo* SymbolTable::get_symbol(const std::string& key) {
  //查找符号时需要从当前的符号表开始查找，如果没有找到，就往上一级符号表查找
  auto iter = table.find(key);
  if (iter != table.end()) {
	return &iter->second;
  }
  if (parent != nullptr) {
	return parent->get_symbol(key);
  }
  return nullptr;
}
void SymbolTable::dump(int depth) {
  // 打印符号表
  std::string tab = std::string(depth, ' ');
  std::cout <<tab<<"Symbol Table:" << std::endl;
  for (auto& key : key_list) {
	std::cout  << tab << key << ": ";
	auto info = get_symbol(key);
	if (info){
	  info->dump();
	  std::cout << std::endl;
	}
  }
  for (auto& child : child_list) {
	child->dump(depth +4);
  }
}
bool SymbolTable::has_symbol(const std::string& key) {
  // 查看是否有该符号
  // 只在本scope查找
  return table.find(key) != table.end();
}

void SymbolTable::delete_symbol(const std::string& key) {
  // 删除符号 只在语义分析阶段使用
  if(has_symbol(key)) {
	table.erase(key);
  }
}

void ArrayInfo::dump() {
  // 打印数组信息
  std::cout << DataTypeToString(type) << " ";
  std::cout << "(";
   for(int i=0;i<dim_num;i++){
	 std::cout << dim[i] << ",";
   }
  std::cout << ") ";
}

void FuncInfo::dump() {
  // 打印函数信息
  std::cout << DataTypeToString(ret_type) << " ";
  std::cout << "(";
  for (auto& param : params) {
	param.dump();
	std::cout << ",";
  }
  std::cout << ") ";
}
bool FuncInfo::has_param(DataType type, std::string_view name) {
  //检查是否已经有此参数
  for (auto& param : params) {
	if (param.type == type && param.name == name) {
	  return true;
	}
  }
  return false;
}
void SymbolInfo::dump() {
  // 打印符号信息
  std::cout << DataTypeToString(type) << " ";
  if (type == kConstInt || type == kInt || type == kFloat) {
	if(!name.empty()){
	  std::cout << name << " ";
	}
	if (have_value) {
	  std::cout << "true" << " ";
	} else {
	  std::cout << "false" << " ";
	}
	std::cout << value << " ";
  }
  else if (type == kFunc) {
	auto func_info = (FuncInfo*)(ptr);
	func_info->dump();
  }
  else if (type == kArray) {
	auto array_info = (ArrayInfo*)(ptr);
	array_info->dump();
  }
}
