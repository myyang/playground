
# ----
# vars
# ----

CC				?= cc
YACC			?= bison
LEX				?= flex

# Automake-like silent rules
V ?= 0
AT_RUN			  = $(AT_RUN_$(V))
AT_RUN_0		  = @echo "  RUN          "$@;
AT_RUN_1		  =

CMDS = \
	clean \
	yacc \
	lex \
	main

clean:
	$(AT_RUN) rm -rf a.out

yacc:
	$(AT_RUN) $(YACC) -d comp.y

lex:
	$(AT_RUN) $(LEX) comp.l

parser: yacc lex
	$(AT_RUN) $(CC) lex.yy.c y.tab.c parser.c

interpreter: yacc lex
	$(AT_RUN) $(CC) lex.yy.c y.tab.c interpreter.c

compiler: yacc lex
	$(AT_RUN) $(CC) lex.yy.c y.tab.c compiler.c
