//
// Created by linfeng on 2022/3/31.
//

#include "asm.h"
CodeGenVisitor::CodeGenVisitor() {
  out_file.open("../riscv/a.s");
  if (!out_file.is_open()) {
	std::cout << "file a.s can't open\n";
	exit(-1);
  }
}

CodeGenVisitor::CodeGenVisitor(const char *outfile) {
  out_file.open(outfile);
  if (!out_file.is_open()) {
	std::cout << "file"<<outfile<< "can't open\n";
	exit(-1);
  }
}

void CodeGenVisitor::VisitProgram(Program *program) {
  out_file << "\t.text\n";
  out_file << "\t.global main\n";
  for (auto &func : program->functions) {
	func.accept(this);
  }
}

void CodeGenVisitor::VisitFunction(Function *function) {
  out_file << function->name << ":\n";
  for (auto &block : function->blocks) {
	block.accept(this);
  }
}

void CodeGenVisitor::VisitBaseBlock(BaseBlock *baseBlock) {
  for (auto &ins : baseBlock->instructions) {
	ins.accept(this);
  }
}


// 根据指令生成代码
// todo!(代码生成)
void CodeGenVisitor::VisitInstruction(Instruction *instruction) {
  switch (instruction->instructionType) {
	case Integer:
	  //todo!(需要修改立即数的加载和寄存器数的加载)
	  out_file << "	li  "
			   << "t" << instruction->target_register << ", ";
	  if (instruction->operand1.isreg)
		out_file << "t" << instruction->operand1.operand.reg;
	  else
		out_file << instruction->operand1.operand.number;
	  out_file<<"\n";
	  break;
	case Return:
	  out_file << "	mv	 "
			   << "a0, "
			   << "t" << instruction->operand1.operand.reg;
	  out_file << "\n";
	  out_file << "	ret  ";
	  out_file<<"\n";
	  break;
	case Unary:
	  // + - !
	  if (instruction->binaryOp==BinaryOp::Add || instruction->binaryOp==BinaryOp::Sub){
		out_file <<"  "<<toString(instruction->binaryOp)<<"  ";
		out_file <<"t"<<instruction->target_register<<", ";
		out_file <<"x0, ";
		out_file <<"t"<<instruction->operand2.operand.reg;
		out_file <<"\n";
	  }else {
		out_file << "	xor  ";
		out_file << "t" << instruction->target_register << ",";
		out_file << "x0, ";
		out_file << "t" << instruction->operand2.operand.reg;
		out_file<<"\n";
	  }
	case Binary:
	  if(instruction->binaryOp==BinaryOp::Le||instruction->binaryOp==BinaryOp::Ge){
		// 小于等于使用大于来判断，然后在判断其是否等于0
		switch (instruction->binaryOp) {
		  case BinaryOp::Le: // <=
			out_file << "	sgt ";
			break;
		  case BinaryOp::Ge:// >=
			out_file << "	slt ";
			break;
		  default:break;
		}
		out_file << "t"<<instruction->operand1.operand.reg <<", ";
		out_file << "t"<<instruction->operand1.operand.reg <<", ";
		out_file << "t"<<instruction->operand2.operand.reg <<"\n";
		out_file << "	seqz ";
		out_file << "t"<<instruction->target_register <<", t"<<instruction->operand1.operand.reg;
		out_file<<"\n";
	  }else if (instruction->binaryOp==BinaryOp::Eq||instruction->binaryOp==BinaryOp::Ne){
		//== !=
		out_file << "	xor  ";
		out_file << "t" << instruction->operand1.operand.reg <<", "<<"t"<<instruction->operand1.operand.reg<<", ";
		out_file << "t" << instruction->operand2.operand.reg<<"\n";
		if (instruction->binaryOp==BinaryOp::Eq)
		  out_file <<"	seqz  ";
		else
		  out_file <<"	snez  ";
		out_file<< "t" << instruction->target_register << ", "<<"t"<<instruction->operand1.operand.reg;
		out_file<<"\n";
	  }else {
		out_file << "	" << toString(instruction->binaryOp) << " ";
		out_file << "t" << instruction->target_register << ", ";
		// 对于一元运算来说，第一个操作数都是0，使用x0寄存器
		// 其它运算则需要使用其对应的寄存器
		if (!instruction->operand1.isreg&&instruction->operand1.operand.number==0){
		  out_file << "x0, ";
		} else{
		  // 所有的操作数都会被加载到寄存器中
		  assert(instruction->operand1.isreg== true);
		  out_file << "t" <<instruction->operand1.operand.reg<<", ";
		}
		assert(instruction->operand2.isreg== true);
		out_file << "t" << instruction->operand2.operand.reg ;
		out_file<<"\n";
	  }
	default:
	  break;
  }
}
