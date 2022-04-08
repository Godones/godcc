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
%token <str_val> IDENT LT GT EQ AND OR NE LE GE CONST INT IF ELSE WHILE BREAK CONTINUE VOID
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
%type <ast_val>  VarDecl VarDef VarDefUp CompUnitItem FuncFParams FuncFParamUp FuncFParamDef
%type <ast_val>  FuncRParams FuncRParamUp CompUnit ArrayExpList
%type <ast_val> InitValList  InitVal
//%type <int_val>
//%type <str_val>


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

TranslationUnitAst
:CompUnit{
  auto trans  = new TranslationUnitAst();
  trans->comp_unit = shared_ptr<Ast>($1);
  ast = shared_ptr<Ast>(trans);
 }
 ;


// 开始符, CompUnit ::= FuncDef, 大括号后声明了解析完成后 parser 要做的事情
// 之前我们定义了 FuncDef 会返回一个 str_val, 也就是字符串指针
// 而 parser 一旦解析完 CompUnit, 就说明所有的 token 都被解析了, 即解析结束了
// 此时我们应该把 FuncDef 返回的结果收集起来, 作为 AST 传给调用 parser 的函数
// $1 指代规则里第一个符号的返回值, 也就是 FuncDef 的返回值
CompUnit
:CompUnitItem{
    auto compUnit = new CompUnitAst(shared_ptr<Ast>($1));
    $$ = compUnit;
}
|CompUnit CompUnitItem{
	auto compUnit = new CompUnitAst(shared_ptr<Ast>($1), shared_ptr<Ast>($2));
	$$ = compUnit;
}
;

CompUnitItem
:FuncDef{
 	$$ = $1;
}
|Decl{
	$$ = $1;
};



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
  : FuncType Identifier '(' FuncFParams ')' Block {
  	auto funcDef = new FuncDefAst();
	funcDef->funcType = shared_ptr<Ast>($1);
	funcDef->ident = shared_ptr<Ast>($2);
	funcDef->funcParam = shared_ptr<Ast>($4);
	funcDef->block = shared_ptr<Ast>($6);
	$$ = funcDef;
  }
  | FuncType Identifier '('  ')' Block {
     	auto funcDef = new FuncDefAst();
   	funcDef->funcType = shared_ptr<Ast>($1);
   	funcDef->ident = shared_ptr<Ast>($2);
   	funcDef->block = shared_ptr<Ast>($5);
   	$$ = funcDef;
     }
  ;

FuncFParams
:FuncFParamUp{
	auto funcFP = new FuncFParamAst();
	funcFP->params = FuncFParamAst::GetParamsFromFuncFParaUp(dynamic_cast<FuncFParamUpAst*>(shared_ptr<Ast>($1).get()));
	$$ = funcFP;
};

FuncFParamUp
:FuncFParamDef {
	auto funcFPUp = new FuncFParamUpAst(shared_ptr<Ast>($1));
	$$ = funcFPUp;
}
|FuncFParamUp ',' FuncFParamDef{
	auto funcFPUp = new FuncFParamUpAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	$$ = funcFPUp;
};


FuncFParamDef
:INT  Identifier{
	auto funcParaDef = new FuncFParamDefAst();
	funcParaDef->type = *($1);
	funcParaDef->ident = shared_ptr<Ast>($2);
	$$ = funcParaDef;

};



//
FuncType
: INT {
    auto funcType = new FuncTypeAst();
    funcType->type = string("int");
    $$ = funcType;
  }
|VOID {
	auto funcType = new FuncTypeAst();
	funcType->type = string("void");
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
:Identifier ArrayExpList '=' InitValList{
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>($1);
	constDef->array_expr_list = shared_ptr<Ast>($2);
	constDef->const_val = shared_ptr<Ast>($4);
	$$ = constDef;
}
|Identifier '=' InitValList{
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>($1);
	constDef->const_val = shared_ptr<Ast>($3);
	$$ = constDef;
}
;
ArrayExpList
: '[' Expr ']'{
 	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>($2));
 	$$ = array_expr;
}
| ArrayExpList '[' Expr ']'{
	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
 	$$ = array_expr;
};

InitValList
:Expr{
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>($1);
	$$ = init_val_list;
}
|'{' '}' {}
|'{' InitVal '}'{
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>($2);
	$$ = init_val_list;
};

InitVal
:InitValList{
	auto init_val = new InitValAst(shared_ptr<Ast>($1));
	$$ = init_val;
}
|InitVal ',' InitValList{
	auto init_val = new InitValAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	$$ = init_val;
};



VarDecl
:FuncType VarDefUp ';'{
	auto varDecl = new VarDeclAst();
	varDecl->varDefs=  VarDeclAst::GetFromVarDefUpAst(dynamic_cast<VarDefUpAst*>(shared_ptr<Ast>($2).get()));
	varDecl->dataType =  shared_ptr<Ast>($1);
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
|Identifier ArrayExpList{
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>($1);
	varDef->array_expr_list = shared_ptr<Ast>($2);
	$$ = varDef;
}
|Identifier '=' InitValList{
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>($1);
	varDef->var_expr =  shared_ptr<Ast>($3);
	varDef->is_expr = true;
	$$ = varDef;
}
|Identifier ArrayExpList '=' InitValList{
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>($1);
	varDef->array_expr_list = shared_ptr<Ast>($2);
	varDef->var_expr =  shared_ptr<Ast>($4);
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
| RETURN ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kReturn;
	$$ = stmt;
}
|Expr ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	stmt->expr = shared_ptr<Ast>($1);
	$$ = stmt;
}
|';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	$$ = stmt;
}
|Block{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBlock;
	stmt->expr = shared_ptr<Ast>($1);
	$$ = stmt;
}
| LVal '=' Expr ';'{
	auto stmt = new StmtAst();
    	stmt->expr = shared_ptr<Ast>($3);
    	stmt->l_val =  shared_ptr<Ast>($1);
    	stmt->type = StmtType::kDecl;
    	$$ = stmt;
 }
