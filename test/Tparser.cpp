//
// Created by linfeng on 2022/3/15.
//
#include "Tparser.h"

//导入文件声明和函数声明
extern FILE *yyin;
extern void file_out(const char *word, const char *type);
extern int yyparse(std::shared_ptr<Ast> &ast);
extern FILE *yyout;

static std::vector<const char *> file_names = {
//	"../test/mytest/test1.c",
//	"../test/mytest/test2.c",
//	"../test/mytest/test3.c",
//	"../test/mytest/test4.c",
//	"../test/mytest/test5.c",
//	"../test/mytest/test6.c",
//	"../test/mytest/fab.c",
//	"../test/semantic/0_var_not_defined.c",
//	"../test/semantic/1_var_defined_again.c",
//	"../test/semantic/2_break_not_in_loop.c",
//	"../test/semantic/3_func_arg_not_match.c",
//	"../test/semantic/4_opnd_not_match.c",
//	"../test/semantic/7_func_lack_of_return.c",
//	"../test/mytest/dev.c",
//	"../test/semantic/while_if_condition_null.c",
//	"../test/semantic/correct.c",
//	"../test/mytest/ir.c",
//	"../test/mytest/array.c",
	"../test/nc_tests/0_BubbleSort.c",
	"../test/nc_tests/1_Fibonacci.c",
	"../test/nc_tests/2_Prime.c",
	"../test/nc_tests/3_PerfectNumber.c",
	"../test/nc_tests/4_CounterClockwiseRotationArray4_4.c",
	"../test/nc_tests/5_YangHuiTriangle.c",
	"../test/nc_tests/6_QuickSort.c",
	"../test/nc_tests/7_Dijkstra.c",
};

void openFile(const char *file_name) {
  INFO("open file:%s", file_name);
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

auto parser(const char *file_name) -> decltype(std::make_shared<Ast>()) {
  std::shared_ptr<Ast> ast = nullptr;
  openFile(file_name);
  int result = yyparse(ast);
  assert(!result);
  return ast;
}

void test_parse_correct() {
  for (auto &file_name : file_names) {
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
  semanticVisitor.globalSymbolTable->dump();
  std::cout << "-------------------------------------------------------\n";
  auto visitor = IRGeneratorVisitor(semanticVisitor.globalSymbolTable);
  ast->accept(&visitor);
  auto ir_code = visitor.programIr;
  auto visitor_default = IrVisitorDefault();
  ir_code->accept(&visitor_default);
}

void test_asm_gen() {
  for(auto &file_name : file_names) {
	auto ast = parser(file_name);
	auto semanticVisitor = SemanticVisitor();
	ast->accept(&semanticVisitor);
	auto visitor = IRGeneratorVisitor(semanticVisitor.globalSymbolTable);
	ast->accept(&visitor);
	auto ir_code = visitor.programIr;
	// 获取文件名称
	std::string file_name_str(file_name);
	auto pos = file_name_str.find_last_of('/');
	auto file_name_without_path = file_name_str.substr(pos + 1);
	auto pos_ = file_name_without_path.find_last_of('.');
	auto file_name_without_extension = file_name_without_path.substr(0, pos_);
	auto filename = file_name_without_extension + ".s";
	auto prefix = "../mips/";
	filename  = prefix + filename;
	auto asmCodeGen = CodeGenVisitor(filename.data());
	ir_code->accept(&asmCodeGen);
  }
}

void test_cst_tree() {
  auto ast = parser(file_names.back());
  GDot json("cst_Tree.dot");
  auto visitor = CstViewVisitor(json);
  ast->accept(&visitor);
}
void test_ast_tree() {
  auto ast = parser(file_names.back());
  GDot json("ast_Tree.dot");
  auto visitor = AstViewVisitor(json);
  ast->accept(&visitor);
}

void test_semantic() {
  auto ast = parser(file_names.back());
  auto visitor = SemanticVisitor();
  ast->accept(&visitor);
  visitor.globalSymbolTable->dump();
}