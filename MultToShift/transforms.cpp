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
            std::vector <Instruction*> delete_instructions; 
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
                                        APInt ap = APInt(ci->getBitWidth(), val, 0);
                                        ConstantInt *c= llvm::ConstantInt::get(ci->getType(),val,0);
                                        //ConstantInt *c = new ConstantInt(it,ap);
                                        Value *v = dyn_cast<Value>(c); 
                                        //ConstantInt ci2 =   ConstantInt(it, ap);

                                        errs()<<"\n1st";
                                        v1->replaceAllUsesWith(v);
                                        Value *temp = Builder.CreateShl(v2,v,"demo",false,false);

                                        (*i).replaceAllUsesWith(temp);
 
                                                                        }

                                }    
                                else if(ConstantInt *ci = dyn_cast<ConstantInt>(v2))
                                {
                                    if(ci->getValue().isPowerOf2())
                                    {
                                        unsigned val = ci->getValue().countTrailingZeros();
                                        APInt ap = APInt(ci->getBitWidth(), val);
                                        ConstantInt *c= llvm::ConstantInt::get(ci->getType(),val,0);
                                        Value *v = dyn_cast<Value>(c); 

                                        errs()<<"\n2st";
                                        Value *temp = Builder.CreateShl(v1,v,"demo",false,false);
                                        v2->replaceAllUsesWith(v);
                                        (*i).replaceAllUsesWith(temp);
                                        errs()<<"\nUses:   ";
                                        errs()<<"\n2nd";
                                    }
                                }

                                else
                                {
                                    //errs().write_escaped((*i).getName()
                                    //llvm::TerminatorInst *term = BB.getTerminator();
                                    
                                    Value *temp = Builder.CreateShl(v1,v2,(*i).getName(),false,false);
                                    
                                    //BasicBlock *ifend =BB.splitBasicBlock(i,"ifend");
                                    //llvm::TerminatorInst(term->getType(),term->TermOpsEnd,
                                    //BasicBlock* entry = BasicBlock::;

                                    //BasicBlock* entry = BasicBlock::Create(getGlobalContext(), ("entry", gcd);
                                          //BasicBlock* ret = BasicBlock::Create(getGlobalContext(), ("return", gcd);
                                                //BasicBlock* cond_false = BasicBlock::Create(getGlobalContext(), ("cond_false", gcd);
                                                      //BasicBlock* cond_true = BasicBlock::Create(getGlobalContext(), ("cond_true", gcd);
                                                            //BasicBlock* cond_false_2 = BasicBlock::Create(getGlobalContext(), ("cond_false", gcd);


                                }
                          
                            errs()<<"\nnsw:"<<op->hasNoSignedWrap();
                            errs()<<"\nnuw:"<<op->hasNoUnsignedWrap();
                            delete_instructions.push_back((i)); 
                            }
                        } 
            }
             
            return false;
        }

    };
}
char MultToShift::ID = 0;

static RegisterPass<MultToShift> X("multshift" ,"Change Mul to Shl for unsigned int multiplication", false,false);

