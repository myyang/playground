%{
    #include "y.tab.h"
%}

%%

";"                 { return COLON; }
"="                 { return EQ; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MULTI; }
"/"                 { return DIVIDE; }
"print"             { return print; }
"exit"              { return c_exit; }
"show"              { return c_exit; }
[a-zA-Z]            { yylval.id = yytext[0]; return identifier; }
[0-9]+(\.[0-9]+)?   { yylval.num = atof(yytext); return number; }
[ \t\n]             { ; }
.                   { ECHO; yyerror("error token"); }

%%

#ifndef yywrap
int yywrap() { return 1; }
#endif
