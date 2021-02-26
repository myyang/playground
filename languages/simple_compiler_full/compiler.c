#include <stdio.h>
#include "node.h"
#include "y.tab.h"

static int lbl;

int execute(nodeType *p)
{
    int lbl1, lbl2;

    if (!p) return 0;
    switch (p->type)
    {
        case typeConst:
            printf("\tpush\t%d\n", p->constNT.value);
            break;
        case typeId:
            printf("\tpush\t%c\n", p->idNT.i + 'a');
            break;
        case typeOp:
            switch (p->opNT.opr)
            {
                case ASSIGN:
                    execute(p->opNT.op[1]);
                    printf("\tpop\t%c\n", p->opNT.op[0]->idNT.i + 'a');
                    break;
                case PRINT:
                    execute(p->opNT.op[0]);
                    printf("\tprint\n");
                    break;
                case UMINUS:
                    execute(p->opNT.op[0]);
                    printf("\tneg\n");
                    break;
                case WHILE:
                    printf("L%03d\n", lbl1 = lbl++);
                    execute(p->opNT.op[0]);
                    printf("\tjz\tL%03d\n", lbl2 = lbl++);
                    execute(p->opNT.op[1]);
                    printf("\tjmp\tL%03d\n", lbl);
                    printf("L%03d\n", lbl2);
                    break;
                case IF:
                    execute(p->opNT.op[0]);
                    if (p->opNT.nops > 2)
                    {
                        /* if else */
                        printf("L%03d\n", lbl1 = lbl++);
                        execute(p->opNT.op[1]);
                        printf("\tjz\tL%03d\n", lbl2 = lbl++);
                        execute(p->opNT.op[2]);
                        printf("\tjmp\tL%03d\n", lbl);
                        printf("L%03d\n", lbl2);
                    }
                    else
                    {
                        /* if */
                        printf("L%03d\n", lbl1 = lbl++);
                        execute(p->opNT.op[1]);
                        printf("L%03d\n", lbl1);
                    }
                    break;
                default:
                    execute(p->opNT.op[0]);
                    execute(p->opNT.op[1]);
                    switch (p->opNT.opr)
                    {
                        case PLUS: printf("\tadd\n"); break;
                        case MINUS: printf("\tsub\n"); break;
                        case MULTI: printf("\tmul\n"); break;
                        case DIVIDE: printf("\tdiv\n"); break;
                        case L_EQ: printf("\tcompEQ\n"); break;
                        case L_NE: printf("\tcompNE\n"); break;
                        case L_GE: printf("\tcompGE\n"); break;
                        case L_GT: printf("\tcompGT\n"); break;
                        case L_LE: printf("\tcompLE\n"); break;
                        case L_LT: printf("\tcompLT\n"); break;
                    }
            }
            break;
    }
    return 0;
}
