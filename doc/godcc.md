# godcc编译器

编译流程:

1. 词法分析:将源代码按照字节流读入,输出有独立意义的Token(单词)
2. 语法分析：从词法分析获得Token流，按照语法规则建立AST抽象语法树
3. 语义分析:建立符号表-> 类型检查->编译器计算
4. 中间代码生成
5. 目标代码生成 ：指令选择->寄存器分配->指令调度

```bison
// 这里写一些选项, 可以控制 Flex/Bison 的某些行为

%{

// 这里写一些全局的代码
// 因为最后要生成 C/C++ 文件, 实现主要逻辑的部分都是用 C/C++ 写的
// 难免会用到头文件, 所以通常头文件和一些全局声明/定义写在这里

%}

// 这里写一些 Flex/Bison 相关的定义
// 对于 Flex, 这里可以定义某个符号对应的正则表达式
// 对于 Bison, 这里可以定义终结符/非终结符的类型

%%

// 这里写 Flex/Bison 的规则描述
// 对于 Flex, 这里写的是 lexer 扫描到某个 token 后做的操作
// 对于 Bison, 这里写的是 parser 遇到某种语法规则后做的操作

%%

// 这里写一些用户自定义的代码
// 比如你希望在生成的 C/C++ 文件里定义一个函数, 做一些辅助工作
// 你同时希望在之前的规则描述里调用你定义的函数
// 那么, 你可以把 C/C++ 的函数定义写在这里, 声明写在文件开头
```

##### Flex定义段

```
下面的命令都以%option开始
noyywrap          yylex等分析函数结束后不再调用yywrap()函数。

nodefault         关闭一些默认行为，比如不能匹配的输入则回射到标准输出

warn              开启所有警告

case-insensitive  整个过程中匹配输入大小写不敏感，但是yytext还是原本输入匹配的内容

yylineno          自动的在yylineno变量中维护当前解析的行数总值，如果是解析的多个文件，可以在开打文件后重置它
```

##### **常用的全局变量**

```text
FILE *yyin/*yyout        Lex中本身已定义的输入和输出文件指针。

这两变量指明了flex生成的词法分析器从哪里获得输入和输出到哪里。默认指向标准输入和标准输出。

char *yytext         指向当前是别的词法单元的指针。

int   yyleng         当前词法单元的长度。

yylineno             提供当前的行数信息

ECHO                 lex中预定义的宏，相当于fprintf(yyout, "%s", yytext) , 即输出当前匹配的词法单元。
```

##### **常用的全局函数**

```text
yylex()          这一函数开始分析，它由lex自动生成。

yywrap()         这一函数在输入或文件的末尾调用。返回0继续扫描，-1结束扫描。

yymore()         这一函数告诉lexer将下一个标记附加到当前标记后。

yyless(int n)    返回当前匹配项除了开始的n个字符内的所有的内容到输入缓冲区，

解析器处理下一匹配时，他们将会被重新解析。
```

#### 第一节

目标: 支持下面的函数

```c
// 注释
int main(){
    return 9;
}
```

```ebnf
CompUnit  ::= FuncDef;

FuncDef   ::= FuncType IDENT "(" ")" Block;
FuncType  ::= "int";

Block     ::= "{" Stmt "}";
Stmt      ::= "return" Number ";";
Number    ::= INT_CONST;
```

IDENT 的名称一定为 main

INT_CONST 的范围为 [0, 2^{31} - 1][0,2 31 −1], 不包含负号

#### 第二节:支持一元表达式

```
Stmt        ::= "return" Exp ";";

Exp         ::= UnaryExp;
PrimaryExp  ::= "(" Exp ")" | Number;
Number      ::= INT_CONST;
UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
UnaryOp     ::= "+" | "-" | "!";
```

### 第三节:支持二元算数运算
```
Exp         ::= AddExp;
PrimaryExp  ::= ...;
Number      ::= ...;
UnaryExp    ::= ...;
UnaryOp     ::= ...;
MulExp      ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp      ::= MulExp | AddExp ("+" | "-") MulExp;
```

