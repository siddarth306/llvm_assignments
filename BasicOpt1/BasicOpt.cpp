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
                  int no_of_functions=0;
                  errs()<<F.size();                  
                  float  no_of_basic_blocks=0.0,no_of_instructions=0.0;
                    for(Module::iterator i = F.begin() ; i!=F.end(); i++)
                    {
                        
                        no_of_functions++; 
                        Function *j =i;
                        Function::iterator k;
                        for( k = j->begin(); k != j->end(); k++)
                        {
                            no_of_basic_blocks+=1;
                                                       
                            BasicBlock *b = k;

                            no_of_instructions+= b->size();; 
                        }
                 }
                 errs()<<"\nTotal number of functions: "<<no_of_functions;
                 errs()<<"\nAvg Basic Blocks per function: "<<(no_of_basic_blocks / no_of_functions);
                 errs()<<"\nAvg number of instructions per block in a function: "<<(no_of_instructions / no_of_basic_blocks / no_of_functions);
                    return false;
            }
    };
}
char BasicOpt::ID = 0;

static RegisterPass<BasicOpt> X("basic-opt" ," Basic Parsing of a module", false,false);

