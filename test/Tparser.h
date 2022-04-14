//
// Created by linfeng on 2022/3/15.
//

#ifndef GODCC_TPARSER_H
#define GODCC_TPARSER_H

#include "../frontend/ast.h"
#include "tools/log.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "../backend/asm.h"
#include "frontend/cst_tree_view.h"
#include "frontend/ast_text_view.h"
#include "frontend/ast_to_ir.h"
#include "frontend/ast_tree_view.h"

int test_ast_text();

void testIRCodeGen();

void test_ast_tree();
void test_cst_tree();
void test_ast_ir();

void test_parse_correct();
#endif//GODCC_TPARSER_H