### 第四节:支持二元逻辑运算
```
Exp         ::= LOrExp;
PrimaryExp  ::= ...;
Number      ::= ...;
UnaryExp    ::= ...;
UnaryOp     ::= ...;
MulExp      ::= ...;
AddExp      ::= ...;
RelExp      ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp       ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp     ::= EqExp | LAndExp "&&" EqExp;
LOrExp      ::= LAndExp | LOrExp "||" LAndExp;
```



### 额外:json数据生成和树图格式化

```
pip install pytm-cli

```





```
     |----B     |----E----|----I
     |          |
     |----C-----|----F         |----J
A----|                         |
     |----D-----|----G----|----|----K
                |
                |----H
```

```
{
 	"name": "A",
    "children": [
        {
        	"name": "B",
            "children": []
        },
        {
        	"name": "C",
            "children": [
                {
                	"name": "E",
                    "children": [
                        {
                        	"name": "I",
                            "children": []  
                        }
                    ]
                },
                {
                 	"name": "F",
                    "children": []
                }
            ]
        },
        {
            "children": [
                {
                    "children": [
                        {
                            "children": [],
                            "name": "J"
                        },
                        {
                            "children": [],
                            "name": "K"
                        }
                    ],
                    "name": "G"
                },
                {
                    "children": [],
                    "name": "H"
                }
            ],
            "name": "D"
        }
    ]
}
```

### 第五节:支持定义常量

==这里开始注意递归匹配的问题==

```
Decl          ::= ConstDecl;
ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";";
BType         ::= "int";
ConstDef      ::= IDENT "=" ConstInitVal;
ConstInitVal  ::= ConstExp;
Block         ::= "{" {BlockItem} "}";
BlockItem     ::= Decl | Stmt;
LVal          ::= IDENT;
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
ConstExp      ::= Exp;

```

```c
CompUnit  ::= FuncDef;

FuncDef   ::= FuncType IDENT "(" ")" Block;
FuncType  ::= "int";
Block         ::= "{" BlockItemUp "}";
BlockItemUp   ::= BlcokItem | BlockItemUp BlockItem
BlockItem     ::= Decl | Stmt;


// Decl Decl Decl

Stmt      ::= "return" Exp ";";
Exp         ::= LOrExp;
Number    	::= INT_CONST;
PrimaryExp  ::= "(" Exp ")" | LVal | Number;
Number      ::= INT_CONST;
UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
UnaryOp     ::= "+" | "-" | "!";
MulExp      ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp      ::= MulExp | AddExp ("+" | "-") MulExp;
RelExp      ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp       ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp     ::= EqExp | LAndExp "&&" EqExp;
LOrExp      ::= LAndExp | LOrExp "||" LAndExp;


Decl          ::= ConstDecl ;
ConstDecl     ::= "const" INT ConstDefUp ";";
ConstDefUp    ::= ConstDef  | ConstDefUp "," ConstDef
ConstDef      ::= IDENT "=" Exp;//注意这里需要判断表达式是否是常量

LVal          ::= IDENT; //这一部分需要建立符号表来查找相关内容
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
```



### 第六节:支持变量和赋值

```
Decl          ::= ConstDecl | VarDecl;
ConstDecl     ::= ...;
BType         ::= ...;
ConstDef      ::= ...;
ConstInitVal  ::= ...;
VarDecl       ::= BType VarDef {"," VarDef} ";";
VarDef        ::= IDENT | IDENT "=" InitVal;
InitVal       ::= Exp;

...

Block         ::= ...;
BlockItem     ::= ...;
Stmt          ::= LVal "=" Exp ";"
                | "return" Exp ";";
```

将其化简并与之前的合并:

