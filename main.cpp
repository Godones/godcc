//
// Created by linfeng on 2022/3/10.
//
#include <iostream>
#include <string>
#include <memory>
#include <cassert>
#include "frontend/ast.h"
#include "frontend/visitor.h"
//导入文件声明和函数声明
extern FILE *yyin;
extern int yyparse(std::shared_ptr<Ast> &ast);


int main(int argc,const char*argv[]) {

    assert(argc == 5);
    std::string mode(argv[1]);
    std::string input(argv[2]);
    std::string output(argv[4]);

    yyin = fopen(input.c_str(), "r");
    if (yyin == nullptr) {
        std::cerr << "open file error" << std::endl;
        return -1;
    }
    std::shared_ptr<Ast> ast;
    auto result = yyparse(ast);
    assert(!result);
    auto visitor = AstVisitor();
    ast->accept(&visitor);
    return 0;
}