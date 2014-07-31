#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Use.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include <map>
//#include <StringRef.h>
using namespace llvm;


namespace {

    struct BasicOpt : public ModulePass {
        static char ID;
        BasicOpt() : ModulePass(ID) {}
        
        virtual void getAnalysisUsage(AnalysisUsage &AU) const
        {
            AU.addRequired<LoopInfo>();
            AU.addRequired<ScalarEvolution>();
        }
        
        virtual bool runOnModule( Module &M) 
        {
            std::map <Function *,int> printf_stat;
            StringRef t;                  
            for(Module::iterator i =M.begin() ; i!=M.end(); i++)
            {
                for (Value::use_iterator x = i->use_begin(); x != i->use_end(); ++x)
                    
                    if (Instruction *Inst = dyn_cast<Instruction>(*x)) 
                    {
                        BasicBlock *b = Inst->getParent();
                        Function *f=b->getParent();
                        LoopInfo &LI = getAnalysis<LoopInfo>(*f);
                        ScalarEvolution *SE = &getAnalysis<ScalarEvolution>(*f);
                        
                        StringRef operand = Inst->getOperand(1)->getName();
                        if(LI.empty())
                        {
                            if(operand.compare("printf")==0 && Inst->getOpcode()==49)
                            {
                                Function *F = Inst->getParent()->getParent(); 
                                printf_stat[F]+=1;;
                            }  
                        }

                        else
                        {
                            if(operand.compare("printf")==0 && Inst->getOpcode()==49)
                            {
                                Function *F = Inst->getParent()->getParent(); 
                                printf_stat[F]+=0;
                                LoopInfo::iterator l = LI.begin();
                                Loop *TLL = LI.getLoopFor(Inst->getParent());
                                int outerDepth = LI.getLoopDepth(Inst->getParent());
                                int innerDepth = LI.getLoopDepth(*((*l)->block_begin()));
                                int looptrip = 1;
                                while(outerDepth >=innerDepth )
                                {
                                    looptrip*=SE->getSmallConstantTripCount(TLL,*((*l)->block_begin()));
                                    TLL= TLL->getParentLoop();
                                    innerDepth++; 
                                }
                                printf_stat[F]+=looptrip;
                            }
                        }
                    
                    }
            }
            errs()<<"\nPrintf function stats";
            for(std::map<Function *,int>::iterator i=printf_stat.begin(); i!=printf_stat.end();i++)
                errs()<<"\nFunction : "<<i->first->getName()<<"\n Number of printf's : "<<i->second<<"\n";        
            return false;
        }
    };
}
char BasicOpt::ID = 0;

static RegisterPass<BasicOpt> X("basic-opt" ," Basic Parsing of a module", false,false);

