%start ROOT

%token EQ
%token NE
%token LT
%token LE
%token GT
%token GE
%token PLUS
%token MINUS
%token MULTI
%token DIVIDE
%token LPAREN
%token RPAREN
%token ASSIGN
%token SEMICOLON
%token IF
%token THEN
%token ELSE
%token FI
%token WHILE
%token DO
%token OD
%token PRINT
%token NUMBER
%token NAME

%%

ROOT:
    stmtseq { execute($1) }
;

stmt:
    designator ASSIGN expr { $$ = assignment($1, $3); }
|   PRINT expr { $$ = print($2); }
|   IF expr THEN stmtseq ELSE stmtseq FI { $$ = ifstmt($2, $4, $6); }
|   IF expr THEN stmtseq FI { $$ = ifstmt($2, $4); }
|   WHILE expr DO stmtseq OD { $$ = whilestmt($2, $4); }
;

stmtseq:
    stmtseq SEMICOLON stmt { $$ = seq($1, $3); }
|   stmt { $$ = $1; }
;

expr:
    expr2 { $$ = $1; }
|   expr2 EQ expr2 { $$ = eq($1, $3); }
|   expr2 NE expr2 { $$ = ne($1, $3); }
|   expr2 GT expr2 { $$ = gt($1, $3); }
|   expr2 GE expr2 { $$ = ge($1, $3); }
|   expr2 LT expr2 { $$ = lt($1, $3); }
|   expr2 LE expr2 { $$ = le($1, $3); }
;

expr2:
    expr3 { $$ = $1; }
|   expr2 PLUS expr3 { $$ = plus($1, $3); }
|   expr2 MINUS expr3 { $$ = minus($1, $3); }
;

expr3:
    expr4 { $$ = $1; }
|   expr3 MULTI expr4 { $$ = multi($1, $3); }
|   expr3 DIVIDE expr4 { $$ = divide($1, $3); }
;

expr4:
    PLUS expr4 { $$ = $2; }
|   MINUS expr4 { $$ = neg($2); }
|   LPAREN expr4 LPAREN { $$ = $2; }
|   NUMBER { $$ = number($1); }
|   designator { $$ = $1; }
;

designator:
    NAME { $$ = name($1); }
;

%%
