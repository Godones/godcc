//
// Created by linfeng on 2022/3/15.
//

#ifndef GODCC_TPARSER_H
#define GODCC_TPARSER_H

#include <cassert>
#include <fstream>
#include <iostream>

#include "../backend/asm.h"
#include "../frontend/ast.h"
#include "frontend/ast_text_view.h"
#include "frontend/ast_to_ir.h"
#include "frontend/ast_tree_view.h"
#include "frontend/cst_tree_view.h"
#include "semantic.h"
#include "tools/log.h"

int test_ast_text();

void test_ir_gen();

void test_semantic();
void test_ast_tree();
void test_cst_tree();
void test_asm_gen();
std::shared_ptr<Ast> parser(const char *filename);
void test_parse_correct();
#endif//GODCC_TPARSER_H
