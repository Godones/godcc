//
// Created by linfeng on 2022/3/13.
//
#include "irvisitor.h"

#include "tools/log.h"

void IrVisitorDefault::VisitProgram(Program *program) {
  for (int i = 0; i < program->global_block->instructions.size(); i++) {
	program->global_block->instructions[i].accept(this);
  }
  for (auto &func : program->functions) {
	func.accept(this);
  }
  std::cout << "\n";
}

void IrVisitorDefault::VisitFunction(Function *function) {
  std::cout << "fun @" << function->name << ":" << toString(function->retType);
  //参数
  std::cout << "(";
  for (auto &arg : function->params) {
	std::cout << toString(arg.dataType) << ",";
  }
  std::cout << ")";
  std::cout << "{\n";
  for (auto &block : function->blocks) {
	block.accept(this);
  }
  std::cout << "}\n";
}

void IrVisitorDefault::VisitBaseBlock(BaseBlock *block) {
  std::cout << block->blkId << ":\n";
  for (auto &ins : block->instructions) {
	ins.accept(this);
  }
  std::cout << "\n";
}

void IrVisitorDefault::VisitInstruction(Instruction *instruction) {
  // 根据指令类型进行输出
  switch (instruction->instructionType) {
	case InstructionType::Integer:
	  break;
	case InstructionType::Return:
	  std::cout << "ret ";
	  if (instruction->operand1.type == OperandType::kInteger) {
		std::cout << instruction->operand1.operand.number << "\n";
	  } else if (instruction->operand1.type == OperandType::kNumber) {
		std::cout << "%" << instruction->operand1.operand.number << "\n";
	  } else {
		std::cout << "\n";
	  }
	  break;
	case InstructionType::Alloc:{
	  std::cout << "@" << instruction->operand1.operand.symbol << " = alloc " << toString(instruction->dataType) << " ";
	  if (instruction->array_dim.size() != 0) {//数组
		std::cout << "array ";
		std::cout << "[";
		for (auto &dim : instruction->array_dim) {
		  std::cout << dim << ",";
		}
		std::cout << "]";
	  }
	  auto next = instruction->next;
	  if (!next) {
		std::cout << "\n";
		break ;
	  }
	  if (instruction->array_dim.size() != 0) {//数组
		std::cout << " {";
		for (auto &dim : next->array_dim) {
		  std::cout << dim << ",";
		}
		std::cout << "}";
	  } else {
		std::cout <<  next->array_dim[0];
	  }
	  std::cout << "\n";
	  break;
	}
	case InstructionType::GlobalString:{
	  std::cout << "@" << instruction->operand1.operand.symbol << " = " << instruction->operand2.operand.symbol << "\n";
	  break ;
	}
	case InstructionType::GlobalAlloc: {
	  std::cout << "@" << instruction->operand1.operand.symbol << " = global " << toString(instruction->dataType) << " ";
	  if (instruction->array_dim.size() != 0) {//数组
		std::cout << "array ";
		std::cout << "[";
		for (auto &dim : instruction->array_dim) {
		  std::cout << dim << ",";
		}
		std::cout << "]";
	  }
	  auto next = instruction->next;
	  assert(next);
	  if (instruction->array_dim.size() != 0) {//数组
		std::cout << " {";
		for (auto &dim : next->array_dim) {
		  std::cout << dim << ",";
		}
		std::cout << "}";
	  } else {
		std::cout <<  next->array_dim[0];
	  }
	  std::cout << "\n";
	  break;
	}
	case InstructionType::Store:
	  std::cout << "store " << "i32" << " ";
	  if (instruction->operand1.type == OperandType::kInteger) {
		std::cout << instruction->operand1.operand.number << ",";
	  }
	  if (instruction->operand1.type == OperandType::kNumber) {
		std::cout << "%" << instruction->operand1.operand.number << ",";
	  }
	  if (instruction->operand2.type == OperandType::kString) {
	  	std::cout << instruction->operand2.operand.symbol << "\n";
	  } else{
	  	std::cout << "%" << instruction->operand2.operand.number << "\n";
	  }
	  break;

	case InstructionType::Load:
	  std::cout << "%" << instruction->m_number << " = load " << " ";
	  if (instruction->operand1.type==OperandType::kNumber) {
		std::cout << "%" << instruction->operand1.operand.number ;
	  }else{
		std::cout << "@" << instruction->operand1.operand.symbol;
	  }
	  std::cout << "\n";
	  break;
	case InstructionType::Binary: {
	  auto print_operand = [](Operand &operand) {
		if (operand.type == OperandType::kNumber)
		  std::cout << "%" << operand.operand.number;
		else if (operand.type == OperandType::kInteger)
		  std::cout << operand.operand.number;
	  };
	  std::cout << "%" << instruction->m_number << " = ";
	  std::cout << toString(instruction->binaryOp);
	  print_operand(instruction->operand1);
	  std::cout << ", ";
	  print_operand(instruction->operand2);
	  std::cout << "\n";
	  break;
	}
	case InstructionType::Jump: {
	  std::cout << "jmp "
				<< "label " << instruction->operand1.operand.number << "\n";
	  break;
	}
	case InstructionType::Branch: {
	  std::cout << "br "
				<< "%" << instruction->operand1.operand.number << ", ";
	  std::cout << "label " << instruction->operand2.operand.number << ", ";
	  std::cout << "label " << instruction->operand3.operand.number << "\n";
	  break;
	}
	case InstructionType::Call: {
	  if (instruction->m_number != -1) {
		std::cout << "%" << instruction->m_number << " = ";
	  }
	  std::cout << "call " << instruction->name << "(";
	  for (auto &fp : instruction->extra) {
		if (fp.operand1.type == OperandType::kInteger) {
		  std::cout << "i32 " << fp.operand1.operand.number << ",";
		} else if (fp.operand1.type == OperandType::kNumber) {
		  std::cout << "%" << fp.operand1.operand.number << ",";
		} else if (fp.operand1.type==OperandType::kString){
		  std::cout << fp.operand1.operand.symbol << ",";
		}
	  }
	  std::cout << ")\n";
	  break ;
	}
	case InstructionType::GetElementPtr:{
	  std::cout << "%" << instruction->m_number << " = ";
	  std::cout << "getelementptr ";
	  if (instruction->operand1.type==OperandType::kString) {
		std::cout << "@" <<instruction->operand1.operand.symbol;
	  }else if(instruction->operand1.type==OperandType::kNumber){
		std::cout << "%" << instruction->operand1.operand.number;
	  }
	  std::cout << ", ";
	  if (instruction->operand2.type==OperandType::kNumber){
		std::cout << "%";
	  }
	  std::cout <<instruction->operand2.operand.number;
	  std::cout << "\n";
	  break;
	}
	case InstructionType::Move:{
	  std::cout << "";
	  break ;
	}
	default:
	  break;
  }
}
