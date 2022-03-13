%option noyywrap
%option nounput
%option noinput
%option yylineno
%option nodefault

%{
#include<iostream>
#include<string>
#include"parser.tab.hpp"
using namespace std;
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
{WhiteSpace}    {}
{LineComment}   {}
"int"           {return INT;}
"return"        {return RETURN;}
{Identifier}    { yylval.str_val = new string(yytext);return IDENT;}
{Decimal}       { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Octal}         { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Hex}           { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
.               { return yytext[0]; }
%%