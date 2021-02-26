%{

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "node.h"

// prototypes
nodeType *opFn(int oper, int nops, ...);
nodeType *idFn(int i);
nodeType *constFn(int value);
void freeNode(nodeType *p);
int execute(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];

%}

%union {
    int num;
    char id;
    nodeType *ptr;
};

%token <num> NUMBER;
%token <id> VARIABLE;
%token ASSIGN SEMI PRINT;
%token LPAREN RPAREN LCURLY RCURLY;
// flow
%token IF ELSE WHILE;
// logic
%token L_EQ L_NE L_GE L_GT L_LE L_LT;
// arithmetic
%token PLUS MINUS MULTI DIVIDE

%right ASSIGN
%left L_GE L_GT L_LE L_LT L_EQ L_NE
%left PLUS MINUS
%left MULTI DIVIDE
%nonassoc UMINUS

%type <ptr> stmt expr stmts

%%

program:
    function    { exit(0); }
;

function:
    function stmt   { execute($2); freeNode($2); }
|   /* NULL */
;

stmt:
    SEMI                                            { $$ = opFn(SEMI, 2, NULL, NULL); }
|   expr SEMI                                       { $$ = $1; }
|   VARIABLE ASSIGN expr SEMI                       { $$ = opFn(ASSIGN, 2, idFn($1), $3); }
|   PRINT expr SEMI                                 { $$ = opFn(PRINT, 1, $2); }
|   WHILE LPAREN expr RPAREN LCURLY stmts RCURLY     { $$ = opFn(WHILE, 2, $3, $6); }
|   IF LPAREN expr RPAREN LCURLY stmts RCURLY        { $$ = opFn(IF, 2, $3, $6); }
|   IF LPAREN expr RPAREN LCURLY stmts RCURLY ELSE LCURLY stmts RCURLY       { $$ = opFn(IF, 3, $3, $6, $10); }
|   LCURLY stmts RCURLY     { $$ = $2; }
;

stmts:
    stmt        { $$ = $1; }
|   stmts stmt  { $$ = opFn(SEMI, 2, $1, $2); }
;

expr:
    NUMBER      { $$ = constFn($1); }
|   VARIABLE    { $$ = idFn($1); }
|   MINUS expr %prec UMINUS     { $$ = opFn(UMINUS, 1, $2); }
|   expr PLUS expr              { $$ = opFn(PLUS, 2, $1, $3); }
|   expr MINUS expr             { $$ = opFn(MINUS, 2, $1, $3); }
|   expr MULTI expr             { $$ = opFn(MULTI, 2, $1, $3); }
|   expr DIVIDE expr            { $$ = opFn(DIVIDE, 2, $1, $3); }
|   expr L_EQ expr              { $$ = opFn(L_EQ, 2, $1, $3); }
|   expr L_NE expr              { $$ = opFn(L_NE, 2, $1, $3); }
|   expr L_GE expr              { $$ = opFn(L_GE, 2, $1, $3); }
|   expr L_GT expr              { $$ = opFn(L_GT, 2, $1, $3); }
|   expr L_LE expr              { $$ = opFn(L_LE, 2, $1, $3); }
|   expr L_LT expr              { $$ = opFn(L_LT, 2, $1, $3); }
|   LPAREN expr RPAREN          { $$ = $2; }
;

%%

void freeNode(nodeType *p)
{
    if (!p) return;
    if (p->type == typeOp)
    {
        int i;
        for (i = 0; i < p->opNT.nops; ++i) freeNode(p->opNT.op[i]);
        free(p->opNT.op);
    }
    free(p);
}

#define SIZEOF_NODETYPE ((char *)&p->constNT - (char *)p)

nodeType *constFn(int val)
{
    nodeType *p;

    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    // assign info
    p->type = typeConst;
    p->constNT.value = val;

    return p;
}

nodeType *idFn(int i)
{

    nodeType *p;

    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    // assign info
    p->type = typeId;
    p->idNT.i = i;

    return p;
}

nodeType *opFn(int oper, int nops, ...)
{
    nodeType *p;

    int nodeSize = sizeof(nodeType);
    printf("oper: %d, nops: %d, size: %d\n", oper, nops, nodeSize);

    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");
    if (nops > 0 && (p->opNT.op = malloc(nops * nodeSize)) == NULL)
        yyerror("out of memory for ops");

    // assign info
    p->type = typeOp;
    p->opNT.opr = oper;
    p->opNT.nops = nops;

    va_list ap;
    int i;
    va_start(ap, nops);
    for (i = 0; i < nops; ++i)
        p->opNT.op[i] = va_arg(ap, nodeType*);
    va_end(ap);

    return p;
}

void yyerror(char *s) { fprintf(stderr, "yyerror: %s\n", s); }

int main(void)
{
    return yyparse();
}
