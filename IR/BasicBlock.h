#include <list>
#include <vector>
#include "basic_ir.h"
//#include "./basic_ir.cpp"
using namespace std;
class Instruction;
class BasicBlock
{
    list<Instruction> instructions;
    int size;
    vector<BasicBlock> successors;
    vector<BasicBlock> predecessors;
    public:
    BasicBlock(vector<BasicBlock> &preds, vector<BasicBlock> &succ);    
    
    list <Instruction>::iterator bb_begin();
    list<Instruction>::iterator bb_end();
    BasicBlock* getParent();

};

