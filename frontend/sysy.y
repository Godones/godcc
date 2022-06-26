%code requires {
  #include <memory>
  #include <string>
  #include "ast.h"
}
//%expect 1
%locations
%{
#include <iostream>
#include <memory>
#include <string>
#include "ast.h"

//#include "ast_to_ir.h" //用于编译器求值


#define YYLOCATION_PRINT location_print //打印位置信息
// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::shared_ptr<Ast> &ast, const char *s);
using namespace std;
%}

// 定义 parser 函数和错误处理函数的附加参数
// 我们需要返回 CST, 所以我们把附加参数定义成AST智能指针
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
  const char * cstr_val;
}

// lexer 返回的所有 token 种类的声明
// 注意 IDENT 和 INT_CONST 会返回 token 的值, 分别对应 str_val 和 int_val
%token RETURN
%token <str_val> IDENT LT GT EQ AND OR NE LE GE CONST INT IF ELSE WHILE BREAK CONTINUE VOID FOR DEC INC STRING
%token <int_val> INT_CONST
//Lt,//<
//Gt,//>
//Eq,//==
//And,//&&
//Or,// ||
//Ne,// !=
//Le,// <=
//Ge,// >=
//DEC --
//INC ++

// 非终结符的类型定义
%type <ast_val> FuncDef FuncType Block Stmt Expr UnaryExp PrimaryExpr Number UnaryOp
%type <ast_val> AddExpr MulExpr RelExpr EqExpr AndExpr OrExpr Decl ConstDecl ConstDefList
ConstDef BlockItemList BlockItem LVal Identifier
%type <ast_val>  VarDecl VarDef VarDefList CompUnitItem FuncFParamList  FuncFParam
%type <ast_val>  FuncRParamList  CompUnit ArrayExpList
%type <ast_val> InitValList  InitVal PostfixExp String
//%type <int_val>
//%type <str_val>


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

