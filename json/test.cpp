//
// Created by linfeng on 2022/3/30.
// target: test json lib
//
#include "json.h"

int main(){
  std::cout << "Json test:\n";
  GodJSon json;
  json.BeganWrite("Function");
  json.BeganWrite("Stmt");
  json.EndWrite();
  json.EndWrite();
  json.close();
  return 0;
}