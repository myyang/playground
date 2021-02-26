%{

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void yyerror(char *s);

double symbols[52];
double symbolVal(char sym);
void updateSymbolVal(char sym, double val);
void showSymbols();

%}

%union { double num; char id; }

%start stmt

%token print
%token show
%token c_exit
%token COLON
%token EQ
%token PLUS
%token MINUS
%token MULTI
%token DIVIDE
%token <num> number
%token <id> identifier

%type <num> stmt expr term
%type <id> assignment

%left PLUS MINUS
%left MULTI DEVIDE
%nonassoc UMINUS

%%

stmt:
    assignment COLON            {;}
|   show COLON                  { showSymbols(); }
|   c_exit COLON                { exit(EXIT_SUCCESS); }
|   print expr COLON            { printf("printing: %f\n", $2); }
|   stmt assignment COLON       {;}
|   stmt c_exit COLON           { exit(EXIT_SUCCESS); }
|   stmt print expr COLON       { printf("printing: %f\n", $3); }
;

assignment:
    identifier EQ expr          { updateSymbolVal($1, $3); }
;

expr:
    term                        { $$ = $1; }
|   MINUS term %prec UMINUS     { $$ = -$2; }
|   expr PLUS expr              { $$ = $1 + $3; }
|   expr MINUS expr             { $$ = $1 - $3; }
|   expr MULTI expr             { $$ = $1 * $3; }
|   expr DIVIDE expr            { $$ = $1 / $3; }
;

term:
    number              { $$ = $1; }
|   identifier          { $$ = symbolVal($1); }
;

%%

void yyerror(char *s) { fprintf(stderr, "unexpected charater: %s\n", s); }

int symbolIdx(char symbol)
{
    int idx = -1;
    if (islower(symbol))
        idx = symbol - 'a' + 26;
    else
        idx = symbol - 'A';
    return idx;
}

double symbolVal(char symbol) { return symbols[symbolIdx(symbol)]; }

void updateSymbolVal(char symbol, double val) { symbols[symbolIdx(symbol)] = val; }

void showSymbols(void)
{
    int i = 0;
    while (i < 52)
    {
        printf("key: %d, val: %f\n", i, symbols[i]);
        ++i;
    }
}

int main(void)
{
    int i = 0;
    while (i < 52)
    {
        symbols[i++] = 0;
    }

    return yyparse();
}