TranslationUnitAst
:CompUnit{
  auto trans  = new TranslationUnitAst();
  trans->comp_unit = shared_ptr<Ast>($1);
  trans->line = @$.first_line;
  trans->column = @$.first_column;
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
      compUnit->line = @$.first_line;
      compUnit->column = @$.first_column;
    $$ = compUnit;
}
|CompUnit CompUnitItem{
	auto compUnit = new CompUnitAst(shared_ptr<Ast>($1), shared_ptr<Ast>($2));
	compUnit->line = @$.first_line;
        compUnit->column = @$.first_column;
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
  : FuncType Identifier '(' FuncFParamList ')' Block {
  	auto funcDef = new FuncDefAst();
	funcDef->funcType = shared_ptr<Ast>($1);
	funcDef->ident = shared_ptr<Ast>($2);
	funcDef->funcParamList = shared_ptr<Ast>($4);
	funcDef->block = shared_ptr<Ast>($6);
 	funcDef->line = @$.first_line;
      	funcDef->column = @$.first_column;
	$$ = funcDef;
  }
  | FuncType Identifier '('  ')' Block {
     	auto funcDef = new FuncDefAst();
   	funcDef->funcType = shared_ptr<Ast>($1);
   	funcDef->ident = shared_ptr<Ast>($2);
   	funcDef->block = shared_ptr<Ast>($5);
   	funcDef->line = @$.first_line;
	funcDef->column = @$.first_column;
   	$$ = funcDef;
     }
  ;


FuncFParamList
:FuncFParam {
	auto func_fpl = new FuncFParamListAst(shared_ptr<Ast>($1));
	func_fpl->line = @$.first_line;
	func_fpl->column = @$.first_column;
	$$ = func_fpl;
}
|FuncFParamList ',' FuncFParam{
	auto func_fpl = new FuncFParamListAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	func_fpl->line = @$.first_line;
	func_fpl->column = @$.first_column;
	$$ = func_fpl;
};


FuncFParam
:FuncType  Identifier{
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>($1);
	funcParaDef->ident = shared_ptr<Ast>($2);
	funcParaDef->first_no_dim = false;
	funcParaDef->line = @$.first_line;
	funcParaDef->column = @$.first_column;
	$$ = funcParaDef;
}
| FuncType Identifier '[' ']'{
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>($1);
	funcParaDef->ident = shared_ptr<Ast>($2);
	funcParaDef->first_no_dim = true;
	funcParaDef->line = @$.first_line;
	funcParaDef->column = @$.first_column;
	$$ = funcParaDef;
}
|FuncType Identifier '[' ']' ArrayExpList{
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>($1);
	funcParaDef->ident = shared_ptr<Ast>($2);
	funcParaDef->first_no_dim = true;
	funcParaDef->array_expr_list = shared_ptr<Ast>($5);
	funcParaDef->line = @$.first_line;
	funcParaDef->column = @$.first_column;
	$$ = funcParaDef;
}
|FuncType Identifier  ArrayExpList{
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>($1);
	funcParaDef->ident = shared_ptr<Ast>($2);
	funcParaDef->first_no_dim = false;
	funcParaDef->array_expr_list = shared_ptr<Ast>($3);
	funcParaDef->line = @$.first_line;
	funcParaDef->column = @$.first_column;
	$$ = funcParaDef;
}
;



//
FuncType
: INT {
    auto funcType = new FuncTypeAst();
    funcType->type = "int";
	funcType->line = @$.first_line;
	funcType->column = @$.first_column;
    $$ = funcType;
  }
|VOID {
	auto funcType = new FuncTypeAst();
	funcType->type = "void";
	funcType->line = @$.first_line;
	funcType->column = @$.first_column;
	$$ = funcType;
}
  ;

Block
  : '{' BlockItemList '}' {
	auto block = new BlockAst();
	block-> block_item_list= shared_ptr<Ast>($2);
	block->line = @$.first_line;
	block->column = @$.first_column;
	$$ = block;
  }
  |'{' '}' {
	auto block = new BlockAst();
	block->line = @$.first_line;
	block->column = @$.first_column;
	$$ = block;
  }
  ;

 BlockItemList
 :BlockItem{
	auto blockItemUp = new BlockItemListAst(shared_ptr<Ast>($1));
	blockItemUp->line = @$.first_line;
	blockItemUp->column = @$.first_column;
	$$ = blockItemUp;
 }
|BlockItemList BlockItem {
	auto blockItemUp = new BlockItemListAst(shared_ptr<Ast>($1),shared_ptr<Ast>($2));
	blockItemUp->line = @$.first_line;
	blockItemUp->column = @$.first_column;
	$$ = blockItemUp;
};

BlockItem
:Stmt{
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>($1);
		blockItem->line = @$.first_line;
        	blockItem->column = @$.first_column;
	$$ = blockItem;
}
|Decl{
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>($1);
		blockItem->line = @$.first_line;
		blockItem->column = @$.first_column;
	$$ = blockItem;
};



Decl
:ConstDecl{
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>($1);
	decl->line = @$.first_line;
	decl->column = @$.first_column;
	$$ = decl;
}
|VarDecl{
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>($1);
		decl->line = @$.first_line;
        	decl->column = @$.first_column;
	$$ = decl;
};

ConstDecl
:CONST FuncType ConstDefList ';'{
	auto constDecl = new ConstDeclAst();
	constDecl->const_def_list= shared_ptr<Ast>($3);
	constDecl->data_type = shared_ptr<Ast>($2);
	constDecl->line = @$.first_line;
	constDecl->column = @$.first_column;
	$$ = constDecl;
};

ConstDefList
:ConstDef{
	auto constDeclUp = new ConstDefListAst(shared_ptr<Ast>($1));
	constDeclUp->line = @$.first_line;
	constDeclUp->column = @$.first_column;
	$$ = constDeclUp;
}
|ConstDefList ',' ConstDef{
	auto constDeclUp = new ConstDefListAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
		constDeclUp->line = @$.first_line;
        	constDeclUp->column = @$.first_column;
	$$ = constDeclUp;
};

ConstDef
:Identifier ArrayExpList '=' InitValList{
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>($1);
	constDef->array_expr_list = shared_ptr<Ast>($2);
	constDef->const_val = shared_ptr<Ast>($4);
	constDef->line = @$.first_line;
	constDef->column = @$.first_column;
	$$ = constDef;
}
|Identifier '=' InitValList{
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>($1);
	constDef->const_val = shared_ptr<Ast>($3);
	constDef->line = @$.first_line;
	constDef->column = @$.first_column;
	$$ = constDef;
}
;
ArrayExpList
: '[' Expr ']'{
 	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>($2));
 	array_expr->line = @$.first_line;
	array_expr->column = @$.first_column;
 	$$ = array_expr;
}
| ArrayExpList '[' Expr ']'{
	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	 	array_expr->line = @$.first_line;
        	array_expr->column = @$.first_column;
 	$$ = array_expr;
};

