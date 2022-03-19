//
// Created by linfeng on 2022/3/15.
//
#include "Tparser.h"

//导入文件声明和函数声明
extern FILE *yyin;

extern int yyparse(std::shared_ptr <Ast> &ast);

extern std::ofstream token_file;

int testParser() {
  yyin = fopen("hello.c", "r");
  if (yyin == nullptr) {
    std::cerr << "open file error" << std::endl;
    return -1;
  }
  //需要输出token
  token_file.open("build/scanner_example.tokens");
  if (!token_file.is_open()) {
    std::cerr << "open file error" << std::endl;
    return -1;
  }
  std::shared_ptr <Ast> ast;
  auto result = yyparse(ast);
  std::cout << "Parse result:" << result << std::endl;
  assert(!result);
  auto visitor = AstVisitor();
  ast->accept(&visitor);
  std::cout << "\n";
  return 0;
}

//void testIRCodeGen(){
//    yyin = fopen("hello.c", "r");
//    if (yyin == nullptr) {
//        std::cerr << "open file error" << std::endl;
//        return ;
//    }
//    std::shared_ptr<Ast> ast;
//    auto result = yyparse(ast);
//    assert(!result);
//    auto visitor = IRGeneratorVisitor();
//    ast->accept(&visitor);
//    auto ir_code = visitor.programIr;
//    auto irvisitor = IrVisitorDefault();
//    ir_code->accept(&irvisitor);
//    return ;
//}
//void testAsmCodeGen(){
//    yyin = fopen("hello.c", "r");
//    if (yyin == nullptr) {
//        std::cerr << "open file error" << std::endl;
//        return ;
//    }
//    std::shared_ptr<Ast> ast;
//    auto result = yyparse(ast);
//    assert(!result);
//    auto visitor = IRGeneratorVisitor();
//    ast->accept(&visitor);
//    auto ir_code = visitor.programIr;
//    auto asmCodeGen = CodeGenVisitor();
//    ir_code->accept(&asmCodeGen);
//    return ;
//}