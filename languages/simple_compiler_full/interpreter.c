#include <stdio.h>
#include "node.h"
#include "y.tab.h"

int execute(nodeType *p)
{
    if (!p) return 0;
    switch (p->type)
    {
        case typeConst: return p->constNT.value;
        case typeId:    return sym[p->idNT.i];
        case typeOp:
            switch (p->opNT.opr)
            {
                case ASSIGN:
                    sym[p->opNT.op[0]->idNT.i] = execute(p->opNT.op[1]);
                    return 0;
                case PRINT:
                    printf("%d\n", execute(p->opNT.op[0]));
                    return 0;
                case SEMI:
                    execute(p->opNT.op[0]);
                    return execute(p->opNT.op[1]);
                // flow
                case WHILE:
                    while (execute(p->opNT.op[0])) execute(p->opNT.op[1]);
                    return 0;
                case IF:
                    if (execute(p->opNT.op[0]))
                        execute(p->opNT.op[1]);
                    else if (p->opNT.nops > 2)
                        execute(p->opNT.op[2]);
                    return 0;
                // arithmetic
                case UMINUS: return -execute(p->opNT.op[0]);
                case PLUS: return execute(p->opNT.op[0]) + execute(p->opNT.op[1]);
                case MINUS: return execute(p->opNT.op[0]) - execute(p->opNT.op[1]);
                case MULTI: return execute(p->opNT.op[0]) * execute(p->opNT.op[1]);
                case DIVIDE:return execute(p->opNT.op[0]) / execute(p->opNT.op[1]);
                case L_EQ: return execute(p->opNT.op[0]) == execute(p->opNT.op[1]);
                case L_NE: return execute(p->opNT.op[0]) != execute(p->opNT.op[1]);
                case L_GE: return execute(p->opNT.op[0]) >= execute(p->opNT.op[1]);
                case L_GT: return execute(p->opNT.op[0]) > execute(p->opNT.op[1]);
                case L_LE: return execute(p->opNT.op[0]) <= execute(p->opNT.op[1]);
                case L_LT: return execute(p->opNT.op[0]) < execute(p->opNT.op[1]);
            }
    }

    return 0;
}
