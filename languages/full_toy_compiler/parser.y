%{
    #include "node.h"

    NBlock *programBlock;

    extern int yylex();
    void yyerror(const char *s) { printf("yyerror: %s\n", s); }
%}

%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    NIdentifier *ident;
    NVariableDeclaration *var_decl;
    ExpressionList *exprvec;
    VariableList *varvec;
    std::string *string;
    int token;
}

%token <string> TIDENTIFIER TINTEGER TDOUBLE
%token <token> TCEQ TCNE TCGE TCGT TCLE TCLT TEQUAL
%token <token> TLPAREN TRPAREN TLCURLY TRCURLY TDOT TCOMMA TSC
%token <token> TPLUS TMINUS TMUL TDIV

%type <ident> ident
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <expr> numeric expr
%type <block> program stmts block
%type <stmt> stmt var_decl func_decl
%type <token> binop

%right TEQUAL
%left TCEQ TCNE TCGE TCGT TCLE TCLT
%left TPLUS TMINUS
%left TMUL TDIV

%%

program:
    stmts   { programBlock = $1; }
;

stmts:
    stmt        { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
|   stmts stmt  { $1->statements.push_back($<stmt>2); }
;

stmt:
    var_decl TSC    { $$ = $1; }
|   func_decl
|   expr TSC        { $$ = new NExpressionStatement(*$1); }
;

block:
    TLCURLY stmts TRCURLY   { $$ = $2; }
|   TLCURLY TRCURLY         { $$ = new NBlock(); }
;

var_decl:
    ident ident TEQUAL expr     { $$ = new NVariableDeclaration(*$1, *$2, $4); }
|   ident ident                 { $$ = new NVariableDeclaration(*$1, *$2); }
;

func_decl:
    ident ident TLPAREN func_decl_args TRPAREN block    { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
;

func_decl_args:
    /* empty */                         { $$ = new VariableList(); }
|   func_decl_args TCOMMA var_decl      { $1->push_back($<var_decl>3); }
|   var_decl                            { $$ = new VariableList(); $$->push_back($<var_decl>1); }
;

ident:
    TIDENTIFIER     { $$ = new NIdentifier(*$1); delete $1; }
;

numeric:
    TDOUBLE         { $$ = new NDouble(atof($1->c_str())); delete $1; }
|   TINTEGER        { $$ = new NInteger(atol($1->c_str())); delete $1; }
;

expr:
    ident TEQUAL expr                       { $$ = new NAssignment(*$<ident>1, *$3); }
|   ident TLPAREN call_args TRPAREN         { $$ = new NMethodCall(*$<ident>1, *$3); delete $3; }
|   ident                                   { $<ident>$ = $1; }
|   numeric
|   expr binop expr                         { $$ = new NBinaryOperator(*$1, $2, *$3); }
|   TLPAREN expr TRPAREN                    { $$ = $2; }
;

call_args:
    /* empty */             { $$ = new ExpressionList(); }
|   call_args TCOMMA expr   { $1->push_back($3); }
|   expr                    { $$ = new ExpressionList(); $$->push_back($1); }
;

binop:
    TCEQ | TCNE | TCGE | TCGT | TCLE | TCLT |
    TPLUS | TMINUS | TMUL | TDIV
;

%%
