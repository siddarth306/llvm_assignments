#include "basic_ir.h"
#include "BasicBlock.h"
int main()
{

    program p;
    Operands o1(immediate,2);
    Operands r1(registr,1);		
    Operands r2(registr,2);	
    Operands r3(registr,3);	
    Operands r4(registr,4);	
    Operands r5(registr,5);	
    Operands r6(registr,6);	
    Operands r7(registr,7);	

    std::vector<Operands> x1,x2,x3,x4,x5,x6,x7,x8,y1;
    y1.push_back(o1);
    x1.push_back(r2);
    x2.push_back(r2);
    x3.push_back(r3);
    x4.push_back(r4);
    x5.push_back(r5);
    x6.push_back(r6);
    x7.push_back(r4);
    x7.push_back(r4);
    x8.push_back(r6);
    x8.push_back(r6);

   // vector<BasicBlock> pred,succ;
   // cout<<"\nBasic bblock size:"<<p.get_size();
    
    Instruction i(ld,r1,y1);
    Instruction i1(ld,r5,y1);
    Instruction i2(mov,r2,x1);
    Instruction i3(mov,r3,x2);
    Instruction i8(mov,r3,y1);
    Instruction i4(jmp,r4,x3);
    Instruction i5(mov,r6,x5);
    Instruction i6(add,r7,x7);
    Instruction i7(add,r7,x8);
   
    p.addsrcInstruction(i);
    p.addsrcInstruction(i1);
    p.addsrcInstruction(i2);
    p.addsrcInstruction(i3);
    //p.get_begin()->addsrcInstruction(i8);
    p.addsrcInstruction(i4);
    p.addsrcInstruction(i5);
    p.addsrcInstruction(i7);
    p.addsrcInstruction(i6);	
    
   // cout<<"prog size:"<<p.getBlock(0)->get_size();
cout<<"3 address code:\n";
    p.createDFA();
    //cout<<"Number of blocks: "<<p.get_size();
    p.print_program();
    /* ssa s1(p);
    s1.convert_to_ssa();
    s1.print_ssa_program();
    s1.optimize_ssa();
    cout<<"\noptimized ";
    s1.print_ssa_program();
*/
}
