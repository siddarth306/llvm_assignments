#include <list>
#include <vector>

//#include "basic_ir.h"
//#include "./basic_ir.cpp"
using namespace std;
class Instruction;
class BasicBlock
{
    char *name;
    list<Instruction> instructions;
    int size;
    vector<BasicBlock> successors;
    vector<BasicBlock> predecessors;
    Instruction *terminator;
    public:
    void setTerminator(Instruction*);
    BasicBlock(char* name);    
    void printProgram();
    list <Instruction>::iterator bb_begin();
    list<Instruction>::iterator bb_end();
    BasicBlock* getParent();

};

