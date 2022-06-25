%option noyywrap
%option nounput
%option noinput
%option yylineno
%option nodefault

%{
#include<iostream>
#include<string>
#include"parser.hpp"
#include <stdio.h>
using namespace std;

void file_out(const char* word,const char* type);
static int began_colum= 0;
static int token_num=0;

#define YY_USER_ACTION \
yylloc.first_line = yylloc.last_line = yylineno; \
yylloc.first_column = began_colum; \
yylloc.last_column = began_colum + yyleng - 1; \
began_colum += yyleng;

%}

/*空格和注释等*/
WhiteSpace [ \t\r]*
LineComment "//".*$
/* 标识符*/
Identifier [a-zA-Z_][a-zA-Z0-9_]*

/*整型数字*/
Decimal [1-9][0-9]*
Octal 0[0-7]*
Hex 0[xX][0-9a-fA-F]+

%%
\n              {began_colum=0;}
{WhiteSpace}    {began_colum += yyleng;}
{LineComment}   {}

"int"           {
                    file_out("int","int");
                    yylval.str_val=new string("int");
                    //began_colum +=yyleng;
                    return INT;
                }
"void"           {
                    file_out("void","void");
                    yylval.str_val=new string("void");
                    //began_colum +=yyleng;
                    return VOID;
                }
"const"         {
                    file_out("const","const");
                     yylval.str_val=new string("const");
                    //began_colum +=yyleng;
                    return CONST;
                }
"if"            {
                    file_out("if","if");
                    yylval.str_val=new string("if");
                    //began_colum +=yyleng;
                    return IF;
                }
"else"          {
                    file_out("else","else");
                    yylval.str_val=new string("else");
                    //began_colum +=yyleng;
                    return ELSE;
                }
"for"           {
                    file_out("for","for");
                    yylval.str_val=new string("for");
                    //began_colum +=yyleng;
                    return FOR;
                }
"while"         {
                    file_out("while","while");
                    yylval.str_val=new string("while");
                    //began_colum +=yyleng;
                    return WHILE;
                }
"break"          {
                    file_out("break","break");
                    yylval.str_val=new string("break");
                    //began_colum +=yyleng;
                    return BREAK;
                }
"continue"       {
                    file_out("continue","continue");
                    yylval.str_val=new string("continue");
                    //began_colum +=yyleng;
                    return CONTINUE;
                }
 "<"            {
                    file_out("<","<");
                     yylval.str_val=new string("<");
                    //began_colum +=yyleng;
                    return LT;
                }
 ">"            {
                    file_out(">",">");
                     yylval.str_val=new string(">");
                    //began_colum +=yyleng;
                    return GT;
                }

 "["            {
                    file_out("[","[");
                     yylval.str_val=new string("[");
                    //began_colum +=yyleng;
                    return '[';
                }
 "]"            {
                    file_out("[","[");
                     yylval.str_val=new string("[");
                    //began_colum +=yyleng;
                    return ']';
                 }
 "{"            {
                    file_out("{","{");
                     yylval.str_val=new string("{");
                    //began_colum +=yyleng;
                    return '{';
                 }
 "}"              {
                     file_out("}","}");
                     yylval.str_val=new string("}");
                    //began_colum +=yyleng;
                    return '}';
                }
 "("            {
                    file_out("(","(");
                     yylval.str_val=new string("(");
                    //began_colum +=yyleng;
                    return '(';
                }
 ")"            {
                    file_out(")",")");
                     yylval.str_val=new string(")");
                    //began_colum +=yyleng;
                    return ')';
                }
"<="            {
                    file_out("<=","<=");
                     yylval.str_val=new string("<=");
                    //began_colum +=yyleng;
                    return LE;
                }
">="            {
                    file_out(">=",">=");
                     yylval.str_val=new string(">=");
                    //began_colum +=yyleng;
                    return GE;
                }

"=="            {
                    file_out("==","==");
                     yylval.str_val=new string("==");
                    //began_colum +=yyleng;
                    return EQ;
                }
"!="            {
                    file_out("!=","!=");
                     yylval.str_val=new string("!=");
                    //began_colum +=yyleng;
                    return NE;
                }
"&&"            {
                    file_out("&&","&&");
                    //began_colum +=yyleng;
                     yylval.str_val=new string("&&");
                    return AND;
                }

"||"            {
                    file_out("||","||");
                     yylval.str_val=new string("||");
                    //began_colum +=yyleng;
                    return OR;
                }
"++"            {
                    file_out("++","++");
                     yylval.str_val=new string("++");
                    //began_colum +=yyleng;
                    return INC;
                }
"--"            {
                    file_out("--","--");
                     yylval.str_val=new string("--");
                    //began_colum +=yyleng;
                    return DEC;
                }

"return"        {
                     file_out("return","return");
                      yylval.str_val=new string("return");
                     //began_colum +=yyleng;
                     return RETURN;
                }
{Identifier}    {
                    yylval.str_val = new string(yytext);
                    file_out(yytext,"Identifier");
                    //began_colum +=yyleng;
                    return IDENT;
                }
{Decimal}       {
                    yylval.int_val = strtol(yytext, nullptr, 0);
                    file_out(yytext,"Decimal");
                    //began_colum +=yyleng;
                    return INT_CONST;
                }
{Octal}         {
                    yylval.int_val = std::stoi(yytext, nullptr, 8);
                    file_out(yytext,"Octal");
                    //began_colum +=yyleng;
                    return INT_CONST;
                }
{Hex}           {
                    yylval.int_val = std::stoi(yytext, nullptr, 16);
                    file_out(yytext,"Hex");
                    //began_colum +=yyleng;
                    return INT_CONST;
                }
";"             {
                    file_out(";",";");
                    //began_colum +=yyleng;
                    return ';';
                }
","             {
                    file_out(",",",");
                    //began_colum +=yyleng;
                    return ',';
                }
.                 {
                    file_out(yytext,"error");
                    //began_colum +=yyleng;
                    return yytext[0];
                  }
%%

void file_out(const char* word,const char* type){
    fprintf(yyout,"[@%d,%d:%d=\"%s\",<%s>,%d:%d]\n",token_num,began_colum,began_colum+yyleng-1,word,type,yylineno,began_colum);
    token_num++;
    if(strcmp(type,"error")==0){
        return;
    }
}