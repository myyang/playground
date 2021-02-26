#include "node.h"
#include "codegen.h"
#include "parser.hpp"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm//IR/IRPrintingPasses.h"
#include "llvm//IR/Instruction.h"
#include "llvm//IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

void CodeGenContext::generateCode(NBlock& root)
{
    std::cout << "Generating code ..." << std::endl;

    std::vector<llvm::Type*> argTypes;
    llvm::FunctionType *ftype = llvm::FunctionType::get(
            llvm::Type::getVoidTy(TheContext), argTypes, false);
    mainFunction = llvm::Function::Create(
            ftype, llvm::GlobalValue::InternalLinkage, "main", module.get());
    llvm::BasicBlock *bblock = llvm::BasicBlock::Create(
            TheContext, "entry", mainFunction, 0);

    /* Push a new variable/block context */
    pushBlock(bblock);
    root.codegen(*this);
    llvm::ReturnInst::Create(TheContext, bblock);
    popBlock();

    /* Print the bytecode in a human-readable format
       to see if our program compiled properly
     */
    std::cout << "Code is generated." << std::endl;
    llvm::legacy::PassManager pm;
    pm.add(llvm::createPrintModulePass(llvm::outs()));
    pm.run(*module.get());
}

llvm::GenericValue CodeGenContext::runCode()
{
    std::cout << "Running code ... " << std::endl;

    llvm::EngineBuilder *eb = new llvm::EngineBuilder(std::move(module));
    llvm::ExecutionEngine *ee = eb->create();

    std::vector<llvm::GenericValue> noargs;
    llvm::GenericValue v = ee->runFunction(mainFunction, noargs);

    std::cout << "Code was run." << std::endl;
    return v;
}

static const llvm::Type *typeOf(const NIdentifier& type)
{
    if (type.name.compare("int") == 0)
    {
        return llvm::Type::getInt64Ty(TheContext);
    }
    else if (type.name.compare("double") == 0)
    {
        return llvm::Type::getDoubleTy(TheContext);
    }
    return llvm::Type::getVoidTy(TheContext);
}

/* component codegen */
llvm::Value *NInteger::codegen(CodeGenContext& context)
{
    std::cout << "codegen: createing integer: " << value << std::endl;
    return llvm::ConstantInt::get(llvm::Type::getInt64Ty(TheContext), value, true);
}

llvm::Value *NDouble::codegen(CodeGenContext& context)
{
    std::cout << "codegen: createing double: " << value << std::endl;
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(TheContext), value);
}

llvm::Value *NIdentifier::codegen(CodeGenContext& context)
{
    std::cout << "Creating identifier reference: " << name << std::endl;
    if (context.locals().find(name) == context.locals().end())
    {
        std::cerr << "undeclared variable: " << name << std::endl;
        return NULL;
    }
    return new llvm::LoadInst(context.locals()[name], "", false, context.currentBlock());
}

llvm::Value *NMethodCall::codegen(CodeGenContext& context)
{
    llvm::Function *fn = context.module->getFunction(id.name.c_str());
    if (fn == NULL)
    {
        std::cout << "no such function: " << id.name << std::endl;
    }

    std::vector<llvm::Value*> args;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        //args.push_back((**it).codegen(context));
    }
    llvm::CallInst *call = llvm::CallInst::Create(fn, args, "", context.currentBlock());
    std::cout << "Creating method call: " << id.name << std::endl;
    return call;
}

llvm::Value *NBinaryOperator::codegen(CodeGenContext& context)
{
    std::cout << "Creating binary operation: " << op << std::endl;
    llvm::Instruction::BinaryOps instr;
    switch (op)
    {
        case TPLUS:     instr = llvm::Instruction::Add; break;
        case TMINUS:    instr = llvm::Instruction::Sub; break;
        case TMUL:      instr = llvm::Instruction::Mul; break;
        case TDIV:      instr = llvm::Instruction::SDiv; break;
        // TODO: logical
        default:
            return NULL;
    }

    return llvm::BinaryOperator::Create(
            instr, lhs.codegen(context), rhs.codegen(context),
            "", context.currentBlock());
}

llvm::Value *NAssignment::codegen(CodeGenContext& context)
{
    std::cout << "Creating assignment: " << id.name << std::endl;
    if (context.locals().find(id.name) == context.locals().end())
    {
        std::cerr << "undeclared variable: " << id.name << std::endl;
        return NULL;
    }
    return new llvm::StoreInst(
            assignment.codegen(context),
            context.locals()[id.name],
            false,
            context.currentBlock());
}

llvm::Value *NBlock::codegen(CodeGenContext& context)
{
    llvm::Value *last = NULL;
    for (auto it = statements.begin(); it != statements.end(); ++it) {
        std::cout << "Generating code for " << typeid(**it).name() << std::endl;
        last = (**it).codegen(context);
    }
    std::cout << "Creating block" << std::endl;
    return last;
}

llvm::Value *NExpressionStatement::codegen(CodeGenContext& context)
{
    std::cout << "Generating code for " << typeid(expression).name() << std::endl;
    return expression.codegen(context);
}

static llvm::AllocaInst* CreateEntryBlockAlloca(
        llvm::BasicBlock *block, const std::string &VarName) {
    llvm::IRBuilder<> TmpB(block, block->begin());
    return TmpB.CreateAlloca(llvm::Type::getDoubleTy(TheContext), 0, VarName.c_str());
}

llvm::Value *NVariableDeclaration::codegen(CodeGenContext& context)
{
    std::cout << "Variable Declaration for " << type.name << " " << id.name << std::endl;
    llvm::AllocaInst *alloc = CreateEntryBlockAlloca(context.currentBlock(), id.name);
    context.locals()[id.name] = alloc;
    if (expr != NULL) {
        NAssignment assn(id, *expr);
        assn.codegen(context);
    }
    return alloc;
}

llvm::Value *NFunctionDeclaration::codegen(CodeGenContext& context)
{
    std::vector<llvm::Type *> argTypes;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        llvm::Type * tmp = const_cast<llvm::Type *>(typeOf((**it).type));
        argTypes.push_back(tmp);
    }

    llvm::FunctionType *fnType = llvm::FunctionType::get(
            llvm::Type::getDoubleTy(TheContext), argTypes, false);
    llvm::Function *fn = llvm::Function::Create(
            fnType, llvm::Function::ExternalLinkage, id.name, context.module.get());
    llvm::BasicBlock *bblock = llvm::BasicBlock::Create(TheContext, "entry", fn, 0);

    context.pushBlock(bblock);

    for (auto it = args.begin(); it != args.end(); ++it)
    {
        (**it).codegen(context);
    }

    block.codegen(context);
    llvm::ReturnInst::Create(TheContext, bblock);

    context.popBlock();

    std::cout << "Creating function: " << id.name << std::endl;
    return fn;
}
