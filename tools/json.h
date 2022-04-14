//
// Created by linfeng on 2022/3/30.
//

#ifndef GODCC_JSON_JSON_H_
#define GODCC_JSON_JSON_H_
#include <iostream>
#include <fstream>
#include <cstdarg>
class GodJSon{
 private:
  FILE *file;
  int state = 0;
 public:
  GodJSon();
  explicit GodJSon(const char *file_name);
  virtual void BeganWrite(const char * dot_name,...);
  virtual void close();
  virtual void EndWrite();
};
#endif//GODCC_JSON_JSON_H_
