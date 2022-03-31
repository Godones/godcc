//
// Created by linfeng on 2022/3/30.
//

#ifndef GODCC_JSON_JSON_H_
#define GODCC_JSON_JSON_H_
#include <iostream>
#include <fstream>

class GodJSon{
 private:
  std::ofstream file;
  int state = 0;
 public:
  GodJSon();
  explicit GodJSon(const char *file_name);
  void BeganWrite(const std::string_view &dot_name);
  void close();
  void EndWrite();
};
#endif//GODCC_JSON_JSON_H_
