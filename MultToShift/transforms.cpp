#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/IR/Type.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
//#include <llvm/IR/Constant.h>
#include <llvm/IR/Operator.h>
#include <llvm/IR/IRBuilder.h>
#include <vector>
using namespace llvm;

namespace {
    struct MultToShift : public BasicBlockPass {
        static char ID;
    
        MultToShift() : BasicBlockPass(ID) {}

        virtual bool runOnBasicBlock(BasicBlock &BB) 
        {
            //unsigned int i;
            vector <Instruction> delete_instructions; 
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
                                    IntegerType *it = ci->getType();
                                    if(ci->getValue().isPowerOf2())
                                    {
                                        unsigned val = ci->getValue().countTrailingZeros();
                                        APInt ap = APInt(ci->getBitWidth(), val, 0);
                                        ConstantInt *c= llvm::ConstantInt::get(ci->getType(),val,0);
                                        //ConstantInt *c = new ConstantInt(it,ap);
                                        Value *v = dyn_cast<Value>(c); 
                                        //ConstantInt ci2 =   ConstantInt(it, ap);

                                        errs()<<"\n1st";
                                        v1->replaceAllUsesWith(v);
                                
                                    Value *temp = Builder.CreateShl(v2,v,"demo",false,false);
                                    }

                                }    
                                else if(ConstantInt *ci = dyn_cast<ConstantInt>(v2))
                                {
                                    if(ci->getValue().isPowerOf2())
                                    {


                                        unsigned val = ci->getValue().countTrailingZeros();
                                        APInt ap = APInt(ci->getBitWidth(), val);
                                        ConstantInt *c= llvm::ConstantInt::get(ci->getType(),val,0);
                                        //ConstantInt *c = new ConstantInt(it,ap);
                                        Value *v = dyn_cast<Value>(c); 
                                        //ConstantInt ci2 =   ConstantInt(it, ap);

                                        errs()<<"\n2st";

                                
                                    //Value *temp = Builder.CreateShl(v2,v,"demo",false,false);

                                        //unsigned val = ci->getValue().countTrailingZeros();
                                       // APInt ap = APInt(sizeof(unsigned int), val, false);
                                        //Value *v = dyn_cast<Value>(ap);

                                        
                                          
                                        Value *temp = Builder.CreateShl(v1,v,"demo",false,false);
                                        
                                        v2->replaceAllUsesWith(v);
                                                    
                                        (*i).replaceAllUsesWith(temp);
                                        
                                        errs()<<"\nUses:   ";
                                       // errs().write_escaped((*(*i).use_begin())->getName());
                                    errs()<<"\n2nd";
                                    }
                                }
                          
   
                            errs()<<"\nnsw:"<<op->hasNoSignedWrap();
                            errs()<<"\nnuw:"<<op->hasNoUnsignedWrap();
                            delete_instructions.push_back((*i)); 
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

