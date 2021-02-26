#include <map>
#include <string>
#include <stack>
#include <memory>

#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Type.h"
#include "llvm/ExecutionEngine/GenericValue.h"

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);

class NBlock;

class CodeGenBlock {
public:
    llvm::BasicBlock *block;
    std::map<std::string, llvm::Value*> locals;
};

class CodeGenContext {
    std::stack<CodeGenBlock*> blocks;
    llvm::Function *mainFunction;

public:
    std::unique_ptr<llvm::Module> module;
    CodeGenContext()
    {
        module = std::make_unique<llvm::Module>("main", TheContext);
    }

    void generateCode(NBlock& root);
    llvm::GenericValue runCode();
    std::map<std::string, llvm::Value*> locals() { return blocks.top()->locals; }
    llvm::BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(llvm::BasicBlock *block)
    {
        blocks.push(new CodeGenBlock());
        blocks.top()->block = block;
    }
    void popBlock()
    {
        CodeGenBlock *top = blocks.top();
        blocks.pop();
        delete top;
    }
};