InitValList
:Expr{
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>($1);
	init_val_list->line = @$.first_line;
	init_val_list->column = @$.first_column;
	$$ = init_val_list;
}
|'{' '}' {
	auto init_val_list = new InitValListAst();
	init_val_list->line = @$.first_line;
	init_val_list->column = @$.first_column;
	$$ = init_val_list;
}
|'{' InitVal '}'{
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>($2);
	init_val_list->line = @$.first_line;
	init_val_list->column = @$.first_column;
	$$ = init_val_list;
};

InitVal
:InitValList{
	auto init_val = new InitValAst(shared_ptr<Ast>($1));
	init_val->line = @$.first_line;
	init_val->column = @$.first_column;
	$$ = init_val;
}
|InitVal ',' InitValList{
	auto init_val = new InitValAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	init_val->line = @$.first_line;
	init_val->column = @$.first_column;
	$$ = init_val;
};



VarDecl
:FuncType VarDefList ';'{
	auto varDecl = new VarDeclAst();
	varDecl->var_def_list = shared_ptr<Ast>($2);
	varDecl->dataType =  shared_ptr<Ast>($1);
		varDecl->line = @$.first_line;
        	varDecl->column = @$.first_column;
	$$ = varDecl;
};

VarDefList
:VarDef{
	auto varDeclUp = new VarDefListAst(shared_ptr<Ast>($1));
	varDeclUp->line = @$.first_line;
	varDeclUp->column = @$.first_column;
        $$ = varDeclUp;
}
|VarDefList ',' VarDef {
	auto varDeclUp = new VarDefListAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	varDeclUp->line = @$.first_line;
	varDeclUp->column = @$.first_column;
        $$ = varDeclUp;
}
;

VarDef
:Identifier{
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>($1);
		varDef->line = @$.first_line;
        	varDef->column = @$.first_column;
	$$ = varDef;
}
|Identifier ArrayExpList{
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>($1);
	varDef->array_expr_list = shared_ptr<Ast>($2);
	varDef->line = @$.first_line;
	varDef->column = @$.first_column;
	$$ = varDef;
}
|Identifier '=' InitValList{
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>($1);
	varDef->var_expr =  shared_ptr<Ast>($3);
	varDef->line = @$.first_line;
	varDef->column = @$.first_column;
	$$ = varDef;
}
|Identifier ArrayExpList '=' InitValList{
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>($1);
	varDef->array_expr_list = shared_ptr<Ast>($2);
	varDef->var_expr =  shared_ptr<Ast>($4);
	varDef->line = @$.first_line;
	varDef->column = @$.first_column;
	$$ = varDef;
};


Identifier
:IDENT{
	auto identifier=  new IdentifierAst();
	identifier->name = ($1)->c_str();
	identifier->line = @$.first_line;
	identifier->column = @$.first_column;
	$$ = identifier;
};



Stmt
: RETURN Expr ';' {
	auto stmt = new StmtAst();
	stmt->expr = shared_ptr<Ast>($2);
	stmt->type = StmtType::kReturn;
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
| RETURN ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kReturn;
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
|Expr ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	stmt->expr = shared_ptr<Ast>($1);
		stmt->line = @$.first_line;
        	stmt->column = @$.first_column;
	$$ = stmt;
}
|';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
		stmt->line = @$.first_line;
        	stmt->column = @$.first_column;
	$$ = stmt;
}
|Block{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBlock;
	stmt->expr = shared_ptr<Ast>($1);
		stmt->line = @$.first_line;
        	stmt->column = @$.first_column;
	$$ = stmt;
}
| LVal '=' Expr ';'{
	auto stmt = new StmtAst();
    	stmt->expr = shared_ptr<Ast>($3);
    	stmt->l_val =  shared_ptr<Ast>($1);
    	stmt->type = StmtType::kAssign;
    		stmt->line = @$.first_line;
        	stmt->column = @$.first_column;
    	$$ = stmt;
 }
