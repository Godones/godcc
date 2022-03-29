%code requires {
  #include <memory>
  #include <string>
  #include "ast.h"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include "ast.h"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::shared_ptr<Ast> &ast, const char *s);
using namespace std;

%}

// 定义 parser 函数和错误处理函数的附加参数
// 我们需要返回一个字符串作为 AST, 所以我们把附加参数定义成字符串的智能指针
// 解析完成后, 我们要手动修改这个参数, 把它设置成解析的得到字符串
%parse-param { std::shared_ptr<Ast> &ast }

// yylval 的定义, 我们把它定义成了一个联合体 (union)
// 因为 token 的值有的是字符串指针, 有的是整数
// 之前我们在 lexer 中用到的 str_val 和 int_val 就是在这里被定义的
// 至于为什么要用字符串指针而不直接用 string 或者 shared_ptr<string>?
// 请自行 STFW 在 union 里写一个带析构函数的类会出现什么情况
%union {
  std::string *str_val;
  int int_val;
  Ast *ast_val;
}

// lexer 返回的所有 token 种类的声明
// 注意 IDENT 和 INT_CONST 会返回 token 的值, 分别对应 str_val 和 int_val
%token INT RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST

// 非终结符的类型定义
%type <ast_val> FuncDef FuncType Block Stmt Expr UnaryExp PrimaryExpr Number UnaryOp
%type <ast_val> AddExpr MulExpr
//%type <int_val>
//%type <str_val>
%%

// 开始符, CompUnit ::= FuncDef, 大括号后声明了解析完成后 parser 要做的事情
// 之前我们定义了 FuncDef 会返回一个 str_val, 也就是字符串指针
// 而 parser 一旦解析完 CompUnit, 就说明所有的 token 都被解析了, 即解析结束了
// 此时我们应该把 FuncDef 返回的结果收集起来, 作为 AST 传给调用 parser 的函数
// $1 指代规则里第一个符号的返回值, 也就是 FuncDef 的返回值
CompUnit
  : FuncDef {
    auto compUnit = make_shared<CompUnitAst>();
    compUnit->funcDef = shared_ptr<Ast>($1);
    ast = compUnit;
  }
  ;

// FuncDef ::= FuncType IDENT '(' ')' Block;
// 我们这里可以直接写 '(' 和 ')', 因为之前在 lexer 里已经处理了单个字符的情况
// 解析完成后, 把这些符号的结果收集起来, 然后拼成一个新的字符串, 作为结果返回
// $$ 表示非终结符的返回值, 我们可以通过给这个符号赋值的方法来返回结果
// 你可能会问, FuncType, IDENT 之类的结果已经是字符串指针了
// 为什么还要用 shared_ptr 接住它们, 然后再解引用, 把它们拼成另一个字符串指针呢
// 因为所有的字符串指针都是我们 new 出来的, new 出来的内存一定要 delete
// 否则会发生内存泄漏, 而 shared_ptr 这种智能指针可以自动帮我们 delete
// 虽然此处你看不出用 shared_ptr 和手动 delete 的区别, 但当我们定义了 AST 之后
// 这种写法会省下很多内存管理的负担
FuncDef
  : FuncType IDENT '(' ')' Block {
  	auto funcDef = new FuncDefAst();
	funcDef->funcType = shared_ptr<Ast>($1);
	funcDef->ident = *shared_ptr<string>($2);
	funcDef->block = shared_ptr<Ast>($5);
	$$ = funcDef;
  }
  ;

// 同上, 不再解释
FuncType
  : INT {
    auto funcType = new FuncTypeAst();
    funcType->type = string("int");
    $$ = funcType;
  }
  ;

Block
  : '{' Stmt '}' {
    auto block = new BlockAst();
    block->stmts = shared_ptr<Ast>($2);
    $$ = block;
  }
  ;

Stmt
  : RETURN Expr ';' {
    auto stmt = new StmtAst();
    stmt->expr = shared_ptr<Ast>($2);
    $$ = stmt;
  }
  ;

Expr
  : AddExpr {
    auto Expr = new ExpAst();
    Expr->realExpr = shared_ptr<Ast>($1);
    $$ = Expr;
  }
;

AddExpr
:MulExpr {
  $$ = new AddExprAst( shared_ptr<Ast>($1));
}
|AddExpr '+' MulExpr{
  $$ = new AddExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"+");
}
|AddExpr '-' MulExpr{
$$ = new AddExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"-");
};

MulExpr
:UnaryExp{
  $$ = new MulExprAst(shared_ptr<Ast>($1));
}
|MulExpr '*' UnaryExp{
$$ = new MulExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"*");
}
|MulExpr '/' UnaryExp{
$$ = new MulExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"/");
}
|MulExpr '%' UnaryExp{
$$ = new MulExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"%");
}
;


UnaryExp
  : PrimaryExpr {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp-> unaryExpr = shared_ptr<Ast>($1);
  	unaryExp->unaryType = UnaryExprAst::UnaryType::PRIMARY;
  	$$ = unaryExp;
  }
  |UnaryOp UnaryExp{
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>($1);
        unaryExp->unaryExpr = shared_ptr<Ast>($2);
	unaryExp->unaryType = UnaryExprAst::UnaryType::UNARY;
	$$ = unaryExp;
  }
;

PrimaryExpr
  : '(' Expr ')' {
  auto primaryAst = new PrimaryExprAst();
  primaryAst->primaryExpr = shared_ptr<Ast>($2);
  primaryAst->primaryType = PrimaryExprAst::PrimaryType::EXP;
  $$ = primaryAst;
  }
  |Number {
  auto primaryAst = new PrimaryExprAst();
    primaryAst->primaryExpr = shared_ptr<Ast>($1);
    primaryAst->primaryType = PrimaryExprAst::PrimaryType::NUMBER;
    $$ = primaryAst;
  }
;

UnaryOp
 : '+' {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "+";
   $$ = unaryOpAst;
 }
 | '-' {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "-";
   $$ = unaryOpAst;
 }
 | '!' {
  auto unaryOpAst = new UnaryOpAst();
  unaryOpAst->op = "!";
  $$ = unaryOpAst;
 }
 ;

Number
  : INT_CONST {
  auto numberAst = new NumberAst();
  numberAst->value = ($1);
  $$ = numberAst;
  }
  ;

%%

// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(shared_ptr<Ast> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