```
CompUnit  ::= FuncDef;

FuncDef   ::= FuncType IDENT "(" ")" Block;
FuncType  ::= "int";
Block         ::= "{" BlockItemUp "}";
BlockItemUp   ::= BlcokItem | BlockItemUp BlockItem
BlockItem     ::= Decl | Stmt;


// Decl Decl Decl

Stmt      ::= "return" Exp ";"
			|  LVal "=" Exp ";" ;
	
Exp         ::= LOrExp;
Number    	::= INT_CONST;
PrimaryExp  ::= "(" Exp ")" | LVal | Number;
Number      ::= INT_CONST;
UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
UnaryOp     ::= "+" | "-" | "!";
MulExp      ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp      ::= MulExp | AddExp ("+" | "-") MulExp;
RelExp      ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp       ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp     ::= EqExp | LAndExp "&&" EqExp;
LOrExp      ::= LAndExp | LOrExp "||" LAndExp;


Decl          ::= ConstDecl | VarDecl ;
ConstDecl     ::= "const" INT ConstDefUp ";";
ConstDefUp    ::= ConstDef  | ConstDefUp "," ConstDef
ConstDef      ::= IDENT "=" Exp;//注意这里需要判断表达式是否是常量

VarDecl		  ::= INT VarDefUp ";";
VarDefUp      ::= ValDef  | ValDefUp "," ValDef 
VarDef        ::= IDENT | IDENT "=" Exp;

LVal          ::= IDENT; //这一部分需要建立符号表来查找相关内容
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
```



### 第七节:支持语句块和作用域

```
Stmt ::= LVal "=" Exp ";"
       | [Exp] ";"
       | Block
       | "return" [Exp] ";";
 []表示重复0或1次

```

### 第八节：支持if语句

```
Stmt ::= LVal "=" Exp ";"
       | [Exp] ";"
       | Block
       | "return" [Exp] ";";
       |"if" "(" Exp ")" Stmt ["else" Stmt]
       | "while" "(" Exp ")" Stmt
       | "break" ";"
       | "continue" ";"
```



### 第九节：支持函数定义和调用

```c
CompUnit    ::= [CompUnit] FuncDef;

FuncDef     ::= FuncType IDENT "(" [FuncFParams] ")" Block;
FuncType    ::= "void" | "int";
FuncFParams ::= FuncFParam {"," FuncFParam};
FuncFParam  ::= BType IDENT;

UnaryExp    ::= ...
              | IDENT "(" [FuncRParams] ")"
              | ...;
FuncRParams ::= Exp {"," Exp};


// 修改
// 需要像之前的的BlockItem一样把函数递归解析放到一个集合中
// 函数参数也是
CompUnit    ::= FuncDefUp
FuncDefUp   ::= FuncDef
    		  | FuncDefUp Funcdef
FuncDef     ::= FuncType IDENT "(" [FuncFParams] ")" Block;
FuncType    ::= "void" | "int";
FuncFParams ::= FuncFParamUp
FuncFParamUp ::= FuncFParam
    		   |FuncFParamUp ',' FuncFParam
FuncFParam  ::= INT IDENT;
UnaryExp    ::= ...
              | IDENT "(" [FuncRParams] ")"
              | ...;
FuncRParams ::= FuncRParamUp
FuncRParamUp 	::= Exp
    		    |   FuncRParamUp ',' Exp
```

```c
// 支持全局变量
CompUnit ::= [CompUnit] (Decl | FuncDef);

// 修改后的语法
TranslationUnit ::= Compunit
Compunit ::= CompunitItem
			| Compunit CompunitItem
CompunitItem  ::= Decl | FuncDef
```



### 第十节：支持多维数组定义

```c
ConstDef   ::= IDENT {"[" ConstExp "]"} "=" ConstInitVal;
ConstInitVal ::= ConstExp | "{" [ConstInitVal {"," ConstInitVal}] "}";
VarDef     ::= IDENT {"[" ConstExp "]"}
			| IDENT {"[" ConstExp "]"} "=" InitVal;
InitVal    ::= Exp | "{" [InitVal {"," InitVal}] "}";
ConstExp ::= Exp;
LVal          ::= IDENT {"[" Exp "]"};
```

==这部分不再变化==

```c
ConstDef   ::= IDENT [ArrayExpList] "=" InitValList;
ArrayExpList  ::= "[" Exp "]"
	  		  | ArrayExpList "[" Exp "]"
InitValList ::= Exp
			  |  "{" "}"
			  |  "{" InitVal "}"

InitVal  ::= InitValList
	      |  InitVal "," InitValList
VarDef     ::= IDENT [ArrayExpList]
			 | IDENT [ArrayExpList] "=" InitValList;
//理论上 InitVal 与 ConstInitVal 不一样
LVal ::= IDENT [ArrayExpList]
```





