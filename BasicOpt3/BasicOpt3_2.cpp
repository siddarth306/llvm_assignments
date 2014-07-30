#include "../../include/llvm-3.4/llvm/Pass.h"
#include "../../include/llvm-3.4/llvm/IR/Module.h"
#include "../../include/llvm-3.4/llvm/IR/Function.h"
#include "../../include/llvm-3.4/llvm/IR/BasicBlock.h"
#include "../../include/llvm-3.4/llvm/IR/Instruction.h"
#include "../../include/llvm-3.4/llvm/Support/raw_ostream.h"
#include "../../include/llvm-3.4/llvm/IR/Use.h"
#include "../../include/llvm-3.4/llvm/Analysis/LoopInfo.h"
#include "../../include/llvm-3.4/llvm/Analysis/ScalarEvolution.h"
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
             
            
                errs()<<"\n****Function : "<<i->getName()<<" ******"; 


                for (Value::use_iterator x = i->use_begin(); x != i->use_end(); ++x)
                    
 
                    if (Instruction *Inst = dyn_cast<Instruction>(*x)) 
                    {
 
                        BasicBlock *b = Inst->getParent();
 
                        Function *f=b->getParent();

                        LoopInfo &LI = getAnalysis<LoopInfo>(*f);
                        ScalarEvolution *SE = &getAnalysis<ScalarEvolution>(*f);
                        if(LI.empty())
                        {
                            errs()<<"No loops";
 
                        }
                        else
                        {
 
                          
                            int cnt=0;
                          
                            errs()<<"\nLoop depth: "<<LI.getLoopDepth(Inst->getParent());
                            LoopInfo::iterator l = LI.begin();
                            
                            errs()<<"\nLoop2 depth2: "<<LI.getLoopDepth(*((*l)->block_begin()));
                                Loop *TLL = *l;

                                if(LI.getLoopFor(Inst->getParent())== TLL )
                                {
                                    errs()<<"\nCount : "<<cnt++;
                                   errs()<<"\n loop trip value: "<<SE->getSmallConstantTripCount(TLL,Inst->getParent());
                                  errs()<<"\n loop trip value 2 : "<<SE->getSmallConstantTripCount(TLL,*((*l)->block_begin()));
  
                                   /* Value *v = TLL->getSmallestConstantTripCount();
                                       if(v != 0)
                                       {
                                       errs()<<"\nvalue= "<<*v;
                                       }
                                       else
                                       {
                                       errs()<<"\nunkown loops";
                                       }*/
                               
                               }
                                                          

                        
                            
                        }
                       

                               
                        StringRef operand = Inst->getOperand(1)->getName();
                        if(operand.compare("printf")==0 && Inst->getOpcode()==49)
                        {
                           Function *F = Inst->getParent()->getParent(); 
                           printf_stat[F]+=1;;
                           errs()<<"\nSize: "<<printf_stat[F]<<" Increment\n";
                           
                        }
                    
                    }
                errs()<<"\nFunction: "<<i->getName()<<" : "<<printf_stat[i];
            }
            for(std::map<Function *,int>::iterator i=printf_stat.begin(); i!=printf_stat.end();i++)
            {

                errs()<<"\n"<<i->first->getName()<<"\n Number of printf's : "<<i->second<<"\n";        
            }
                
            return false;
        }
    };
}
char BasicOpt::ID = 0;

static RegisterPass<BasicOpt> X("basic-opt" ," Basic Parsing of a module", false,false);