|IF '(' Expr ')' Stmt %prec LOWER_THAN_ELSE{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->line = @$.first_line;
	ifStmt->column = @$.first_column;
	ifStmt->expr = shared_ptr<Ast>($3);
	ifStmt->stmt =  shared_ptr<Ast>($5);
	stmt-> expr = shared_ptr<Ast>(ifStmt);
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
|IF '(' Expr ')' Stmt ELSE Stmt{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->line = @$.first_line;
	ifStmt->column = @$.first_column;
	ifStmt->expr = shared_ptr<Ast>($3);
	ifStmt->stmt =  shared_ptr<Ast>($5);
	ifStmt->elseStmt = shared_ptr<Ast>($7);
	stmt-> expr = shared_ptr<Ast>(ifStmt);
		stmt->line = @$.first_line;
        	stmt->column = @$.first_column;
	$$ = stmt;
}
|WHILE '(' Expr ')' Stmt{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kWhile;
	auto whileStmt = new WhileStmtAst();
	whileStmt->expr = shared_ptr<Ast>($3);
	whileStmt->stmt =  shared_ptr<Ast>($5);
	whileStmt->line = @$.first_line;
	whileStmt->column = @$.first_column;
	stmt->expr = shared_ptr<Ast>(whileStmt);
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
|BREAK ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBreak;
		stmt->line = @$.first_line;
        	stmt->column = @$.first_column;
	$$ = stmt;
}
|CONTINUE ';'{
	auto stmt = new StmtAst();
	stmt->type = StmtType::kContinue;
		stmt->line = @$.first_line;
        	stmt->column = @$.first_column;
	$$ = stmt;
}
|FOR '(' Stmt  Stmt  Expr ')' Stmt {
	printf("FOR\n");
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>($3);
	forStmt->expr2 = shared_ptr<Ast>($4);
	forStmt->expr3 = shared_ptr<Ast>($5);
	forStmt->stmt =  shared_ptr<Ast>($7);
	forStmt->line = @$.first_line;
	forStmt->column = @$.first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
|FOR '(' Stmt  Stmt  ')' Stmt {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>($3);
	forStmt->expr2 = shared_ptr<Ast>($4);
	forStmt->stmt =  shared_ptr<Ast>($6);
	forStmt->line = @$.first_line;
	forStmt->column = @$.first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
|FOR '(' VarDecl  Stmt  Expr ')' Stmt {
	printf("FOR\n");
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>($3);
	forStmt->expr2 = shared_ptr<Ast>($4);
	forStmt->expr3 = shared_ptr<Ast>($5);
	forStmt->stmt =  shared_ptr<Ast>($7);
	forStmt->line = @$.first_line;
	forStmt->column = @$.first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
|FOR '(' VarDecl  Stmt  ')' Stmt {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>($3);
	forStmt->expr2 = shared_ptr<Ast>($4);
	forStmt->stmt =  shared_ptr<Ast>($6);
	forStmt->line = @$.first_line;
	forStmt->column = @$.first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = @$.first_line;
	stmt->column = @$.first_column;
	$$ = stmt;
}
 ;

Expr
  : OrExpr {
    auto Expr = new ExpAst();
    Expr->realExpr = shared_ptr<Ast>($1);
	Expr->line = @$.first_line;
	Expr->column = @$.first_column;
    $$ = Expr;
  }
;

AddExpr
:MulExpr {
  auto binary = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kAdd);
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
|AddExpr '+' MulExpr{
  auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kAdd,"+");
  binary->line = @$.first_line;
  binary->column = @$.first_column;
  $$ = binary;
}
|AddExpr '-' MulExpr{

  auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kAdd,"-");
  binary->line = @$.first_line;
  binary->column = @$.first_column;
  $$ = binary;
};

RelExpr
:AddExpr{
 auto binary = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kRel);
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
| RelExpr LT AddExpr{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,"<");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
| RelExpr GT AddExpr{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,">");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
| RelExpr LE AddExpr{
auto binary =  new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,"<=");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
| RelExpr GE AddExpr{
auto binary= new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kRel,">=");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
};

EqExpr
:RelExpr {
auto binary = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kEq);
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
|EqExpr EQ RelExpr{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kEq,"==");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
|EqExpr NE RelExpr{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kEq,"!=");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
};

