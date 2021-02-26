
# ----
# vars
# ----

CXX				?= clang++
CXXFLAGS		?=-g -std=c++17
LLVM_CONFIG		?= llvm-config
YACC			?= bison
LEX				?= flex

# Automake-like silent rules
V ?= 0
AT_RUN			  = $(AT_RUN_$(V))
AT_RUN_0		  = @echo "  RUN          "$@;
AT_RUN_1		  =

LLVM_CONFIG_FLAGS :=`$(LLVM_CONFIG) --cxxflags --ldflags --system-libs --libs all`

CMDS = \
	clean \
	yacc \
	lex \
	main

clean:
	$(AT_RUN) rm -rf tokens.cpp parser.cpp parser.hpp a.out

yacc:
	$(AT_RUN) $(YACC) -d -o parser.cpp parser.y

lex:
	$(AT_RUN) $(LEX) -o tokens.cpp tokens.l

main: yacc lex
	$(AT_RUN) $(CXX) $(CXXFLAGS) parser.cpp tokens.cpp codegen.cpp main.cpp $(LLVM_CONFIG_FLAGS)

