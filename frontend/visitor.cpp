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
    if (expAst->expType == ExpAst::ExpType::UNARY)
        std::cout << "UnaryExpAst <>\n";
    expAst->realExpr->setSpaces(expAst->spaces+1);
    expAst->realExpr->accept(this);
}

void AstVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
    unaryExprAst->printSpace();
    if (unaryExprAst->unaryType == UnaryExprAst::UnaryType::UNARY) {
        std::cout << "Op UnaryExpAst <> ";
        unaryExprAst->unaryExpr->unaryOp->accept(this);//一元运算符号
        std::cout << "\n";
        unaryExprAst->unaryExpr->unaryExpr->setSpaces(unaryExprAst->spaces+1);
        unaryExprAst->unaryExpr->unaryExpr->accept(this);
    } else {
        std::cout << "Primary UnaryExpAst <> \n";
        unaryExprAst->primaryExp->setSpaces(unaryExprAst->spaces+1);
        unaryExprAst->primaryExp->accept(this);
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
        primaryExprAst->exp->setSpaces(primaryExprAst->spaces+1);
        primaryExprAst->exp->accept(this);
    } else if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::NUMBER) {

        std::cout << "Number PrimaryExpAst <>\n";
        primaryExprAst->number->setSpaces(primaryExprAst->spaces+1);
        primaryExprAst->number->accept(this);
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
    Instruction instruction;
    instruction.operand = num;
    instruction.instructionType = InstructionType::Return;
    block.instructions.emplace_back(instruction);
}

void IRGeneratorVisitor::VisitExp(ExpAst *expAst) {
    if (expAst->expType == ExpAst::ExpType::UNARY)
        std::cout << "UnaryExpAst:\n ";
    expAst->realExpr->accept(this);
}

void IRGeneratorVisitor::VisitUnaryExpAst(UnaryExprAst *unaryExprAst) {
    if (unaryExprAst->unaryType == UnaryExprAst::UnaryType::UNARY) {
        std::cout << "Op UnaryExpAst:\n ";
        unaryExprAst->unaryExpr->unaryOp->accept(this);//一元运算符号
        unaryExprAst->unaryExpr->unaryExpr->accept(this);
    } else {
        std::cout << "Primary UnaryExpAst:\n ";
        unaryExprAst->primaryExp->accept(this);
    }
}

void IRGeneratorVisitor::VisitBinaryExpAst(BinaryExprAst *) {

}

void IRGeneratorVisitor::VisitUnaryOpAst(UnaryOpAst *unaryOpAst) {
    std::cout << "UnaryOpAst:" << unaryOpAst->op << "\n ";
}

void IRGeneratorVisitor::VisitPrimaryExpAst(PrimaryExprAst *primaryExprAst) {
    if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::EXP) {
        std::cout << "Exp PrimaryExpAst:\n ";
        std::cout << "(";
        primaryExprAst->exp->accept(this);
        std::cout << ")";
    } else if (primaryExprAst->primaryType == PrimaryExprAst::PrimaryType::NUMBER) {
        std::cout << "Number PrimaryExpAst:\n ";
        primaryExprAst->number->accept(this);
    }
}

void IRGeneratorVisitor::VisitNumberAst(NumberAst *numberAst) {
    std::cout << "NumberAst:\n ";
    std::cout << numberAst->value;
}


void IRGeneratorVisitor::VisitIdentifierAst(IdentifierAst *) {
    //标识符，这里暂时不需要
}
