//
// Created by linfeng on 2022/4/11.
//

#ifndef GODCC_TOOLS_DOT_H_
#define GODCC_TOOLS_DOT_H_
#include <cassert>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <stack>

#include "log.h"
class GDot {
 private:
  FILE *file;
  std::stack<int> id_stack;
  int node_id = 0;

 public:
  GDot();
  explicit GDot(const char *file_name);
  void BeganWrite(const char *fmt);
  void close();
  void EndWrite();
};

#endif//GODCC_TOOLS_DOT_H_
