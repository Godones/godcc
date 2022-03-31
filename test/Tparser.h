//
// Created by linfeng on 2022/3/15.
//

#ifndef GODCC_TPARSER_H
#define GODCC_TPARSER_H

#include "../frontend/ast.h"
#include "../log/log.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "../backend/asm.h"

int testParser();

void testIRCodeGen();

void testAsmCodeGen();

void testAsmViewGen();
#endif//GODCC_TPARSER_H
