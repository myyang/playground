%{
#include <stdlib.h>
#include "node.h"
#include "y.tab.h"

void yyerror(char *s);
%}

%%

"=="                { return L_EQ; }
"!="                { return L_NE; }
">="                { return L_GE; }
">"                 { return L_GT; }
"<="                { return L_LE; }
"<"                 { return L_LT; }
"="                 { return ASSIGN; }
";"                 { return SEMI; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MULTI; }
"/"                 { return DIVIDE; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LCURLY; }
"}"                 { return RCURLY; }
"if"                { return IF; }
"else"              { return ELSE; }
"while"             { return WHILE; }
"print"             { return PRINT; }
[0-9]+              { yylval.num = atoi(yytext); return NUMBER; }
[a-z]               { yylval.id = *yytext; return VARIABLE; }
[ \n\t]+    ;
"//".*\n    ;
.           yyerror("illegal token");

%%

int yywrap() { return 1; }
