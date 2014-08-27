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
    struct MultToShift : public FunctionPass {
        static char ID;

        MultToShift() : FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F) 
        {
            //unsigned int i;
            std::vector <Instruction*> deleteInstructions; 
            std::vector <Instruction*> addIfStatements;

            for(Function::iterator f=F.begin(); f!=F.end(); f++)
            { 

                for(BasicBlock::iterator i=f->begin(); i!=f->end(); i++)
                {


                    if((*i).getOpcode()==Instruction::Mul )
                    {
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
                                        Value *temp = Builder.CreateShl(v1,v,"demo",false,false);
                                        v2->replaceAllUsesWith(v);
                                        (*i).replaceAllUsesWith(temp);
                                    }
                                }

                                else
                                {
                                    addIfStatements.push_back(i);
                                    


                                    //BasicBlock *ifend =f->splitBasicBlock(i,"ifend");
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
                                deleteInstructions.push_back((i)); 
                            }
                        }
                    } 
                }


            }
            for(std::vector<Instruction*>::iterator iv = addIfStatements.begin(); iv!=addIfStatements.end(); iv++)
            {
                static IRBuilder<> Builder((*iv));

                Value *v1 = (*iv)->getOperand(0);
                Value *v2 = (*iv)->getOperand(1);

                unsigned int one = 1;
                Constant *constantOne = llvm::ConstantInt::get(v1->getType(),one,"constantOne"); 
                Constant *consantZero = llvm::ConstantInt::get(v1->getType(),one-1,"constantZero");
                Value *sub_val = Builder.CreateSub(v1,constantOne,"val0MinusOne",0,0);
                
                Value *vconst = dyn_cast<Value>(consantZero); 
                Value *sub_val2 = Builder.CreateSub(v2,constantOne,"val1MinusOne",0,0);
                Value *and_val0 = Builder.CreateAnd(v1,sub_val,"isval0PowerOfTwo");
                Value *and_val1 = Builder.CreateAnd(v2,sub_val2,"isval1PowerOfTwo");
                
                //BasicBlock *bsplit2 = (*bsplit).splitBasicBlock((*iv),"elsestart");

                Value *cmp = Builder.CreateICmpEQ(and_val0,vconst);
                
                BasicBlock *bsplit = (*iv)->getParent()->splitBasicBlock((*iv),"ifstart");
//                BasicBlock *iftrue = llvm::BasicBlock::Create(llvm::getGlobalContext(),"iftrue",(*iv)->getParent()->getParent(),bsplit);
 //               BasicBlock *iffalse = llvm::BasicBlock::Create(llvm::getGlobalContext(),"ifalse",(*iv)->getParent()->getParent(),bsplit);

  //              IRBuilder<> ifBlockBuilder((iftrue)),ifFalseBlockBuilder((iffalse));
                
   //             Value *temp = Builder.CreateShl(v1,v2,"demo",false,false);
                

                //Value *temp2 = Builder.CreateMul(v1,v2,"demo",false,false);
    //            Value *t = Builder.CreateCondBr(cmp,iftrue,iffalse);

//Value *temp = Builder.CreateShl(v1,v2,(*iv)->getName(),false,false);





            }

            return false;
        }
    };
}
char MultToShift::ID = 0;

static RegisterPass<MultToShift> X("multshift" ,"Change Mul to Shl for unsigned int multiplication", false,false);

