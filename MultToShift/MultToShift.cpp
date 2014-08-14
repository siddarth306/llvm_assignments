#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/IR/Type.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Operator.h>
using namespace llvm;

namespace {
    struct MultToShift : public BasicBlockPass {
        static char ID;
    
        MultToShift() : BasicBlockPass(ID) {}

        virtual bool runOnBasicBlock(BasicBlock &BB) 
        {
            //unsigned int i;
            for(BasicBlock::iterator i=BB.begin(); i!=BB.end(); i++)
            {
                for (unsigned int j=0; j<(*i).getNumOperands() ; j++)
                {
                    //errs()<<"hi";
                    Value *v = (*i).getOperand(j);
                    //errs()<<(*i).getOpcode();
                    if((*i).getOpcode()==Instruction::Mul )
                        if(OverflowingBinaryOperator *op = dyn_cast<OverflowingBinaryOperator>(i))
                        {
   
                            errs()<<"\nnsw:"<<op->hasNoSignedWrap();
                            errs()<<"\nnuw:"<<op->hasNoUnsignedWrap();
                        } 
                                   //if (op->hasNoSignedWrap() && !op->hasNoUnsignedWrap()) 
                           //if( llvm::ConstantInt *ci =dyn_cast<llvm::ConstantInt>(v))
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

