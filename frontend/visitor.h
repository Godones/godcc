//
// Created by linfeng on 2022/3/12.
//

#ifndef GODCC_VISITOR_H
#define GODCC_VISITOR_H
#include "ast.h"
#include "../IR/IR.h"
#include "../log/log.h"
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

// 符号表建立
class BuildSymbolVisitor : public Visitor {
public:
    void VisitCompUnitAst( CompUnitAst*) override;
    void VisitFuncDefAst( FuncDefAst*)  override;
    void VisitFuncTypeAst( FuncTypeAst*)  override;
    void VisitBlockAst( BlockAst*) override;
    void VisitStmtAst( StmtAst*) override;
    void VisitIdentifierAst( IdentifierAst*) override;
};

// 中间代码生成
class IRGeneratorVisitor : public Visitor {
public:
    std::shared_ptr<Program> programIr = nullptr;
public:
    void VisitCompUnitAst( CompUnitAst*) override;
    void VisitFuncDefAst( FuncDefAst*)  override;
    void VisitFuncTypeAst( FuncTypeAst*)  override;
    void VisitBlockAst( BlockAst*) override;
    void VisitStmtAst( StmtAst*) override;
    void VisitIdentifierAst( IdentifierAst*) override;
};
#endif //GODCC_VISITOR_H
