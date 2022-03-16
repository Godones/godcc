//
// Created by linfeng on 2022/3/13.
//
#include "../log/log.h"
#include "irvisitor.h"
void IrVisitorDefault::VisitProgram( Program*program){
    for(auto&func:program->functions){
        func.accept(this);
    }
    std::cout<<"\n";
}
void IrVisitorDefault::VisitFunction(Function *function){
    std::cout << "fun @" << function->name << ":" << toString(function->retType)<<"{\n";
    for (auto&block:function->blocks) {
        block.accept(this);
    }
    std::cout << "}";
}
void IrVisitorDefault::VisitBaseBlock( BaseBlock* block){
    std::cout << block->blockName << ":\n";
    for (auto &ins:block->instructions) {
        ins.accept(this);
    }
}
void IrVisitorDefault::VisitInstruction(Instruction* instruction) {
    std::cout << toString(instruction->instructionType) << " ";
    std::cout << instruction->operand ;
    std::cout << "\n";
}