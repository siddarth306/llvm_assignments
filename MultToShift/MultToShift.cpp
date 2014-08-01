#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/IR/Type.h>
using namespace llvm;

namespace {
    struct MultToShift : public BasicBlockPass {
        static char ID;
    
        MultToShift() : BasicBlockPass(ID) {}

        virtual bool runOnBasicBlock(BasicBlock &BB) 
        {
            unsigned int i;
            for(BasicBlock::iterator i=BB.begin(); i!=BB.end(); i++)
            {
                
                   
                for (User::op_iterator j = (*i).op_begin(); j!= (*i).op_end(); j++)
                 
                {
                      
              
                    if((*j)->getType()->isUnsignedIntegerType())
                    {
                        errs()<<"hello";
                    }
                } 
            }

              

             
            return false;
        }

    };
}
char MultToShift::ID = 0;

static RegisterPass<MultToShift> X("multshift" ,"Change Mul to Shl for unsigned int multiplication", false,false);

