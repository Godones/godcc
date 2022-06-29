//
// Created by linfeng on 2022/3/13.
//
#include "irvisitor.h"

#include "tools/log.h"

void IrVisitorDefault::VisitProgram(Program *program) {
  for (auto & instruction : program->global_block->instructions) {
	instruction.accept(this);
  }
  for (auto &func : program->functions) {
	func.accept(this);
  }
  out << "\n";
}

void IrVisitorDefault::VisitFunction(Function *function) {
  out << "fun @" << function->name << ":" << toString(function->retType);
  //参数
  out << "(";
  for (auto &arg : function->params) {
	out << toString(arg.dataType) << ",";
  }
  out << ")";
  out << "{\n";
  for (auto &block : function->blocks) {
	block.accept(this);
  }
  out << "}\n";
}

void IrVisitorDefault::VisitBaseBlock(BaseBlock *block) {
  out << block->blkId << ":\n";
  for (auto &ins : block->instructions) {
	ins.accept(this);
  }
  out << "\n";
}

void IrVisitorDefault::VisitInstruction(Instruction *instruction) {
  // 根据指令类型进行输出
  switch (instruction->instructionType) {
	case InstructionType::Integer:
	  break;
	case InstructionType::Return:
	  out << "ret ";
	  if (instruction->operand1.type == OperandType::kInteger) {
		out << instruction->operand1.operand.number << "\n";
	  } else if (instruction->operand1.type == OperandType::kNumber) {
		out << "%" << instruction->operand1.operand.number << "\n";
	  } else {
		out << "\n";
	  }
	  break;
	case InstructionType::Alloc:{
	  out << "@" << instruction->operand1.operand.symbol << " = alloc " << toString(instruction->dataType) << " ";
	  if (instruction->array_dim.size() != 0) {//数组
		out << "array ";
		out << "[";
		for (auto &dim : instruction->array_dim) {
		  out << dim << ",";
		}
		out << "]";
	  }
	  auto next = instruction->next;
	  if (!next) {
		out << "\n";
		break ;
	  }
	  if (instruction->array_dim.size() != 0) {//数组
		out << " {";
		for (auto &dim : next->array_dim) {
		  out << dim << ",";
		}
		out << "}";
	  } else {
		out <<  next->array_dim[0];
	  }
	  out << "\n";
	  break;
	}
	case InstructionType::GlobalString:{
	  out << "@" << instruction->operand1.operand.symbol << " = " << instruction->operand2.operand.symbol << "\n";
	  break ;
	}
	case InstructionType::GlobalAlloc: {
	  out << "@" << instruction->operand1.operand.symbol << " = global " << toString(instruction->dataType) << " ";
	  if (!instruction->array_dim.empty()) {//数组
		out << "array ";
		out << "[";
		for (auto &dim : instruction->array_dim) {
		  out << dim << ",";
		}
		out << "]";
	  }
	  auto next = instruction->next;
	  assert(next);
	  if (!instruction->array_dim.empty()) {//数组
		out << " {";
		for (auto &dim : next->array_dim) {
		  out << dim << ",";
		}
		out << "}";
	  } else {
		out <<  next->array_dim[0];
	  }
	  out << "\n";
	  break;
	}
	case InstructionType::Store:
	  out << "store " << "i32" << " ";
	  if (instruction->operand1.type == OperandType::kInteger) {
		out << instruction->operand1.operand.number << ",";
	  }
	  if (instruction->operand1.type == OperandType::kNumber) {
		out << "%" << instruction->operand1.operand.number << ",";
	  }
	  if (instruction->operand2.type == OperandType::kString) {
	  	out << instruction->operand2.operand.symbol << "\n";
	  } else{
	  	out << "%" << instruction->operand2.operand.number << "\n";
	  }
	  break;

	case InstructionType::Load:
	  out << "%" << instruction->m_number << " = load " << " ";
	  if (instruction->operand1.type==OperandType::kNumber) {
		out << "%" << instruction->operand1.operand.number ;
	  }else{
		out << "@" << instruction->operand1.operand.symbol;
	  }
	  out << "\n";
	  break;
	case InstructionType::Binary: {
	  auto print_operand = [&](Operand &operand) {
		if (operand.type == OperandType::kNumber)
		  out << "%" << operand.operand.number;
		else if (operand.type == OperandType::kInteger)
		  out << operand.operand.number;
	  };
	  out << "%" << instruction->m_number << " = ";
	  out << toString(instruction->binaryOp);
	  print_operand(instruction->operand1);
	  out << ", ";
	  print_operand(instruction->operand2);
	  out << "\n";
	  break;
	}
	case InstructionType::Jump: {
	  out << "jmp "
				<< "label " << instruction->operand1.operand.number << "\n";
	  break;
	}
	case InstructionType::Branch: {
	  out << "br "
				<< "%" << instruction->operand1.operand.number << ", ";
	  out << "label " << instruction->operand2.operand.number << ", ";
	  out << "label " << instruction->operand3.operand.number << "\n";
	  break;
	}
	case InstructionType::Call: {
	  if (instruction->m_number != -1) {
		out << "%" << instruction->m_number << " = ";
	  }
	  out << "call " << instruction->name << "(";
	  for (auto &fp : instruction->extra) {
		if (fp.operand1.type == OperandType::kInteger) {
		  out << "i32 " << fp.operand1.operand.number << ",";
		} else if (fp.operand1.type == OperandType::kNumber) {
		  out << "%" << fp.operand1.operand.number << ",";
		} else if (fp.operand1.type==OperandType::kString){
		  out << fp.operand1.operand.symbol << ",";
		}
	  }
	  out << ")\n";
	  break ;
	}
	case InstructionType::GetElementPtr:{
	  out << "%" << instruction->m_number << " = ";
	  out << "getelementptr ";
	  if (instruction->operand1.type==OperandType::kString) {
		out << "@" <<instruction->operand1.operand.symbol;
	  }else if(instruction->operand1.type==OperandType::kNumber){
		out << "%" << instruction->operand1.operand.number;
	  }
	  out << ", ";
	  if (instruction->operand2.type==OperandType::kNumber){
		out << "%";
	  }
	  out <<instruction->operand2.operand.number;
	  out << "*";
	  out << instruction->operand3.operand.number << "\n";
	  break;
	}
	case InstructionType::Move:{
	  out << "";
	  break ;
	}
	default:
	  break;
  }
}
IrVisitorDefault::IrVisitorDefault(std::string &&filename) {
  out.open(filename);
  if (!out.is_open()) {
    std::cerr << "open file error" << std::endl;
  }
}
IrVisitorDefault::IrVisitorDefault() {
  out.open("../mips/a.ir");
  if (!out.is_open()) {
    std::cerr << "open file error" << std::endl;
  }
}
