#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
    struct BasicOpt : public ModulePass {
        static char ID;    
        BasicOpt() : ModulePass(ID) {}

        virtual bool runOnModule(Module &F) {
            return false;
        }

    };
}
char BasicOpt::ID = 0;

static RegisterPass<BasicOpt> X("basic-opt" ," Basic Parsing of a module", false,false);

