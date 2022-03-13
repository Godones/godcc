//
// Created by linfeng on 2022/3/11.
//

#include "ast.h"
void CompUnitAst::accept(Visitor *visitor) {
    std::cout << "CompUnitAST { ";
    visitor->VisitCompUnitAst(this);
    std::cout << " }";
}
void FuncDefAst::accept( Visitor *visitor)  {
    std::cout << "FuncDefAST { ";
    visitor->VisitFuncTypeAst(funcType);
    std::cout <<", ";
    std::cout << ident;
    std::cout <<", ";
    visitor->VisitBlockAst(block);
    std::cout << " }";
}
void FuncTypeAst::accept( Visitor *visitor)  {
    std::cout << "FuncType { ";
    std::cout << type;
    std::cout << " }";
}

void BlockAst::accept( Visitor *visitor) {
    std::cout << "BlockAst{";
    visitor->VisitStmtAst(stmts);
    std::cout << "}";
}
void StmtAst::accept( Visitor *visitor)  {
    std::cout << "StmtAst { ";
    std::cout << statement;
    std::cout << "}";
}

void IdentifierAst::accept( Visitor *) {
    std::cout << "IdentifierAst { ";
    std::cout << name;
    std::cout << "}";
}

