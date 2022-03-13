//
// Created by linfeng on 2022/3/12.
//
#include "visitor.h"
void AstVisitor::VisitCompUnitAst( CompUnitAst* compUnitAst){
    std::cout << "CompUnitAST { ";
    compUnitAst->accept(compUnitAst->funcDef);
    std::cout << " }";
}
void AstVisitor::VisitFuncDefAst( FuncDefAst* funcDefAst) {
    funcDefAst->accept(this);
}
void AstVisitor::VisitFuncTypeAst( FuncTypeAst* funcTypeAst) {
    funcTypeAst->accept(this);
}

void AstVisitor::VisitBlockAst( BlockAst* blockAst) {
    blockAst->accept(this);
}
void AstVisitor::VisitStmtAst( StmtAst*stmtAst){
    stmtAst ->accept(this);
}
void AstVisitor::VisitIdentifierAst( IdentifierAst*identifierAst) {
    identifierAst->accept(this);
}

