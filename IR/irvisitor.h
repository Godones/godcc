//
// Created by linfeng on 2022/3/13.
//

#ifndef GODCC_IRVISITOR_H
#define GODCC_IRVISITOR_H
#include "IR.h"

struct Program;
struct Function;
struct BaseBlock;
struct Instruction;

class IrVisitor {
public:
    virtual void VisitProgram(Program*) =0;
    virtual void VisitFunction( Function*) =0;
    virtual void VisitBaseBlock( BaseBlock*) = 0;
    virtual void VisitInstruction(Instruction*) = 0;
};

class IrVisitorDefault : public IrVisitor {
public:
    void VisitProgram( Program*) override ;
    void VisitFunction( Function*) override;
    void VisitBaseBlock( BaseBlock*) override;
    void VisitInstruction(Instruction*) override;
};
#endif //GODCC_IRVISITOR_H
