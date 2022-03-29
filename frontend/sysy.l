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


%}

/*空格和注释等*/
WhiteSpace [ \t\n\r]*
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
                    began_colum +=yyleng;
                    return INT;
                }
"return"        {
                     file_out("return","return");
                     began_colum +=yyleng;
                     return RETURN;
                }
{Identifier}    {
                    yylval.str_val = new string(yytext);
                    file_out(yytext,"Identifier");
                    began_colum +=yyleng;
                    return IDENT;
                }
{Decimal}       {
                    yylval.int_val = strtol(yytext, nullptr, 0);
                    file_out(yytext,"Decimal");
                    began_colum +=yyleng;
                    return INT_CONST;
                }
{Octal}         {
                    yylval.int_val = strtol(yytext, nullptr, 0);
                    file_out(yytext,"Octal");
                    began_colum +=yyleng;
                    return INT_CONST;
                }
{Hex}           {
                    yylval.int_val = strtol(yytext, nullptr, 0);
                    file_out(yytext,"Hex");
                    began_colum +=yyleng;
                    return INT_CONST;
                }
.               {
                    file_out(yytext,yytext);
                    began_colum +=yyleng;
                    return yytext[0];
                }
%%

void file_out(const char* word,const char* type){
    fprintf(yyout,"[@%d,%d:%d=\"%s\",<%s>,%d:%d]\n",token_num,began_colum,began_colum+yyleng-1,word,type,yylineno,began_colum);
    token_num++;
}