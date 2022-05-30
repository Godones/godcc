//
// Created by linfeng on 2022/3/15.
//
#include "Tparser.h"

//导入文件声明和函数声明
extern FILE *yyin;
extern void file_out(const char *word, const char *type);
extern int yyparse(std::shared_ptr<Ast> &ast);
extern FILE *yyout;



static  std::vector<const char *> file_names = {
	"../test/test1.c",
	"../test/test2.c",
	"../test/test3.c",
	"../test/test4.c",
	"../test/test5.c",
	"../test/test6.c",
	"../test/fab.c",
	"../test/semantic/0_var_not_defined.c",
//	"../test/semantic/correct.c"
	"../test/semantic/1_var_defined_again.c",
	"../test/semantic/2_break_not_in_loop.c",
	"../test/semantic/3_func_arg_not_match.c",
	"../test/semantic/4_opnd_not_match.c",
	"../test/semantic/7_func_lack_of_return.c",
	"../test/dev.c",
	"../test/semantic/while_if_condition_null.c",
	"../test/semantic/correct.c",
	"../test/ir.c",
};

void openFile(const char * file_name){
  INFO("open file:%s",file_name);
  yyin = fopen(file_name, "r");
  if (yyin == nullptr) {
	std::cout << "open file "
			  << file_name
			  << " failed\n";
	exit(-1);
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

auto parser(const char * file_name)-> decltype(std::make_shared<Ast>()) {
  static std::shared_ptr<Ast> ast = nullptr;
  if (ast!=nullptr) {
	return ast;
  }
  openFile(file_name);
  int result = yyparse(ast);
  assert(!result);
  return ast;
}

void test_parse_correct(){
  for (auto &file_name:file_names){
	auto ast = parser(file_name);
	assert(ast);
  }
}


int test_ast_text() {
  auto ast = parser(file_names.back());
  auto visitor = AstVisitor();
  ast->accept(&visitor);
  return 0;
}

void test_ir_gen() {
  auto ast = parser(file_names.back());
  auto semanticVisitor = SemanticVisitor();
  ast->accept(&semanticVisitor);
  auto visitor = IRGeneratorVisitor(semanticVisitor.globalSymbolTable);
  ast->accept(&visitor);
  auto ir_code = visitor.programIr;
  auto visitor_default = IrVisitorDefault();
  ir_code->accept(&visitor_default);
}

//void test_asm_gen() {
//  auto ast = parser(file_names.back());
//  auto semanticVisitor = SemanticVisitor();
//  ast->accept(&semanticVisitor);
//  auto visitor = IRGeneratorVisitor(semanticVisitor.globalSymbolTable);
//  ast->accept(&visitor);
//  auto ir_code = visitor.programIr;
//  auto asmCodeGen = CodeGenVisitor();
//  ir_code->accept(&asmCodeGen);
//}

void test_cst_tree(){

  auto ast = parser(file_names.back());
  GDot json("cst_Tree.dot");
  auto visitor = CstViewVisitor(json);
  ast->accept(&visitor);
}
void test_ast_tree(){

  auto ast = parser(file_names.back());
  GDot json("ast_Tree.dot");
  auto visitor = AstViewVisitor(json);
  ast->accept(&visitor);
}

void test_semantic(){
  auto ast = parser(file_names.back());
  auto visitor = SemanticVisitor();
  ast->accept(&visitor);
  visitor.globalSymbolTable->dump();
}