


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
//#include "BasicBlock.h"
//#include "Function.h"
using namespace std;
class BasicBlock;
enum instruction_type { ld,st,mov,add,sub,mul,div };

enum operand_type { immediate, registr, address,labl };

class label
{
    const string &labelName;
    int index;
    public:
    label();
    void getLabelName();
    int getLabelIndex();
};
class Operands
{	
	operand_type type;
	int value;

public:
	Operands();
	Operands(operand_type op_type, int op_value);		
	Operands(operand_type op_type, const string &op_value);							
    Operands(operand_type op_type, label l1, label l2);
	operand_type get_type();
	int get_value();

	void set_type(operand_type temp);
	void set_value(int temp);
		
	void print_operand();
	void print_destination();
};

class Instruction
{
	instruction_type opcode;
	Operands destination;
	std::vector<Operands> srcs;
    BasicBlock* Parent; 
public:
    BasicBlock* getParent();	
	Instruction (instruction_type instruct_opcode,const Operands &i_dest,const vector<Operands> &i_srcs,BasicBlock* inst_parent);
	Instruction();
    
	Operands get_destination();
	vector<Operands>::iterator get_srcs_head();
	instruction_type get_opcode();

	void set_destination(Operands temp);
	void set_srcs(int size, vector<Operands>::iterator &it_begin);
	void set_opcode(instruction_type temp);

	void print_instruction();
		

};


class program
{
	list<Instruction> code;
	
public:
	list<Instruction>::iterator get_begin();
	list<Instruction>::iterator get_end();

	void add_instruction (const Instruction &new_instruction);
	int get_size();
	void delete_instruction(int i);
	Instruction get_instruction(int i);
	void print_program ();
		
};


class ssa
{
	list<Instruction>::iterator start,end; 
	map<int,int> register_table;
	program ssa_format;   
	
public:
	ssa (program &p);
	
	void convert_to_ssa ();
	void print_ssa_program ();

	
	void optimize_ssa();
	
};