|IF '(' Expr ')' Stmt %prec LOWER_THAN_ELSE{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->expr = shared_ptr<Ast>($3);
	ifStmt->stmt =  shared_ptr<Ast>($5);
	stmt-> expr = shared_ptr<Ast>(ifStmt);
	$$ = stmt;
}
|IF '(' Expr ')' Stmt ELSE Stmt{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->expr = shared_ptr<Ast>($3);
	ifStmt->stmt =  shared_ptr<Ast>($5);
	ifStmt->elseStmt = shared_ptr<Ast>($7);
	stmt-> expr = shared_ptr<Ast>(ifStmt);
	$$ = stmt;
}
|WHILE '(' Expr ')' Stmt{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kWhile;
	auto whileStmt = new WhileStmtAst();
	whileStmt->expr = shared_ptr<Ast>($3);
	whileStmt->stmt =  shared_ptr<Ast>($5);
	stmt->expr = shared_ptr<Ast>(whileStmt);
	$$ = stmt;
}
|BREAK ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBreak;
	$$ = stmt;
}
|CONTINUE ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kContinue;
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
  $$ = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kAdd);
}
|AddExpr '+' MulExpr{
  $$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kAdd,"+");
}
|AddExpr '-' MulExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kAdd,"-");
};

RelExpr
:AddExpr{
 $$ = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kRel);
}
| RelExpr LT AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,"<");
}
| RelExpr GT AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,">");
}
| RelExpr LE AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,"<=");
}
| RelExpr GE AddExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,">=");
};

EqExpr
:RelExpr {
$$ = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kEq);
}
|EqExpr EQ RelExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kEq,"==");
}
|EqExpr NE RelExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kEq,"!=");
};

AndExpr
:EqExpr{
$$ = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kAnd);
}
|AndExpr  AND EqExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kAnd,"&&");
};


OrExpr
:AndExpr{
$$ = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kLor);
}
|OrExpr OR AndExpr{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kLor,"||");
};

MulExpr
:UnaryExp{
  $$ = new BinaryExprAst(shared_ptr<Ast>($1),BinaryType::kMul);
}
|MulExpr '*' UnaryExp{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kMul,"*");
}
|MulExpr '/' UnaryExp{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kMul,"/");
}
|MulExpr '%' UnaryExp{
$$ = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kMul,"%");
}
;


UnaryExp
  : PrimaryExpr {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp-> unaryExpr = shared_ptr<Ast>($1);
  	unaryExp->unaryType = UnaryType::kPrimary;
  	$$ = unaryExp;
  }
  |UnaryOp UnaryExp{
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>($1);
        unaryExp->unaryExpr = shared_ptr<Ast>($2);
	unaryExp->unaryType = UnaryType::kUnary;
	$$ = unaryExp;
  }
| Identifier '(' ')'{
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>($1);
	unaryExp->unaryType = UnaryType::kCall;
	$$ = unaryExp;
}
|Identifier '(' FuncRParams ')'{
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>($1);
        unaryExp->unaryExpr = shared_ptr<Ast>($3);
	unaryExp->unaryType = UnaryType::kCall;
	$$ = unaryExp;
}
;

FuncRParams
:FuncRParamUp{
	auto funcRP = new FuncRParamAst();
	funcRP->params = FuncRParamAst::GetParamsFromFuncRParaUp(dynamic_cast<FuncRParamUpAst*>(shared_ptr<Ast>($1).get()));
	$$ = funcRP;
}
;
FuncRParamUp
:Expr{
	auto funcRPUp = new FuncRParamUpAst(shared_ptr<Ast>($1));
	$$ = funcRPUp;
}
|FuncRParamUp ',' Expr{
	auto funcRPUp = new FuncRParamUpAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	$$ = funcRPUp;
}
;

PrimaryExpr
  : '(' Expr ')' {
  auto primaryAst = new PrimaryExprAst();
  primaryAst->primaryExpr = shared_ptr<Ast>($2);
  primaryAst->primaryType = PrimaryType::EXP;
  $$ = primaryAst;
  }
  |Number {
  auto primaryAst = new PrimaryExprAst();
    primaryAst->primaryExpr = shared_ptr<Ast>($1);
    primaryAst->primaryType = PrimaryType::NUMBER;
    $$ = primaryAst;
  }
  |LVal{
      auto primaryAst = new PrimaryExprAst();
      primaryAst->primaryType = PrimaryType::IDENTIFIER;
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
| Identifier ArrayExpList{
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>($1);
	lval->array_expr_list = shared_ptr<Ast>($2);
	$$ = lval;
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
//  printf("%d:%d '%s'\n",yylloc.first_lien,yylloc.first_colunmn,s);
	printf("%s\n",s);
}
