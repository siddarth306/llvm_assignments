#include <list>
#include <vector>
#include <string>
#include <iostream>
//#include "basic_ir.h"
//#include "./basic_ir.cpp"
using namespace std;
class Instruction;
class BasicBlock
{
    unsigned int Id;
    list<Instruction*> instructions;
    int size;
    vector<BasicBlock*> successors;
    vector<BasicBlock*> predecessors;
    Instruction *terminator;
    
    public:
    
    void setTerminator(Instruction*);
    BasicBlock(unsigned int blockId);    
    void printBlock();
    list <Instruction*>::iterator bb_begin();
    list<Instruction*>::iterator bb_end();
    BasicBlock* getParent();
    void insertInstruction(Instruction *inst);
    void deleteInstruction(int i);
    Instruction* getInstruction(int i);
    unsigned int get_size();
    unsigned int getID(){return Id;}
    void printhello();
    void addSuccessor(BasicBlock* succ){successors.push_back(succ);}
    void addPredecessor(BasicBlock* pred){predecessors.push_back(pred);}
};

