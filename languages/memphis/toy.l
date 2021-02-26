%{
    #include "y.tab.h"
    extern int yylval;
%}
%%

"="         { return EQ; }
"!="        { return NE; }
"<"         { return LT; }
"<="        { return LE; }
">"         { return GT; }
">="        { return GE; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULTI; }
"/"         { return DIVIDE; }
"("         { return LPAREN; }
")"         { return RPAREN; }
":="        { return ASSIGN; }
";"         { return SEMICOLON; }
"IF"        { return IF; }
"THEN"      { return THEN; }
"ELSE"      { return ELSE; }
"FI"        { return FI; }
"WHILE"     { return WHILE; }
"DO"        { return DO; }
"OD"        { return OD; }
"PRINT"     { return PRINT; }
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[a-z]       { yylval = yytext[0]-'a'; return NAME; }
\           { ; }
\n          { newline(); }
\t          { ; }
"//".*\n    { newline(); }
.           { yyerror("illegal token"); }

%%

#ifndef yywrap
yywrap() { return 1; }
#endif