AndExpr
:EqExpr{
auto binary = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kAnd);
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
|AndExpr  AND EqExpr{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kAnd,"&&");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
};


OrExpr
:AndExpr{
auto binary = new BinaryExprAst( shared_ptr<Ast>($1),BinaryType::kLor);
	binary->line = @$.first_line;
	binary->column = @$.first_column;
  $$ = binary;
}
|OrExpr OR AndExpr{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kLor,"||");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
};

MulExpr
:UnaryExp{
  auto binary = new BinaryExprAst(shared_ptr<Ast>($1),BinaryType::kMul);
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
|MulExpr '*' UnaryExp{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kMul,"*");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
|MulExpr '/' UnaryExp{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kMul,"/");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
|MulExpr '%' UnaryExp{
auto binary = new BinaryExprAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3),BinaryType::kMul,"%");
  binary->line = @$.first_line;
binary->column = @$.first_column;
  $$ = binary;
}
;


UnaryExp
  : PostfixExp {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp-> unaryExpr = shared_ptr<Ast>($1);
  	unaryExp->unaryType = UnaryType::kPostfix;
  	unaryExp->line = @$.first_line;
        unaryExp->column = @$.first_column;
  	$$ = unaryExp;
  }
  |UnaryOp UnaryExp{
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>($1);
        unaryExp->unaryExpr = shared_ptr<Ast>($2);
	unaryExp->unaryType = UnaryType::kUnary;
  	unaryExp->line = @$.first_line;
	unaryExp->column = @$.first_column;
	$$ = unaryExp;
  }
  |DEC UnaryExp{
  	auto unaryExp = new UnaryExprAst();
  	unaryExp->unaryExpr = shared_ptr<Ast>($2);
  	auto unaryOpAst = new UnaryOpAst("--");
  	unaryExp->unaryOp = shared_ptr<Ast>(unaryOpAst);
  	unaryExp->unaryType = UnaryType::kUnary;
  	unaryExp->line = @$.first_line;
	unaryExp->column = @$.first_column;
  	$$ = unaryExp;
  }
  |INC UnaryExp{
  	auto unaryExp = new UnaryExprAst();
  	unaryExp->unaryExpr = shared_ptr<Ast>($2);
  	auto unaryOpAst = new UnaryOpAst("++");
	unaryExp->unaryOp = shared_ptr<Ast>(unaryOpAst);
  	unaryExp->unaryType = UnaryType::kUnary;
  	unaryExp->line = @$.first_line;
	unaryExp->column = @$.first_column;
	$$ = unaryExp;
}
| Identifier '(' ')'{
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>($1);
	unaryExp->unaryType = UnaryType::kCall;
	  unaryExp->line = @$.first_line;
	unaryExp->column = @$.first_column;
	$$ = unaryExp;
}
|Identifier '(' FuncRParamList ')'{
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>($1);
    	unaryExp->unaryExpr = shared_ptr<Ast>($3);
	unaryExp->unaryType = UnaryType::kCall;
	  unaryExp->line = @$.first_line;
	unaryExp->column = @$.first_column;
	$$ = unaryExp;
}
;

PostfixExp:PrimaryExpr{
	auto postfixExp = new PostfixExprAst();
	postfixExp->postfixExpr = shared_ptr<Ast>($1);
	postfixExp->postfixType = PostfixType::kPrimary;
	 postfixExp->line = @$.first_line;
	postfixExp->column = @$.first_column;
	$$ = postfixExp;
}
|PostfixExp DEC {
	auto postfixExp = new PostfixExprAst();
	postfixExp->postfixExpr = shared_ptr<Ast>($1);
	postfixExp->postfixType = PostfixType::kBDec;
	  postfixExp->line = @$.first_line;
	postfixExp->column = @$.first_column;
	$$ = postfixExp;
}
|PostfixExp INC {
	auto postfixExp = new PostfixExprAst();
	postfixExp->postfixExpr = shared_ptr<Ast>($1);
	postfixExp->postfixType = PostfixType::kBInc;
        postfixExp->line = @$.first_line;
	postfixExp->column = @$.first_column;
	$$ = postfixExp;
}
;


