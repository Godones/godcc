//
// Created by linfeng on 2022/3/30.
// target: test tools lib
//
#include "json.h"
#include "log.h"
#include "dot.h"

void json_test(){

  GodJSon json;
  json.BeganWrite("Function");
  json.BeganWrite("Stmt");
  json.EndWrite();
  json.EndWrite();
  json.close();
  INFO("Json test Ok");
}

void dot_test(){

  GDot dot("test.dot");
  dot.BeganWrite("Function");
  dot.BeganWrite("Stmt");
  dot.BeganWrite("Stmt");
  dot.BeganWrite("Stmt");
  dot.EndWrite();
  dot.EndWrite();
  dot.EndWrite();
  dot.BeganWrite("Decl");
  dot.EndWrite();
  dot.EndWrite();
  dot.close();
  INFO("Dot test Ok");
}
int main(){
  json_test();
  dot_test();
  return 0;
}