#include "basic_ir.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include "./BasicBlock.h"
//#include "./Function.h"
using namespace std;
BasicBlock demio(1);

string global_opcodes[] = {"ld","st","mov","add","sub","mul","div","cmp","jmp" };
//std::vector<> v;
std::vector<string> symbol_table;
int src_size[8] = {1,1,1,2,2,2,2,2};

struct reg_opt_entry
{
    int dest;
    int src;
    int inst_no;
    int value;

};

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
Instruction::Instruction (instruction_type instruct_opcode,const Operands &i_dest,const vector<Operands> &i_srcs,list<BasicBlock>::iterator inst_parent)
{
    opcode = instruct_opcode;
    destination = i_dest;
    srcs = i_srcs;
    Parent = inst_parent;

    
}

Instruction::Instruction(){}

Operands Instruction::get_destination()
{
    return destination;
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

void Instruction::changeParent(list<BasicBlock>::iterator newParent)
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


list<Instruction>::iterator BasicBlock::bb_end ()
{
    return instructions.begin();
}


list<Instruction>::iterator BasicBlock::bb_begin ()
{
    return instructions.end();
}

void BasicBlock::insertInstruction(const Instruction &new_instruction)
{
    cout<<"Size:"<<instructions.size();
    instructions.push_back(new_instruction);
}

void BasicBlock::printBlock ()
{
    cout<<"block size:"<<instructions.size();
    for (list<Instruction>::iterator i = instructions.begin(); i != instructions.end(); ++i)
    {
        cout<<"\nhy";
        i->print_instruction();
    }
}

unsigned int BasicBlock::get_size()
{
    return instructions.size();
}
void BasicBlock::deleteInstruction(int i)
{
    list<Instruction>::iterator it = instructions.begin();
    advance(it,i);
    instructions.erase(it);
}

Instruction BasicBlock::getInstruction(int i)
{
    list<Instruction>::iterator it = instructions.begin();
    advance(it,i);
    return *it;
}


list<BasicBlock>::iterator program::get_begin ()
{
    return codeBlocks.begin();
}


list<BasicBlock>::iterator program::get_end ()
{
    return codeBlocks.end();
}

void program::addBlock (const BasicBlock &newBlock)
    
{
    codeBlocks.push_back(newBlock);
}

void program::print_program ()
{
    cout<<"size:"<<codeBlocks.size();
    for (list<BasicBlock>::iterator i = codeBlocks.begin(); i != codeBlocks.end(); ++i)
    {
       cout<<"\nprinting block:"; 
        i->printBlock();
        
    }
}

int program::get_size()
{
    return codeBlocks.size();
}
void program::deleteBlock(int i)
{
    list<BasicBlock>::iterator it = codeBlocks.begin();
    advance(it,i);
    codeBlocks.erase(it);
}

BasicBlock program::getBlock(int i)
{
    list<BasicBlock>::iterator it = codeBlocks.begin();
    advance(it,i);
    return *it;
}

void program::createDFA()
{
    list<BasicBlock>::iterator first_block = codeBlocks.begin();
    for(list<Instruction>::iterator i= first_block->bb_begin(); i!= first_block->bb_end();i++)
    {

        
        if((*i).get_opcode()== jmp)
        {
            BasicBlock bnew(codeBlocks.size());
            codeBlocks.push_back(bnew); 
        }
        
              
        i->changeParent((codeBlocks.end()));

    }
}
