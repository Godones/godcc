//
// Created by linfeng on 2022/3/10.
//
#include <iostream>

#include "test/Tparser.h"
int main(int argc, const char *argv[]) {
  INFO("Godcc:");
  test_parse_correct();
  INFO("parse all files ok!");
  test_ast_text();
  test_ast_tree();
  return 0;
}
