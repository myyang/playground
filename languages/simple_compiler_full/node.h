#ifndef SIMPLE_COMPILER_NODE_H
#define SIMPLE_COMPILER_NODE_H

typedef enum { typeConst, typeId, typeOp } nodeEnum;

// constants
typedef struct {
    int value;
} constNodeType;

// identifiers
typedef struct {
    int i;
} idNodeType;

// operators
typedef struct {
    // operator
    int opr;
    // number of operands
    int nops;
    // operands
    struct nodeTypeTag **op;

} opNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;

    union {
        constNodeType constNT;
        idNodeType idNT;
        opNodeType opNT;
    };
} nodeType;

extern int sym[26];
#endif