FuncRParamList
:Expr{
	auto funcRPUp = new FuncRParamListAst(shared_ptr<Ast>($1));
	  	  funcRPUp->line = @$.first_line;
                funcRPUp->column = @$.first_column;
	$$ = funcRPUp;
}
|FuncRParamList ',' Expr{
	auto funcRPUp = new FuncRParamListAst(shared_ptr<Ast>($1),shared_ptr<Ast>($3));
	  funcRPUp->line = @$.first_line;
	funcRPUp->column = @$.first_column;
	$$ = funcRPUp;
}
;

PrimaryExpr
  : '(' Expr ')' {
  auto primaryAst = new PrimaryExprAst();
  primaryAst->primaryExpr = shared_ptr<Ast>($2);
  primaryAst->primaryType = PrimaryType::EXP;
  primaryAst->line = @$.first_line;
  primaryAst->column = @$.first_column;
  auto expr = dynamic_cast<ExpAst*>($2);
  //编译器求值
  if(expr->have_value){
  	primaryAst->have_value = true;
  	primaryAst->value = expr->value;
  }
  $$ = primaryAst;
  }
  |Number {
  auto primaryAst = new PrimaryExprAst();
    primaryAst->primaryExpr = shared_ptr<Ast>($1);
    primaryAst->primaryType = PrimaryType::NUMBER;
      primaryAst->line = @$.first_line;
   primaryAst->column = @$.first_column;
    $$ = primaryAst;
  }
  |String {
	auto primaryAst = new PrimaryExprAst();
	primaryAst->primaryExpr = shared_ptr<Ast>($1);
	primaryAst->primaryType = PrimaryType::STRING;
	primaryAst->line = @$.first_line;
	primaryAst->column = @$.first_column;
	$$ = primaryAst;
  }
  |LVal{
      auto primaryAst = new PrimaryExprAst();
      primaryAst->primaryType = PrimaryType::IDENTIFIER;
      primaryAst->primaryExpr = shared_ptr<Ast>($1);
        primaryAst->line = @$.first_line;
      	  primaryAst->column = @$.first_column;
      $$ = primaryAst;
  }
;

LVal
:Identifier{
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>($1);
	  lval->line = @$.first_line;
	  lval->column = @$.first_column;
	$$ = lval;
}
| Identifier ArrayExpList{
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>($1);
	lval->array_expr_list = shared_ptr<Ast>($2);
	  lval->line = @$.first_line;
	  lval->column = @$.first_column;
	$$ = lval;
}
;


UnaryOp
 : '+' {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "+";
   unaryOpAst->line = @$.first_line;
   unaryOpAst->column = @$.first_column;
   $$ = unaryOpAst;
 }
 | '-' {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "-";
   unaryOpAst->line = @$.first_line;
   unaryOpAst->column = @$.first_column;
   $$ = unaryOpAst;
 }
 | '!' {
  auto unaryOpAst = new UnaryOpAst();
  unaryOpAst->op = "!";
  unaryOpAst->line = @$.first_line;
  unaryOpAst->column = @$.first_column;
  $$ = unaryOpAst;
 }
 ;

Number
  : INT_CONST {
  auto numberAst = new NumberAst();
  numberAst->value = ($1);
  numberAst->line = @$.first_line;
  numberAst->column = @$.first_column;
  $$ = numberAst;
  }
  ;

String :STRING{
	auto stringAst = new StringAst();
	stringAst->value = ($1)->c_str();
	stringAst->line = @$.first_line;
	stringAst->column = @$.first_column;
	$$ = stringAst;
}
%%

// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(shared_ptr<Ast> &ast, const char *s) {
  	printf("[ERROR] address:%d:%d '%s'\n",yylloc.first_line,yylloc.first_column,s);
}
