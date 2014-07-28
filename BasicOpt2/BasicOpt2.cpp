#include "llvm/Pass.h"
//#include "../../include/llvm-3.4/llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/Dominators.h"

#include <vector>
using namespace llvm;

namespace {
    struct BasicOpt : public FunctionPass{
            static char ID;
            std::vector<BasicBlock *> inaccessable; 
            BasicOpt() : FunctionPass(ID) {}

            virtual void getAnalysisUsage(AnalysisUsage &AU) const {
                      AU.addRequired<DominatorTree>();
                          }
             
            virtual bool runOnFunction(Function &F) {
                  DominatorTree &DT = getAnalysis<DominatorTree>();
                  int x=0;

                  for(Function::iterator j = F.begin(); j != F.end(); j++)
                  {
                      x++;
                      BasicBlock *block = j;
                      if(j != F.begin() && j!=F.end()&& !DT.isReachableFromEntry( block) )
                      {
                          errs()<<"\n Block :"<<x<<" is unreachable";
                          inaccessable.push_back(block); 
                      }
                    
                  }
                  errs()<<"\nNumber of inaccessable blocks:"<<inaccessable.size();
                  for(int i = inaccessable.size()-1; i>=0; i--)
                  {
                      inaccessable[i]->eraseFromParent();
                  }
                  errs()<<"\nAll unreachable blocks removed\n";
                  return false;
            }
    };
}
char BasicOpt::ID = 0;

static RegisterPass<BasicOpt> X("basic-opt" ," Basic Parsing of a module", false,false);

