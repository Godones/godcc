//
// Created by linfeng on 2022/3/10.
//
#include "test/Tparser.h"
#include "frontend/ast_to_ir.h"
#include "frontend/ast_tree_view.h"
#include "frontend/cst_tree_view.h"
#include "semantic.h"
#include "tools/log.h"


void help_info(){
  std::cout << "Usage: ./main [options]\n"
			<< "Options:\n"
			<< "  -h, --help\t\t\tShow this help message and exit\n"
			<< "  -i, --input\t\t\tInput file\n"
			<< "  -dir, --dir\t\t\tOutput directory,default mips\n"
			<< "  -ir,        \t\t\tOutput IR\n"
			<< "  -ast,        \t\t\tOutput AST\n"
			<< "  -cst,        \t\t\tOutput CST\n"
			<< "  -test,       \t\t\tTest\n"
			<< std::endl;
}



int main(int argc, const char *argv[]) {
  INFO("Godcc:");
  for (int i = 0; i < argc; i++) {
	if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
	  help_info();
	  return 0;
	}
	if (strcmp(argv[i],"-test") == 0) {
	  test_asm_gen();
	  return 0;
	}
  }

  std::string input_file;
  std::string output_dir = "../mips/";
  bool is_output_ir = false;
  bool is_output_ast = false;
  bool is_output_cst = false;

  for (int i = 1; i < argc; i++) {
	if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
	  if (i + 1 < argc) {
		i++;
		input_file = argv[i];
	  } else {
		std::cerr << "Error: -i or --input requires an argument." << std::endl;
	  }
	} else if (strcmp(argv[i], "-dir") == 0 || strcmp(argv[i], "--dir") == 0) {
	  if (i + 1 < argc) {
		i++;
		output_dir = std::string(argv[i]) + "/";
	  } else {
		std::cerr << "Error: -dir or --dir requires an argument." << std::endl;
	  }
	} else if (strcmp(argv[i], "-ir") == 0) {
	  is_output_ir = true;
	} else if (strcmp(argv[i], "-ast") == 0) {
	  is_output_ast = true;
	}else if (strcmp(argv[i], "-cst") == 0) {
	  is_output_cst = true;
	} else {
	  std::cerr << "Error: Unknown option: " << argv[i] << std::endl;
	  help_info();
	  return 1;
	}
  }
  if (input_file.empty()) {
	std::cerr << "Error: No input file." << std::endl;
	return 1;
  }

  // 获取文件名称
  std::string file_name_str(input_file);
  auto pos = file_name_str.find_last_of('/');
  auto file_name_without_path = file_name_str.substr(pos + 1);
  auto pos_ = file_name_without_path.find_last_of('.');
  auto file_name_without_extension = file_name_without_path.substr(0, pos_);
  auto filename = file_name_without_extension + ".s";
  auto prefix = output_dir;
  filename  = prefix + filename;

  INFO("Syntax Analysis and Lexical Analysis");
  auto ast = parser(input_file.data());
  if (is_output_cst){
	INFO("Output CST");
	auto cst_name = output_dir + file_name_without_extension + ".cst";
	GDot json(cst_name.c_str());
	auto visitor = CstViewVisitor(json);
	ast->accept(&visitor);
  }
  if (is_output_ast){
	INFO("Output AST");
	auto ast_name = output_dir + file_name_without_extension + ".ast";
	GDot json(ast_name.c_str());
	auto visitor = AstViewVisitor(json);
	ast->accept(&visitor);
  }
  INFO("Semantic Analysis");
  auto semanticVisitor = SemanticVisitor();
  ast->accept(&semanticVisitor); //语义分析
  INFO("IR Generation");
  auto visitor = IRGeneratorVisitor(semanticVisitor.globalSymbolTable);
  ast->accept(&visitor); //中间代码生成
  auto ir_code = visitor.programIr;
  if (is_output_ir){
	INFO("Output IR");
	auto ir_name = output_dir + file_name_without_extension + ".ir";
	auto visitor_default = IrVisitorDefault(ir_name.c_str());
	ir_code->accept(&visitor_default);
  }
  INFO("Asm Generation");
  auto asmCodeGen = CodeGenVisitor(filename.data());
  ir_code->accept(&asmCodeGen);

  return 0;
}
