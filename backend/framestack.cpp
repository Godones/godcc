//
// Created by linfeng on 2022/6/27.
//

#include "framestack.h"

void FrameStack::push(const std::string &name, int var_size) {
  // 变量以及各种参数入栈
  frame_map[name] = top;
  top += var_size;
  size += var_size;
}

int FrameStack::get_offset(const std::string& name) {
  // 获取变量的偏移量
  auto it = frame_map.find(name);
  if (it == frame_map.end()) {
	ERROR("variable not found");
	return -1;
  }
  return it->second;
}
void FrameStack::correct() {
  // 检查栈大小是否按照16字节对齐
  if (size % 16 != 0) {
	size += 16 - size % 16;
  }
}
int FrameStack::get_size() {
  return size;
}
bool FrameStack::has_name(const std::string& name) {
  return frame_map.find(name) != frame_map.end();
}
