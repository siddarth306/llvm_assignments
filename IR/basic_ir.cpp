#include "basic_ir.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include "./BasicBlock.h"
#include <cstring>
#include <algorithm>
//#include "./Function.h"
using namespace std;
BasicBlock demio(1);

string global_opcodes[] = {"ld","st","mov","add","sub","mul","dv","jmp","cmp" };
//std::vector<> v;
std::vector<string> symbol_table;
int src_size[8] = {1,1,1,2,2,2,1,1};

struct forwardEdge
    {
        BasicBlock* src;
        string label;
    };


struct reg_opt_entry
{
    int dest;
    int src;
    int inst_no;
    int value;

};

label::label(string labelname)
{
    labelName = labelname;
}

operand_type Operands::get_type()
{
    return type;
}

void Operands::set_type(operand_type temp)
{
    type = temp;
}

void Operands::set_value(int temp)
{
    value = temp;
}
int Operands::get_value()
{
    return value;
}

Operands::Operands ()	{}		

Operands::Operands (operand_type op_type, int op_value)			
{
    type = op_type;
    value = op_value;
}
Operands::Operands (operand_type op_type, const string &op_value)
{

    if(op_type == labl)
    {
        str = op_value;
    }
    type =address;
    value = symbol_table.size();
    symbol_table.push_back(op_value);
    /*bool repeat = false;

      for (int i = 0; i <symbol_table.size() ; ++i)
      {
      if(op_value.compare(symbol_table[i]) == 0)
      {
      repeat = true;
      value = i;
      }
      }
      if (!repeat)
      {
      value = symbol_table.size();
      symbol_table.push_back(op_value);
      }*/

}	

void Operands::print_operand ()
{

    if (type == immediate)
    {
        cout<<" "<<value;
    }
    else if (type == registr)
    {
        cout<<" r"<<value;
    }
    else if (type == address)
    {
        cout<<" "<<symbol_table[value]; 
    }
    /*switch(type)
      {
      case immediate :														// Immediate operand

      break;
      case 2 :														// registr operand

      break;
      case 3 :
    // Memory Location operand
    }*/
}

void Operands::print_destination ()
{
    if (type == registr)						
        cout<<" r"<<value;

    if (type == address)
        cout<<" "<<symbol_table[value];
}
Instruction::Instruction (instruction_type instruct_opcode,const Operands &i_dest,const vector<Operands> &i_srcs,BasicBlock *inst_parent)
{
    opcode = instruct_opcode;
    destination = i_dest;
    srcs = i_srcs;
    Parent = inst_parent;
    labelPresent =false;

}

Instruction::Instruction (instruction_type instruct_opcode,const Operands &i_dest,const vector<Operands> &i_srcs)
{
    cout<<"\nhi!!!!";
    opcode = instruct_opcode;
    destination = i_dest;
    srcs = i_srcs;
    //    Parent = inst_parent;
    labelPresent = false;

}

Instruction::Instruction (instruction_type instruct_opcode,const Operands &i_dest,const vector<Operands> &i_srcs,string labelname)
{
    opcode = instruct_opcode;
    destination = i_dest;
    srcs = i_srcs;
    //    Parent = inst_parent;
    labelPresent = true;
    // this->labelName.copy(labelName,labelName.size(),0);
    this->labelName = labelname;
    cout<<"\nLabel present";
}



Instruction::Instruction(){}

Operands Instruction::get_destination()
{
    return destination;
}

vector<Operands>& Instruction::getsrc()
{
    return this->srcs;
}

void Instruction:: set_destination(Operands temp)
{
    destination.set_type(temp.get_type());
    destination.set_value(temp.get_value());
}

void Instruction::set_srcs(int size, vector<Operands>::iterator &it_begin)
{
    for (std::vector<Operands>::iterator i = it_begin ; i != it_begin + size; ++i)
    {
        Operands temp_op;
        temp_op.set_type(i->get_type());
        temp_op.set_value(i->get_value());
    }
}
vector<Operands>::iterator Instruction::get_srcs_head()
{
    return srcs.begin();
}

instruction_type Instruction::get_opcode()
{
    return opcode;
}

void Instruction::set_opcode(instruction_type temp)
{
    opcode = temp;
}

void Instruction::print_instruction ()
{
    string name= global_opcodes[opcode];
    cout<<"\n"<<name;

    destination.print_destination();
    for (unsigned int i = 0; i < srcs.size(); ++i)
        srcs[i].print_operand();
}

void Instruction::changeParent(BasicBlock *newParent)
{
    Parent = newParent;
}

BasicBlock::BasicBlock(unsigned int Id)
{
    this->Id = Id; 
    
}
void BasicBlock::setTerminator(Instruction *terminate)
{
    terminator = terminate;
}


list<Instruction*>::iterator BasicBlock::bb_end ()
{
    return instructions.end();
}


list<Instruction*>::iterator BasicBlock::bb_begin ()
{
    return instructions.begin();
}

void BasicBlock::insertInstruction(Instruction *new_instruction)
{
    instructions.push_back(new_instruction);
}

void BasicBlock::printBlock ()
{
    cout<<"\nBlock number:"<<Id;
    cout<<"\npredecessor size:"<<this->predecessors.size();
    cout<<"\nsuccessor size:"<<this->successors.size();
    for (list<Instruction*>::iterator i = instructions.begin(); i != instructions.end(); ++i)
    {
        (*i)->print_instruction();
    }
}

