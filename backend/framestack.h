//
// Created by linfeng on 2022/6/27.
//

#ifndef GODCC_FRAMESTAACK_H
#define GODCC_FRAMESTAACK_H
#include <unordered_map>
#include "../tools/log.h"

class FrameStack {
 private:
  std::unordered_map<std::string,int> frame_map;//变量和偏移量的关系
  int top = 0;//栈顶
  int size = 0;//栈的大小
 public:
  FrameStack()=default;
  int get_offset(const std::string& name);
  void push(const std::string& name,int size);
  void correct();
  int get_size();
  bool has_name(const std::string& name);
};
#endif//GODCC_FRAMESTAACK_H
