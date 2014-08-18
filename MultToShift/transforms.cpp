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
#include <llvm/IR/IRBuilder.h>
using namespace llvm;

namespace {
    struct MultToShift : public BasicBlockPass {
        static char ID;
    
        MultToShift() : BasicBlockPass(ID) {}

        virtual bool runOnBasicBlock(BasicBlock &BB) 
        {
            //unsigned int i;
             
            BasicBlock *bb = &BB; 
            for(BasicBlock::iterator i=BB.begin(); i!=BB.end(); i++)
            {
               
                    //errs()<<"hi";
                    //errs()<<(*i).getOpcode();
                    if((*i).getOpcode()==Instruction::Mul )
                        if(OverflowingBinaryOperator *op = dyn_cast<OverflowingBinaryOperator>(i))
                        {
                            
                            static IRBuilder<> Builder(i);
                            
                             Value *v1 = (*i).getOperand(0);
                   
                             Value *v2 = (*i).getOperand(1);

                            if(!op->hasNoSignedWrap() && !op->hasNoUnsignedWrap() )
                            {
                                if(ConstantInt *ci = dyn_cast<ConstantInt>(v1))
                                {
                                    if(ci->getValue().isPowerOf2())
                                    {
                                        unsigned val = ci->getValue().countTrailingZeros();
                                        APInt ap = APInt(ci->getBitWidth(), val, false);
                                        ConstantInt ci2 = ConstantInt(ci->getType(),ap);

                                        errs()<<"\n1st";

                                
                                        Value *temp = Builder.CreateShl(v2,v,"demo",false,false);
                                    }

                                }    
                                else if(ConstantInt *ci = dyn_cast<ConstantInt>(v2))
                                {
                                    if(ci->getValue().isPowerOf2())
                                    {

                                        unsigned val = ci->getValue().countTrailingZeros();
                                        APInt ap = APInt(sizeof(unsigned int), val, false);
                                        Value *v = dyn_cast<Value>(ap);

                                
                                        Value *temp = Builder.CreateShl(v1,v,"demo",false,false);


                                    errs()<<"\n2nd";
                                    }
                                }
                          
   
                            errs()<<"\nnsw:"<<op->hasNoSignedWrap();
                            errs()<<"\nnuw:"<<op->hasNoUnsignedWrap();
                        
                            }
                        } 
                                   //if (op->hasNoSignedWrap() && !op->hasNoUnsignedWrap()) 
                           //if( llvm::ConstantInt *ci =dyn_cast<llvm::ConstantInt>(v))
            }
             
            return false;
        }

    };
}
char MultToShift::ID = 0;

static RegisterPass<MultToShift> X("multshift" ,"Change Mul to Shl for unsigned int multiplication", false,false);