unsigned int BasicBlock::get_size()
{
    return instructions.size();
}
void BasicBlock::deleteInstruction(int i)
{
    list<Instruction*>::iterator it = instructions.begin();
    advance(it,i);
    instructions.erase(it);
}

Instruction* BasicBlock::getInstruction(int i)
{
    list<Instruction*>::iterator it = instructions.begin();
    advance(it,i);
    return *it;
}


list<BasicBlock*>::iterator program::get_begin ()
{
    return codeBlocks.begin();
}


list<BasicBlock*>::iterator program::get_end ()
{
    return codeBlocks.end();
}

void BasicBlock::printhello()
{
    cout<<"hi";
}
void program::addBlock (BasicBlock *newBlock)

{
    codeBlocks.push_back(newBlock);
}

void program::print_program ()
{
    for (list<BasicBlock*>::iterator i = codeBlocks.begin(); i != codeBlocks.end(); ++i)
    {
        (*i)->printBlock();

    }
}

int program::get_size()
{
    return codeBlocks.size();
}
void program::deleteBlock(int i)
{
    list<BasicBlock*>::iterator it = codeBlocks.begin();
    advance(it,i);
    codeBlocks.erase(it);
}
void program::addsrcInstruction(const Instruction &inst)
{
    this->src_program.push_back(inst);
}
BasicBlock* program::getBlock(int i)
{
    list<BasicBlock*>::iterator it = codeBlocks.begin();
    advance(it,i);
    return *it;
}

void program::createDFA()
{
    vector<forwardEdge> forwardEdgeTable;
    // list<BasicBlock*>::iterator first_block = codeBlocks.begin();
    //cout<<"\n\n Basic block size:"<<codeBlocks.size();
    //cout<<"\n\n\nSize:"<<(*first_block)->get_size();
    BasicBlock *binit = new BasicBlock(codeBlocks.size());
    codeBlocks.push_back(binit);
    vector<string> blocksToBeCreated;    
    bool prevjmp =false; 
    for(list<Instruction>::iterator i= src_program.begin(); i!= src_program.end();i++)
    {
        cout<<"\nOpcode:"<<(*i).get_opcode();        
        cout<<(*i).islabelPresent();
        if(prevjmp )
        {
            //cout<<"i\nNew block created..";
            prevjmp=false;
            BasicBlock *bnew = new BasicBlock(codeBlocks.size());
            codeBlocks.push_back(bnew); 
            
            if( (*i).islabelPresent() )
            {
                blocksToBeCreated.push_back((*i).getLabel());
                
             list<BasicBlock*>::iterator bbIterate = codeBlocks.begin(); 
             advance(bbIterate,codeBlocks.size()-1);  
             labelTable[ (*i).getLabel() ]  = *(bbIterate); 
             cout<<"\nLabel:             "<<(*i).getLabel();   
             //labelTable[ (*i).getLabel() ] = *( --codeBlocks.end() );
            }
        }
        else if((*i).islabelPresent() && std::find(blocksToBeCreated.begin(),blocksToBeCreated.end(), (*i).getLabel())!= blocksToBeCreated.end())
        {
             BasicBlock *bnew = new BasicBlock(codeBlocks.size());
             codeBlocks.push_back(bnew);

             list<BasicBlock*>::iterator bbIterate = codeBlocks.begin(); 
             advance(bbIterate,codeBlocks.size()-1);  
             labelTable[ (*i).getLabel() ]  = *(bbIterate);        
             cout<<"\n\nLabel:      "<<(*i).getLabel(); 

        }
                                                                                                                                      
        i->changeParent(*(--codeBlocks.end()));

        if((*i).get_opcode()==jmp)
        {
            //cout<<"\nEntered jump";
            prevjmp =true;
            
            string label = (*(*i).get_srcs_head()).getLabel();
           // cout<<"\nFound label";
            //cout<<"\nLabelTable size:"<<labelTable.size();
            if(labelTable.find(label) !=labelTable.end())
            {
              //  cout<<"\nUpdating label Table";
                cout<<(labelTable.find(label))->second->getID();
                BasicBlock* pred = (labelTable.find(label))->second; 
                pred->addPredecessor((*i).getParent());
                (*i).getParent()->addSuccessor((labelTable[label]));
            }
            else
            {
            cout<<"\nFuture Block created"; 
            blocksToBeCreated.push_back((*i).getLabel());
            //cout<<"\nCreating Edge";  
            forwardEdge edge;
            edge.label = label;
            edge.src = (*i).getParent();
            forwardEdgeTable.push_back(edge);
            }
            
        }
        Instruction *inew = new Instruction((*i).get_opcode(),(*i).get_destination(),(*i).getsrc(),*(--codeBlocks.end()));

        list<BasicBlock*>::iterator lastBlock = codeBlocks.end();
        lastBlock--; 
        (*lastBlock)->insertInstruction(inew);
        //(*codeBlocks.end())->printhello();
        //(*codeBlocks.end())

    }
 
    for(vector<forwardEdge>::iterator iter=forwardEdgeTable.begin();iter!=forwardEdgeTable.end();iter++)
    {
        cout<<"\nLabel"<<iter->label;
         (labelTable[iter->label])->addPredecessor(iter->src);
        (iter->src)->addSuccessor(labelTable[iter->label]); 
       
    }
}

