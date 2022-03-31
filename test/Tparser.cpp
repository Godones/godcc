//
// Created by linfeng on 2022/3/15.
//
#include "Tparser.h"

//导入文件声明和函数声明
extern FILE *yyin;
extern void file_out(const char *word, const char *type);
extern int yyparse(std::shared_ptr<Ast> &ast);
extern FILE *yyout;


void openFile(){
  yyin = fopen("../test/hello.c", "r");
  if (yyin == nullptr) {
	std::cout << "open file "
			  << "../test/hello.c"
			  << " failed\n";
	return ;
  }
  //需要输出token
  yyout = fopen("token.txt", "w");
  if (yyout == nullptr) {
	std::cout << "open file "
			  << "token.txt"
			  << " failed\n";
	return;
  }
}

auto parser()-> decltype(std::make_shared<Ast>()) {
  static std::shared_ptr<Ast> ast = nullptr;
  if (ast!=nullptr) {
	return ast;
  }
  openFile();
  int result = yyparse(ast);
  assert(!result);
//  fclose(yyin);
//  fclose(yyout);
  return ast;
}
int testParser() {
  openFile();
  auto ast = parser();
  auto visitor = AstVisitor();
  ast->accept(&visitor);
  std::cout << "\n";
  return 0;
}

void testIRCodeGen() {
  openFile();
  auto ast = parser();
  auto visitor = IRGeneratorVisitor();
  ast->accept(&visitor);
  auto ir_code = visitor.programIr;
  auto visitor_default = IrVisitorDefault();
  ir_code->accept(&visitor_default);
}

void testAsmCodeGen() {
  openFile();
  auto ast = parser();
  auto visitor = IRGeneratorVisitor();
  ast->accept(&visitor);
  auto ir_code = visitor.programIr;
  auto asmCodeGen = CodeGenVisitor();
  ir_code->accept(&asmCodeGen);
}