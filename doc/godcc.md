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
    "children": [
        {
            "children": [],
            "name": "B"
        },
        {
            "children": [
                {
                    "children": [
                        {
                            "children": [],
                            "name": "I"
                        }
                    ],
                    "name": "E"
                },
                {
                    "children": [],
                    "name": "F"
                }
            ],
            "name": "C"
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
    ],
    "name": "A"
}
```
