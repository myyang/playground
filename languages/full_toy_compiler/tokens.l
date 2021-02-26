%{
    #include <string>
    #include "node.h"
    #include "parser.hpp"

    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng);
    #define TOKEN(t) (yylval.token = t)

    extern "C" int yywrap() {};
%}

%%

[ \t\n]         ;
"//".*\n        ;
[a-zA-Z_][a-zA-Z0-9_]*      { SAVE_TOKEN; return TIDENTIFIER; }
[0-9]+.[0-9]*               { SAVE_TOKEN; return TDOUBLE; }
[0-9]*                      { SAVE_TOKEN; return TINTEGER; }
"=="        return TOKEN(TCEQ);
"!="        return TOKEN(TCNE);
">="        return TOKEN(TCGE);
"<="        return TOKEN(TCLE);
">"         return TOKEN(TCGT);
"<"         return TOKEN(TCLT);
"="         return TOKEN(TEQUAL);
"("         return TOKEN(TLPAREN);
")"         return TOKEN(TRPAREN);
"{"         return TOKEN(TLCURLY);
"}"         return TOKEN(TRCURLY);
"."         return TOKEN(TDOT);
","         return TOKEN(TCOMMA);
";"         return TOKEN(TSC);
"+"         return TOKEN(TPLUS);
"-"         return TOKEN(TMINUS);
"*"         return TOKEN(TMUL);
"/"         return TOKEN(TDIV);
.           { printf("Unknown token: %s!\n", yytext); yyterminate(); }

%%
