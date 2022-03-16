%option noyywrap
%option nounput
%option noinput
%option yylineno
%option nodefault

%{
#include<iostream>
#include<string>
#include"parser.tab.hpp"
#include <fstream>
using namespace std;


/*ofstream token_file("scanner_example.tokens");*/
void file_out(const char* word,const char* type);
int began_line =0 ;
int began_colum= 0;
int token_num=0;
ofstream token_file;
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
\n              {began_line++;began_colum=0;}
{WhiteSpace}    {began_colum += yyleng;}
{LineComment}   {began_line++;}
"int"           {
                    began_colum +=yyleng;
                    file_out("int","int");
                    return INT;
                }
"return"        {
                     began_colum +=yyleng;
                     file_out("return","return");
                     return RETURN;
                }
{Identifier}    {
                    yylval.str_val = new string(yytext);
                    began_colum +=yyleng;
                    file_out(yytext,"Identifier");
                    return IDENT;
                }
{Decimal}       {
                    yylval.int_val = strtol(yytext, nullptr, 0);
                    began_colum +=yyleng;
                    file_out(yytext,"Decimal");
                    return INT_CONST;
                }
{Octal}         {
                    yylval.int_val = strtol(yytext, nullptr, 0);
                    began_colum +=yyleng;
                    file_out(yytext,"Octal");
                    return INT_CONST;
                }
{Hex}           {
                    yylval.int_val = strtol(yytext, nullptr, 0);
                    began_colum +=yyleng;
                    file_out(yytext,"Hex");
                    return INT_CONST;
                }
.               {
                    began_colum +=yyleng;
                    file_out(yytext,yytext);
                    return yytext[0];
                }
%%

void file_out(const char* word,const char* type){
    if(!token_file.is_open()){
        return;
    }
    token_file <<"[@" << token_num << ",";
    token_file << began_colum << ":" << began_colum+yyleng << "=" << "'" << word << "'"<< ",";
    token_file << "<'" << type << "'>,";
    token_file << began_line << ":" << began_colum<< "]\n";
}