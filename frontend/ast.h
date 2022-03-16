//
// Created by linfeng on 2022/3/11.
//

#ifndef GODCC_AST_H
#define GODCC_AST_H
#include <ostream>
#include <memory>
#include <iostream>
#include "visitor.h"
class Visitor;
class CompUnitAst;
class FuncDefAst;
class FuncTypeAst;
class BlockAst;
class StmtAst;
class IdentifierAst;

class Ast{
public:
    virtual ~Ast() = default;
    virtual void accept(Visitor* ) = 0;
};

class CompUnitAst:public Ast {
public:
    std::shared_ptr<Ast> funcDef;
public:
    ~CompUnitAst() override = default;
    void accept( Visitor *);
};


class FuncDefAst:public Ast {
public:
    std::shared_ptr<Ast> funcType; //类型
    std::string ident;//标识符
//    std::shared_ptr<><Ast> param;//参数
    std::shared_ptr<Ast> block;//函数体
public:
    ~FuncDefAst() override =default;
    void accept( Visitor *) ;
};


class FuncTypeAst:public Ast {
public:
    std::string type;
//    std::shared_ptr<><Ast> param;
public:
    ~FuncTypeAst() override =default;
    void accept( Visitor *) ;
};


class BlockAst:public Ast {
public:
    std::shared_ptr<Ast>stmts;
    ~BlockAst() override =default;
    void accept( Visitor *) ;
};


class StmtAst:public Ast {
public:
    std::string statement;
    ~StmtAst() override =default;
    void accept( Visitor *) ;
};


class IdentifierAst:public Ast {
public:
    std::string name;
public:
    ~IdentifierAst() override =default;
    void accept( Visitor *);
};





#endif //GODCC_AST_H
