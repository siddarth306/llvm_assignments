#include "../../include/llvm-3.4/llvm/Pass.h"
#include "../../include/llvm-3.4/llvm/IR/Module.h"
#include "../../include/llvm-3.4/llvm/IR/Function.h"
#include "../../include/llvm-3.4/llvm/IR/BasicBlock.h"
#include "../../include/llvm-3.4/llvm/IR/Instruction.h"
#include "../../include/llvm-3.4/llvm/Support/raw_ostream.h"
#include "../../include/llvm-3.4/llvm/IR/Use.h"
//#include <StringRef.h>
using namespace llvm;

namespace {
    struct BasicOpt : public ModulePass {
            static char ID;
            BasicOpt() : ModulePass(ID) {}

            virtual bool runOnModule(Module &F) {
                  int no_of_functions=0;
                  errs()<<F.size();
                  StringRef t;                  
                  float  no_of_basic_blocks=0.0,no_of_instructions=0.0;
                  for(Module::iterator i = F.begin() ; i!=F.end(); i++)
                  {
                      
                        int no_of_printf=0;
                        for (Value::use_iterator x = i->use_begin(); x != i->use_end(); ++x)
                        if (Instruction *Inst = dyn_cast<Instruction>(*x)) {
                                StringRef operand = Inst->getOperand(1)->getName();

                                if(operand.compare("printf")==0/* && Inst->getOpcode()==49*/)
                                { 
                                     no_of_printf++; 
                                }

                        }
                        errs()<<"\nFunction name: "<<i->getName();
                        errs()<<"\nNumber of printfs: "<<no_of_printf;



                 }
                    return false;
            }
    };
}
char BasicOpt::ID = 0;

static RegisterPass<BasicOpt> X("basic-opt" ," Basic Parsing of a module", false,false);

