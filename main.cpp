//
// Created by linfeng on 2022/3/10.
//
#include "test/Tparser.h"


int main(int argc, const char *argv[]) {
  INFO("Godcc:");

#ifdef PARSE_TEST
  test_parse_correct();
  INFO("parse all files ok!");
#endif

  INFO("test_cst_text:");
  test_ast_text();
  INFO("test_cst_text ok!");


  INFO("test_cst_tree:");
  test_cst_tree();
  INFO("test_cst_tree ok!");

  INFO("test_ast_tree:");
  test_ast_tree();
  INFO("test_ast_tree ok!");
//
//  INFO("test_ir_gen:");
//  test_ir_gen();
//  INFO("test_ir_gen ok!");
//
//  INFO("test_asm_gen:");
//  test_asm_gen();
//  INFO("test_asm_gen ok!");
//
  INFO("test_semantic");
  test_semantic();
  INFO("test_semantic ok!");

  return 0;
}
