#include "basic_ir.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
//#include "./BasicBlock.h"
//#include "./Function.h"
using namespace std;


string global_opcodes[] = {"ld","st","mov","add","sub","mul","div","cmp","jmp" };
//std::vector<> v;
std::vector<string> symbol_table;
int src_size[7] = {1,1,1,2,2,2,2};

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

Instruction::Instruction (instruction_type instruct_opcode, const Operands &i_dest, const vector<Operands> &i_srcs,BasicBlock* inst_parent)
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
    for (int i = 0; i < srcs.size(); ++i)
        srcs[i].print_operand();
}


list<Instruction>::iterator program::get_begin ()
{
    return code.begin();
}


list<Instruction>::iterator program::get_end ()
{
    return code.end();
}

void program::add_instruction (const Instruction &new_instruction)
{
    code.push_back(new_instruction);
}

void program::print_program ()
{
    for (list<Instruction>::iterator i = code.begin(); i != code.end(); ++i)
        i->print_instruction();

}

int program::get_size()
{
    return code.size();
}
void program::delete_instruction(int i)
{
    list<Instruction>::iterator it = code.begin();
    advance(it,i);
    code.erase(it);
}

Instruction program::get_instruction(int i)
{
    list<Instruction>::iterator it = code.begin();
    advance(it,i);
    return *it;
}
ssa::ssa (program &p)
{

    start = p.get_begin();
    end = p.get_end();

}


/*
   Algorithm for ssa

   maintain a counter
   check if destination register exists inregister table
   If it doesn't, then add the register number and assign it with counter value

   If it does then assign it with counter value
   Increment counter 
   */

/*void ssa::convert_to_ssa ()						//Updates register table 
{

    int counter=0;

    for (list <Instruction>::iterator i= start; i != end; ++i)     
    {

        Operands temp_destination = i->get_destination();

        std::vector<Operands> temp_srcs;
        for (vector<Operands>::iterator x= i->get_srcs_head(); x != i->get_srcs_head()+ src_size[i->get_opcode()]; ++x)
        {
            Operands temp_operand;
            temp_operand.set_type(x->get_type());
            if (x->get_type() == registr)											
            {


                temp_operand.set_value(register_table[x->get_value()]);
            }
            else
                temp_operand.set_value(x->get_value());
            temp_srcs.push_back(temp_operand);


        }	 

        if (temp_destination.get_type() == registr )
        {
            register_table[temp_destination.get_value()] = counter++;
            temp_destination.set_value(counter-1);
        }

        Instruction pseudo_instruction2(i->get_opcode(), temp_destination, temp_srcs);
        ssa_format.add_instruction(pseudo_instruction2);
        cout<<"\n";

    }
}*/


void ssa::print_ssa_program ()
{
    cout<<"ssa_format:\n";
    ssa_format.print_program();
}




void ssa::optimize_ssa()
{
    std::vector<reg_opt_entry> register_opt_table ;
    int counter = 0,opcode,j;
    std::vector<Operands>::iterator src_head;
    int size2 = ssa_format.get_size();
    set<int> deleted_elements;
    int de=0;
    /*for (int hello = 0; hello < size2; ++hello)
      {
      deleted_elements.push_back(false);
      }*/


    reg_opt_entry table_entry;
    for (list<Instruction>::iterator it = ssa_format.get_begin(); it != ssa_format.get_end(); ++it)
    {

        opcode = it->get_opcode();

        if(opcode == mov)
        {

            src_head = it->get_srcs_head();

            if (src_head->get_type() == registr && it->get_destination().get_type() == registr)
            {
                table_entry.src = it->get_srcs_head()->get_value();
                table_entry.dest = it->get_destination().get_value();
                table_entry.inst_no = counter;
                //table_entry.deleted = false;

                for (j = register_opt_table.size()-1; j>=0; --j)
                {
                    if(register_opt_table[j].dest == table_entry.src)
                    {
                        table_entry.value = register_opt_table[j].value;
                        break;
                    }
                }
                if(j < 0)
                    table_entry.value = table_entry.src;
                register_opt_table.push_back(table_entry);

            }

            else
            {
                Operands op_dest = it->get_destination();

                for (int l = 0 ; l <= register_opt_table.size(); ++l)
                    if (register_opt_table[l].dest == op_dest.get_value())
                        register_opt_table[l].value = register_opt_table[l].dest;
            }
        }

        else if (opcode == add || opcode == sub || opcode == mul || opcode == div)
        {

            int latest_value;

            for (int k = 0; k < 2; ++k)
            {
                Operands op = *(it->get_srcs_head() +k);

                if (op.get_type() == registr)
                {
                    for (int i = register_opt_table.size()-1; i >=0 ; --i)
                        if (register_opt_table[i].dest == op.get_value())
                        {
                            latest_value = register_opt_table[i].value;
                            break;
                        }





                    for (int l = register_opt_table.size() ; l >= 0; --l)
                    {
                        if (register_opt_table[l].dest == op.get_value() && register_opt_table[l].value == latest_value)
                        {
                            //register_opt_table[l].deleted = true;
                            //cout<<"\nDelete instruction: "<<l<<endl;
                            //ssa_format.delete_instruction(register_opt_table[l].inst_no-de);
                            //de++;
                            deleted_elements.insert(register_opt_table[l].inst_no);
                            op.set_value(register_opt_table[l].src);
                            (it->get_srcs_head()+k)->set_value(register_opt_table[l].value);

                            //deleted_elements[counter] = true;
                        }
                    }
                }
            }
        }

        else if(opcode = ld)
        {
            Operands op_dest = it->get_destination();

            for (int l = 0 ; l <= register_opt_table.size(); ++l)
            {
                if (register_opt_table[l].dest == op_dest.get_value())
                {
                    register_opt_table[l].value = register_opt_table[l].dest;
                }

            }
        }
        ++counter;
    }

    cout<<endl;
    set<int>::iterator i ;
    while (!deleted_elements.empty())
    {


        i = deleted_elements.begin();
        cout<<"\n"<<*i; 
        ssa_format.delete_instruction(*i-de);
        deleted_elements.erase(i);
        de++;

    }

    //ssa_format.delete_instruction(*(deleted_elements.end())-de);
}

BasicBlock::BasicBlock(vector<BasicBlock&> &preds, vector<BasicBlock&> &succ)
{
    predecessors= preds;
    successors = succ;
}
