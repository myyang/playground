#include <iostream>
#include <vector>

#include "llvm/IR/Value.h"

class CodeGenContext;
class NExpression;
class NStatement;
class NVariableDeclaration;

typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NStatement*> StatementList;
typedef std::vector<NVariableDeclaration*> VariableList;


// basic AST node
class Node {
public:
    virtual ~Node() = default;
    virtual llvm::Value *codegen(CodeGenContext& context) = 0;
};

class NExpression : public Node {
};

class NStatement : public Node {
};

class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) { }
    virtual llvm::Value *codegen(CodeGenContext& context);
};

class NDouble : public NExpression {
public:
    double value;
    NDouble(double value) : value(value) { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(std::string name) : name(name) { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NMethodCall : public NExpression {
public:
    const NIdentifier& id;
    ExpressionList args;
    NMethodCall(const NIdentifier& id, ExpressionList& args) : id(id), args(args) {}
    NMethodCall(const NIdentifier& id) : id(id) { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NBinaryOperator : public NExpression {
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) : op(op), lhs(lhs), rhs(rhs) { };
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NAssignment : public NExpression {
public:
    NIdentifier& id;
    NExpression& assignment;
    NAssignment(NIdentifier& id, NExpression& assignment) : id(id), assignment(assignment) { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NBlock : public NExpression {
public:
    StatementList statements;
    NBlock() { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) : expression(expression) { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NVariableDeclaration : public NStatement {
public:
    const NIdentifier& type;
    NIdentifier& id;
    NExpression* expr;
    NVariableDeclaration(
            const NIdentifier& type,
            NIdentifier& id) :
        type(type), id(id) { }
    NVariableDeclaration(
            const NIdentifier& type,
            NIdentifier& id,
            NExpression *expr) :
        type(type), id(id), expr(expr) { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};

class NFunctionDeclaration : public NStatement {
public:
    const NIdentifier& type;
    const NIdentifier& id;
    VariableList args;
    NBlock& block;
    NFunctionDeclaration(
            const NIdentifier& type,
            const NIdentifier& id,
            const VariableList& args,
            NBlock& block) :
        type(type), id(id), args(args), block(block) { }
    virtual llvm::Value* codegen(CodeGenContext& context);
};
