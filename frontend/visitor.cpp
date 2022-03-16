//
// Created by linfeng on 2022/3/12.
//
#include "visitor.h"
void AstVisitor::VisitCompUnitAst( CompUnitAst* compUnitAst){
    std::cout << "CompUnitAST { ";
    compUnitAst->funcDef->accept(this);
    std::cout << " }";
}
void AstVisitor::VisitFuncDefAst( FuncDefAst* funcDefAst) {
    std::cout << "FuncDefAST { ";
    funcDefAst->funcType->accept(this);
    std::cout <<", ";
    std::cout << funcDefAst->ident;
    std::cout <<", ";
    funcDefAst->block->accept(this);
    std::cout << " }";
}
void AstVisitor::VisitFuncTypeAst( FuncTypeAst* funcTypeAst) {
    std::cout << "FuncType { ";
    std::cout << funcTypeAst->type;
    std::cout << " }";
}

void AstVisitor::VisitBlockAst( BlockAst* blockAst) {
    std::cout << "BlockAst{ ";
    blockAst->stmts->accept(this);
    std::cout << " }";
}
void AstVisitor::VisitStmtAst( StmtAst*stmtAst){
    std::cout << "StmtAst { ";
    std::cout << stmtAst->statement;
    std::cout << " }";
}
void AstVisitor::VisitIdentifierAst( IdentifierAst*identifierAst) {
    std::cout << "IdentifierAst { ";
    std::cout << identifierAst->name;
    std::cout << "}";
}



void IRGeneratorVisitor::VisitCompUnitAst(CompUnitAst * compUnitAst) {
    programIr = std::make_shared<Program>();
    compUnitAst->funcDef->accept(this);
}

void IRGeneratorVisitor::VisitFuncDefAst(FuncDefAst *funcDefAst) {
    Function function;
    function.name = funcDefAst->ident;
    programIr->functions.emplace_back(function);
    funcDefAst->funcType->accept(this);
    funcDefAst->block->accept(this);
}

void IRGeneratorVisitor::VisitFuncTypeAst(FuncTypeAst *funcTypeAst) {
    auto &function = programIr->functions.back();
    if (funcTypeAst->type == "int") {
        function.retType = DataType::Int;
    } else if (funcTypeAst->type == "void") {
        function.retType = DataType::Void;
    }
}

void IRGeneratorVisitor::VisitBlockAst(BlockAst *blockAst) {
    // 函数块生成
    auto &function = programIr->functions.back();
    BaseBlock block;
    block.blockName = "%entry";
    function.blocks.emplace_back(block);//相当于第一个baseblock
    blockAst->stmts->accept(this);
}

void IRGeneratorVisitor::VisitStmtAst(StmtAst *stmtAst) {
    //当前只支持return，因此这里不需要对其进行判断，支持其它语句时这里需要修改
    //
    auto &function = programIr->functions.back();
    auto &block = function.blocks.back();
    int num = std::atoi(stmtAst->statement.c_str());
    // 如果是return语句，则生成一个ret指令
    Instruction instruction;
    instruction.operand = num;
    instruction.instructionType = InstructionType::Return;
    block.instructions.emplace_back(instruction);
}

void IRGeneratorVisitor::VisitIdentifierAst(IdentifierAst *) {
    //标识符，这里暂时不需要
}
