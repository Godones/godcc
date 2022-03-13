//
// Created by linfeng on 2022/3/12.
//

#ifndef GODCC_VISITOR_H
#define GODCC_VISITOR_H
#include "ast.h"

class CompUnitAst;
class FuncDefAst;
class FuncTypeAst;
class BlockAst;
class StmtAst;
class IdentifierAst;
class Visitor {
public:
    virtual void VisitCompUnitAst( CompUnitAst*) =0;
    virtual void VisitFuncDefAst( FuncDefAst*) =0;
    virtual void VisitFuncTypeAst( FuncTypeAst*) = 0;
    virtual void VisitBlockAst(BlockAst*) = 0;
    virtual void VisitStmtAst(StmtAst*) = 0;
    virtual void VisitIdentifierAst( IdentifierAst*) = 0;
};

class AstVisitor : public Visitor {
public:
    void VisitCompUnitAst( CompUnitAst*) override;
    void VisitFuncDefAst( FuncDefAst*)  override;
    void VisitFuncTypeAst( FuncTypeAst*)  override;
    void VisitBlockAst( BlockAst*) override;
    void VisitStmtAst( StmtAst*) override;
    void VisitIdentifierAst( IdentifierAst*) override;
};
#endif //GODCC_VISITOR_H
