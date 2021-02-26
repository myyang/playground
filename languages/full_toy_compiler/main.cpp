#include <iostream>
#include "node.h"
#include "codegen.h"

extern NBlock* programBlock;
extern int yyparse();

int main()
{
    yyparse();
    std::cout << programBlock << std::endl;

    CodeGenContext context;
    context.generateCode(*programBlock);
    context.runCode();

    return 0;
}
