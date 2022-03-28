//
// Created by linfeng on 2022/3/15.
//
#include "Tparser.h"

//导入文件声明和函数声明
extern FILE *yyin;
extern void file_out(const char* word,const char* type);
extern int yyparse(std::shared_ptr <Ast> &ast);
extern FILE *yyout;

int testParser() {
  yyin = fopen("../hello.c", "r");
  if (yyin == nullptr) {
    std::cout << "open file "<<"../hello.c"<<" failed\n" ;
    return -1;
  }
  //需要输出token
  yyout = fopen("token.txt", "w");
  if (yyout == nullptr) {
    std::cout << "open file "<<"token.txt"<<" failed\n" ;
    return -1;
  }
//  file_o
  fprintf(yyout, "token\n");
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