//
// Created by linfeng on 2022/3/12.
//
#include "visitor.h"

void AstVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
    compUnitAst->printSpace();
    std::cout << "CompUnitAST <> \n";
    compUnitAst->funcDef->setSpaces(compUnitAst->spaces+1);
    compUnitAst->funcDef->accept(this);
}

void AstVisitor::VisitFuncDefAst(FuncDefAst *funcDefAst) {
    funcDefAst->printSpace();
    std::cout << "FuncDefAST <> ";
    funcDefAst->funcType->accept(this);
    std::cout << funcDefAst->ident << "\n";
    funcDefAst->block->setSpaces(funcDefAst->spaces+1);
    funcDefAst->block->accept(this);
}

void AstVisitor::VisitFuncTypeAst(FuncTypeAst *funcTypeAst) {
    std::cout << funcTypeAst->type << " ";
}

void AstVisitor::VisitBlockAst(BlockAst *blockAst) {
    blockAst->printSpace();
    std::cout << "BlockAst <>\n";
    blockAst->stmts->setSpaces(blockAst->spaces+1);
    blockAst->stmts->accept(this);
}

void AstVisitor::VisitStmtAst(StmtAst *stmtAst) {
    stmtAst->printSpace();
    std::cout << "StmtAst <>\n";
    stmtAst->expr->setSpaces(stmtAst->spaces+1);
    stmtAst->expr->accept(this);
}

void AstVisitor::VisitIdentifierAst(IdentifierAst *identifierAst) {
    identifierAst->printSpace();
    std::cout << "IdentifierAst:\n ";
    std::cout << identifierAst->name;
}

void AstVisitor::VisitExp(ExpAst *expAst) {
    expAst->printSpace();
    if (expAst->expType == ExpAst::ExpType::UNARY){
        std::cout << "UnaryExpAst <>\n";
        expAst->realExpr->setSpaces(expAst->spaces+1);
        expAst->realExpr->accept(this);
    }
}

void AstVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
    unaryExprAst->printSpace();
    if (unaryExprAst->unaryType == UnaryExprAst::UnaryType::UNARY) {
        std::cout << "Op UnaryExpAst <> ";
        unaryExprAst->unaryOp->accept(this);//一元运算符号
        std::cout << "\n";
        unaryExprAst->unaryExpr->setSpaces(unaryExprAst->spaces+1);
        unaryExprAst->unaryExpr->accept(this);
    } else {
        std::cout << "Primary UnaryExpAst <> \n";
        unaryExprAst->unaryExpr->setSpaces(unaryExprAst->spaces+1);
        unaryExprAst->unaryExpr->accept(this);
    }
}

void AstVisitor::VisitBinaryExpAst(BinaryExprAst *) {

}

void AstVisitor::VisitUnaryOpAst(UnaryOpAst *unaryOpAst) {
    std::cout  << unaryOpAst->op;
}

void AstVisitor::VisitPrimaryExpAst(PrimaryExprAst *primaryExprAst) {
    primaryExprAst->printSpace();
    if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::EXP) {
        std::cout << "Exp PrimaryExpAst <> ()\n";
        primaryExprAst->primaryExpr->setSpaces(primaryExprAst->spaces+1);
        primaryExprAst->primaryExpr->accept(this);
    } else if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::NUMBER) {

        std::cout << "Number PrimaryExpAst <>\n";
        primaryExprAst->primaryExpr->setSpaces(primaryExprAst->spaces+1);
        primaryExprAst->primaryExpr->accept(this);
    }
}

void AstVisitor::VisitNumberAst(NumberAst *numberAst) {
    numberAst->printSpace();
    std::cout << "NumberAst <> "<< numberAst->value << "\n";
}





void IRGeneratorVisitor::VisitCompUnitAst(CompUnitAst *compUnitAst) {
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
    // 第一步 解析return语句中的表达式
    stmtAst->expr->accept(this);
    // 建立一个ret指令
    Instruction instruction;
//    instruction.operand1 = num;
    instruction.instructionType = InstructionType::Return;
    block.instructions.emplace_back(instruction);
}

void IRGeneratorVisitor::VisitExp(ExpAst *expAst) {
    expAst->realExpr->accept(this);
}

void IRGeneratorVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
    // 获得最后一个base_block
    auto &function = programIr->functions.back();
    auto &block = function.blocks.back();
    block.instructions.emplace_back(Instruction());
    auto &instruction = block.instructions.back();
    if (unaryExprAst->unaryType == UnaryExprAst::UnaryType::UNARY) {
        // 对于一元运算符，需要生成一个指令
        // 如 -5 / -(?)
        // 先解析符号后面的表达式
        unaryExprAst->unaryExpr->accept(this);
        unaryExprAst->unaryOp->accept(this);//一元运算符号
//        instruction.operand1 = 0;

    } else {
        std::cout << "Primary UnaryExpAst:\n ";
        unaryExprAst->unaryExpr->accept(this);
    }
}

void IRGeneratorVisitor::VisitBinaryExpAst(BinaryExprAst *) {
    auto &function = programIr->functions.back();
    auto &block = function.blocks.back();
    auto &instruction = block.instructions.back();
    instruction.instructionType = InstructionType::Binary;
}

void IRGeneratorVisitor::VisitUnaryOpAst(UnaryOpAst *unaryOpAst) {
    // 所有的一元运算符可以转化为二元运算符
    auto &function = programIr->functions.back();
    auto &block = function.blocks.back();
    auto &instruction = block.instructions.back();
    instruction.instructionType = InstructionType::Binary;
}

void IRGeneratorVisitor::VisitPrimaryExpAst(PrimaryExprAst *primaryExprAst) {
    if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::EXP) {

    } else if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::NUMBER) {
    }
}

void IRGeneratorVisitor::VisitNumberAst(NumberAst *numberAst) {

}


void IRGeneratorVisitor::VisitIdentifierAst(IdentifierAst *) {
    //标识符，这里暂时不需要
}
