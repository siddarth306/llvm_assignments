#include"./BasicBlock.h"
#include <list>
class Function
{
    list<BasicBlock> basicBlocks;
    int size;

    public:

    list<BasicBlock>::iterator begin();
    list<BasicBlock>::iterator end();
};








