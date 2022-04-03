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
%token RETURN
%token <str_val> IDENT LT GT EQ AND OR NE LE GE CONST INT
%token <int_val> INT_CONST
//Lt,//<
//Gt,//>
//Eq,//==
//And,//&&
//Or,// ||
//Ne,// !=
//Le,// <=
//Ge,// >=

// 非终结符的类型定义
%type <ast_val> FuncDef FuncType Block Stmt Expr UnaryExp PrimaryExpr Number UnaryOp
%type <ast_val> AddExpr MulExpr RelExpr EqExpr AndExpr OrExpr Decl ConstDecl ConstDefUp
ConstDef BlockItemUp BlockItem LVal Identifier
%type <ast_val>  VarDecl VarDef VarDefUp
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
  : FuncType Identifier '(' ')' Block {
  	auto funcDef = new FuncDefAst();
	funcDef->funcType = shared_ptr<Ast>($1);
	funcDef->ident = shared_ptr<Ast>($2);
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
  : '{' BlockItemUp '}' {
    auto block = new BlockAst();
    auto blockItemUp = shared_ptr<Ast>($2);
    block->blockItems = BlockAst::GetFromBlockItemUp(dynamic_cast<BlockUpAst*>(blockItemUp.get()));
    $$ = block;
  }
  ;

 BlockItemUp
 :BlockItem{
	auto blockItemUp = new BlockUpAst(shared_ptr<Ast>($1));
	$$ = blockItemUp;
 }
|BlockItemUp BlockItem {
	auto blockItemUp = new BlockUpAst(shared_ptr<Ast>($1),shared_ptr<Ast>($2));
	$$ = blockItemUp;
};

BlockItem
:Stmt{
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>($1);
	$$ = blockItem;
}
|Decl{
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>($1);
	$$ = blockItem;
};



Decl
:ConstDecl{
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>($1);
	$$ = decl;
}
|VarDecl{
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>($1);
	$$ = decl;
};

ConstDecl
:CONST INT ConstDefUp ';'{
	auto constDecl = new ConstDeclAst();
	constDecl->constDefs=  ConstDeclAst::GetFromConstDefUpAst(dynamic_cast<ConstDefUpAst*>(shared_ptr<Ast>($3).get()));
	constDecl->dataType = *($2);
	$$ = constDecl;
};

ConstDefUp
:ConstDef{
	auto constDeclUp = new ConstDefUpAst(shared_ptr<Ast>($1));
	$$ = constDeclUp;
}
|ConstDefUp ',' ConstDef{
	auto constDeclUp = new ConstDefUpAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	$$ = constDeclUp;
};

ConstDef
:Identifier '=' Expr{
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>($1);
	constDef->const_val = shared_ptr<Ast>($3);
	$$ = constDef;
};


VarDecl
:INT VarDefUp ';'{
	auto varDecl = new VarDeclAst();
	varDecl->varDefs=  VarDeclAst::GetFromVarDefUpAst(dynamic_cast<VarDefUpAst*>(shared_ptr<Ast>($2).get()));
	varDecl->dataType =  *($1);
	$$ = varDecl;
};

VarDefUp
:VarDef{
	auto varDeclUp = new VarDefUpAst(shared_ptr<Ast>($1));
        $$ = varDeclUp;
}
|VarDefUp "," VarDef {
	auto varDeclUp = new VarDefUpAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
        $$ = varDeclUp;
}
;

VarDef
:Identifier{
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>($1);
	$$ = varDef;
}
|Identifier '=' Expr{
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>($1);
	varDef->var_expr =  shared_ptr<Ast>($3);
	varDef->is_expr = true;
	$$ = varDef;
};


Identifier
:IDENT{
	auto identifier=  new IdentifierAst();
	identifier->name = *($1);
	$$ = identifier;
};

Stmt
  : RETURN Expr ';' {
    auto stmt = new StmtAst();
    stmt->expr = shared_ptr<Ast>($2);
    stmt->type = StmtType::kReturn;
    $$ = stmt;
  }
| LVal '=' Expr ';'{
	auto stmt = new StmtAst();
    	stmt->expr = shared_ptr<Ast>($3);
    	stmt->l_val =  shared_ptr<Ast>($1);
    	stmt->type = StmtType::kDecl;
    	$$ = stmt;
 }
  ;

Expr
  : OrExpr {
    auto Expr = new ExpAst();
    Expr->realExpr = shared_ptr<Ast>($1);
    $$ = Expr;
  }
;

AddExpr
:MulExpr {
  $$ = new BinaryExprAst( shared_ptr<Ast>($1));
}
|AddExpr '+' MulExpr{
  $$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"+");
}
|AddExpr '-' MulExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"-");
};

RelExpr
:AddExpr{
 $$ = new BinaryExprAst( shared_ptr<Ast>($1));
}
| RelExpr LT AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"<");
}
| RelExpr GT AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),">");
}
| RelExpr LE AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"<=");
}
| RelExpr GE AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),">=");
};

EqExpr
:RelExpr {
$$ = new BinaryExprAst( shared_ptr<Ast>($1));
}
|EqExpr EQ RelExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"==");
}
|EqExpr NE RelExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"!=");
};

AndExpr
:EqExpr{
$$ = new BinaryExprAst( shared_ptr<Ast>($1));
}
|AndExpr  AND EqExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"&&");
};


OrExpr
:AndExpr{
$$ = new BinaryExprAst( shared_ptr<Ast>($1));
}
|OrExpr OR AndExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"||");
};

MulExpr
:UnaryExp{
  $$ = new BinaryExprAst(shared_ptr<Ast>($1));
}
|MulExpr '*' UnaryExp{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"*");
}
|MulExpr '/' UnaryExp{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"/");
}
|MulExpr '%' UnaryExp{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),"%");
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
  |LVal{
  auto primaryAst = new PrimaryExprAst();
      primaryAst->primaryType = PrimaryExprAst::PrimaryType::IDENTIFIER;
      primaryAst->primaryExpr = shared_ptr<Ast>($1);
      $$ = primaryAst;
  }
;

LVal
:Identifier{
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>($1);
	$$ = lval;
}
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
//  printf("%d:%d '%s'\n",yylloc.first_lien,yylloc.first_colunmn,s);
	printf("%s\n",s);
}