完整的文法子集如下：

```
翻译单元   		TranslationUnitAst 	::= compUnit
编译单元   		CompUnit      		::=  Decl | FuncDef ;
                             		| CompUnit (Decl | FuncDef);
声明       	Decl				 ::= ConstDecl | VarDecl;
常量声明       ConstDecl     		::= "const" INT ConstDefList ";";
声明列表       ConstDefList  		::= ConstDef
                        			| ConstDefList "," ConstDef
函数类型       FuncType       		::= "int" | "void";
常量定义       ConstDef      		::= IDENT "=" InitValList;
                            		| IDENT ArrayExpList "=" InitValList
数组声明       ArrayExpList   		::= '[' Exp ']'
                        			|  ArrayExpList '[' Exp ']'
初始化值列表    InitValList  		   ::= Exp
                       				| "{"  "}"
                       				| "{" InitVal "}"
初始化值       InitVal				::= InitValList
                      				| InitVal InitValList

变量声明       VarDecl       	::= FuncType VarDefList ";";
变量定义列表    VarDefList       ::= VarDef
                        			| VarDefList ',' VarDef
变量定义       VarDef       	::= IDENT 
                                | IDENT ArrayExpList "=" InitValL
                                | IDENT ArrayExpList 
                                | IDENT "=" InitValList;

函数定义     FuncDef      		::= FuncType IDENT "("  ")" Block
                      	     	 | FuncType IDENT "(" FuncFParamList ")" Block;
形参列表     FuncFParamList   	::= FuncFParam 
                                | FuncFParamList FuncFParam;

形参定义    FuncFParam   ::= FuncType IDENT  
                        | FuncType IDENT "[" "]" 
                        | FuncType IDENT "[" "]" ArrayExpList
                        | FuncType IDENT  ArrayExpList
 
语句块      Block         	::= "{" BlockItemList "}";
语句块列表   BlockItemList 	::= BlockItem
                        	| BlockItemList BlockItem
语句块项     BlockItem     ::= Decl | Stmt;
语句        Stmt         ::= LVal "=" Exp ";"
                        | [Exp] ";"
                        | Block
                        | "if" "(" Exp ")" Stmt ["else" Stmt]
                        | "while" "(" Exp ")" Stmt
                        | "break" ";"
                        | "continue" ";"
                        | "return" [Exp] ";";
表达式      Exp          ::= LOrExp;
左值        LVal          ::= IDENT [ArrayExpList] ; 
基本表达式   PrimaryExp    ::= "(" Exp ")" | LVal | Number;
数值        Number        ::= INT_CONST;
一元表达式   UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParamList] ")" | UnaryOp UnaryExp;
一元运算符   UnaryOp       ::= "+" | "-" | "!";
函数实参列表 FuncRParamList :: Exp
                           | FuncRParamList "," Exp
乘法表达式   MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
加法表达式   AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;
关系表达式   RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
相等表达式   EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;
逻辑与表达式  LAndExp       ::= EqExp | LAndExp "&&" EqExp;
逻辑或表达式  LOrExp        ::= LAndExp | LOrExp "||" LAndExp;
```



==考虑如何展开表达式语句中的重复语句==

```
  std::string pre_name = BinaryTypeToString(binary_expr_ast->type);
  auto left = dynamic_cast<PrimaryExprAst*>(binary_expr_ast->left.get());
  auto right = dynamic_cast<PrimaryExprAst*>(binary_expr_ast->right.get());
  if (left || right){
	j_son_.BeganWrite(pre_name+"BinaryExp");
	if(left){
	  left->accept(this);
	  j_son_.BeganWrite(binary_expr_ast->op);
	  j_son_.EndWrite();
	}
	assert(right);
	right->accept(this);
	j_son_.EndWrite();
  } else{
	if (binary_expr_ast->left)
		binary_expr_ast->left->accept(this);
	binary_expr_ast->right->accept(this);
  }
```

如果是二元节点的话则就需要将两边的表达式同时递归到最底层

如果是一元节点就需要将右节点递归到最底层



对于递归文法，使用堆栈将其取出。
