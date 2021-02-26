ref: https://cse.iitkgp.ac.in/~bivasm/notes/LexAndYaccTutorial.pdf

compile to parser: `yacc -d comp.y && lex comp.l && cc lex.yy.c y.tab.c parse.c`
compile to intepreter: `yacc -d comp.y && lex comp.l && cc lex.yy.c y.tab.c interpreter.c`

status: WIP
