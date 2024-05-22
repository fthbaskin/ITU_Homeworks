/**
    Fatih Baskýn, 150210710
    NOT gate
    @input a
    @output b
    NOTs a and gives b
*/
module not_gate(a, b);
    //Inputs
    input wire a;    
    //Outputs
    output wire b;    
    //Operations
    assign b = !a;
endmodule

/**  
    Fatih Baskýn, 150210710
    two input AND gate
    @input a
    @input b
    @output c
    ANDS a and b and gives c
*/
module and_gate(a, b, c);
    //Inputs
    input wire a;
    input wire b;    
    //Outputs
    output wire c;
    //Operations
    assign c = a & b;     
endmodule

/**
    Fatih Baskýn, 150210710
    three input AND gate
    @input a
    @input b
    @input c
    @output d
    by using and_gate module defined earlier,
    ANDs a, b, c gives d
*/
module and_gate_3input(a, b, c, d);
    //Inputs
    input wire a;
    input wire b;
    input wire c;    
    //Outputs
    output wire d;    
    //Intermediate wires
    wire int;
    //Operations
    and_gate a_b(.a(a), .b(b), .c(int)); //AND a, b give int
    and_gate a_b_c(.a(c), .b(int), .c(d)); //AND int and c give d
endmodule

/**
    Fatih Baskýn, 150210710
    two input OR gate
    @input a
    @input b
    @output c
    ORs a, b and gives c
*/
module or_gate(a, b, c);
    //inputs
    input wire a;
    input wire b;    
    //outputs
    output wire c;    
    //operations
    assign c = a | b;     
endmodule

/**
    Fatih Baskýn, 150210710
    three input OR gate
    @input a
    @input b
    @input c
    @output d
    by using or_gate module defined earlier,
    ORs a, b, c gives d    
*/
module or_gate_3input(a, b, c, d);
    //Inputs
    input wire a;
    input wire b;
    input wire c;    
    //Outputs
    output wire d;    
    //Intermediate
    wire intermediate;    
    //OR gates
    or_gate a_b(.a(a), .b(b), .c(intermediate)); //OR a, b give intermediate
    or_gate a_b_c(.a(intermediate), .b(c), .c(d)); //OR intermediate, c give d    
endmodule

/**
    Fatih Baskýn, 150210710
    two input NAND gate
    @input a
    @input b
    @output c
    works by first AND a, b give a_and_b
    then NOT a_and_b gives c    
*/    
module nand_gate(a, b, c);
    //Inputs
    input wire a;
    input wire b;    
    //Intermediate wires
    wire a_and_b;    
    //AND operation
    and_gate intermediate(.a(a), .b(b), .c(a_and_b));    
    //Outputs
    output wire c;    
    //NAND operation
    not_gate NAND(.a(a_and_b), .b(c));        
endmodule

/**
    Fatih Baskýn, 150210710
    three input NAND gate
    @input a
    @input b
    @input c
    @output d
    works by first NAND a, b give intermediate_1
    then negate intermediate_1 by connecting to NAND, give intermediate_2   
    then NAND c and intermediate_2, give d as output
*/
module nand_gate_3input(a, b, c, d);
    //Inputs
    input wire a;
    input wire b;
    input wire c;    
    //Outputs
    output wire d;    
    //Operations
    //NANDs a,b gives intermediate_1
    wire intermediate_1;
    nand_gate a_b(.a(a), .b(b), .c(intermediate_1));
    //Negates intermediate_1 by connecting to NAND gate, gives intermediate_2
    wire intermediate_2;
    nand_gate a_b_negation(.a(intermediate_1), .b(intermediate_1), .c(intermediate_2));
    //Final NAND
    nand_gate final(.a(intermediate_2), .b(c), .c(d));   
endmodule

/**
    Fatih Baskýn, 150210710
    two input XOR gate
    @input a
    @input b
    @output c
    works by first complementing a and b
    then ANDs (a, b complement) and (a complement, b)
    then ORs ab' and a'b, gives result c   
*/
module xor_gate(a, b, c);
    //Inputs
    input wire a;
    input wire b;    
    //Complement wires
    wire a_comp;
    wire b_comp;    
    //Complements
    not_gate not_a(.a(a), .b(a_comp)); //NOT a, give a_comp
    not_gate not_b(.a(b), .b(b_comp)); //NOT b, give b_comp    
    //AND wires
    wire a_comp_and_b; //a'b
    wire a_and_b_comp; //ab'    
    //AND operations    
    and_gate not_a_and_b(.a(a_comp), .b(b), .c(a_comp_and_b)); //a'b
    and_gate a_and_not_b(.a(a), .b(b_comp), .c(a_and_b_comp)); //ab'
    //Outputs
    output wire c;    
    //XOR
    or_gate XOR(.a(a_comp_and_b), .b(a_and_b_comp), .c(c)); //a'b + ab'
endmodule

/**
    Fatih Baskýn, 150210710
    2:1 Multiplexer
    @input i_0
    @input i_1
    @selector s_0
    @output o
    First complements s_0 because
    IF s_0 = 0 then s_0_comp = 1, s_0_comp and i_0 = i_0
    IF s_1 = 1 then s_1 and i_1 = i_1
    Note that 1 AND x = x (Identity Rule)
    Finally or the i_0_select and i_1_select, give the output
*/
module mux_2to1(i_0, i_1, s_0, o);
    //Inputs
    input wire i_0;
    input wire i_1;    
    //Selectors
    input wire s_0;    
    //Outputs
    output wire o;    
    //s_0 complement
    wire s_0_comp;
    not_gate not_s_0(.a(s_0), .b(s_0_comp)); //Negate s_0
    //Intermediate wires
    wire i_0_select;
    wire i_1_select;    
    //AND operations
    //If s_0 = 0 then s_0_comp = 1, s_0_comp and i_0 = i_0
    and_gate select_i_0(.a(i_0), .b(s_0_comp), .c(i_0_select));
    //If s_1 = 1 then s_1 and i_1 = i_1
    and_gate select_i_1(.a(i_1), .b(s_0), .c(i_1_select));    
    //OR operations
    //OR the i_0_select and i_1_select wires.
    or_gate MUX_2to1(.a(i_0_select), .b(i_1_select), .c(o));        
endmodule

/**
    Fatih Baskýn, 150210710
    4:1 Multiplexer
    @input i_0      @input i_1
    @input i_2      @input i_3    
    @selector s_0   @selector s_1
    @output o
    IF s_0 = 0, first level multiplexers select i_0 or i_2
    IF s_0 = 1, first level multiplexers select i_1 or i_3 
    Second level multiplexer selects output of the first level multiplexers
    IF s_1 = 0, second level multiplexer selects output of i_0 - i_1 MUX
    IF s_1 = 1, second level multiplexer selects output of i_2 - i_3 MUX
*/
module mux_4to1(i_0, i_1, i_2, i_3, s_0, s_1, o);
    //Inputs
    input wire i_0;
    input wire i_1;
    input wire i_2;
    input wire i_3;    
    //Selectors
    input wire s_0;
    input wire s_1;    
    //Output
    output wire o;    
    //Selector cables for s_0
    wire s_1_equals_0;
    wire s_1_equals_1;    
    //s_0 operations
    //  i_0 - i_1 MUX, s_1 = 0
    mux_2to1 for_s_1_equals_0(.i_0(i_0), .i_1(i_1), .s_0(s_0), .o(s_1_equals_0));
    //  i_2 - i_3 MUX, s_1 = 1
    mux_2to1 for_s_1_equals_1(.i_0(i_2), .i_1(i_3), .s_0(s_0), .o(s_1_equals_1));    
    //s_1 operations    
    mux_2to1 for_s_1(.i_0(s_1_equals_0), .i_1(s_1_equals_1), .s_0(s_1), .o(o));       
endmodule

/**
    Fatih Baskýn, 150210710
    8:1 Multiplexer
    @input i_0      @input i_1      @input i_2      @input i_3
    @input i_4      @input i_5      @inpýt i_6      @input i_7
    @selector s_0   @selector s_1   @selector s_2   
    @output o
    First levels multiplexers are selecting four inputs via s_1 and s_0
    for_s_2_equals_0 is a 4:1 MUX that selects i_0, i_1, i_2, i_3
    for_s_2_equals_1 is a 4:1 MUX that selects i_4, i_5, i_6, i_7
    Second level multiplexer is a 2:1 multiplexer that selects the output of first level MUXes
*/
module mux_8to1(i_0, i_1, i_2, i_3, i_4, i_5, i_6, i_7, s_0, s_1, s_2, o);
    //Inputs
    input wire i_0;
    input wire i_1;
    input wire i_2;
    input wire i_3;
    input wire i_4;
    input wire i_5;
    input wire i_6;
    input wire i_7;    
    //Selectors
    input wire s_0;
    input wire s_1;
    input wire s_2;    
    //Output
    output wire o;    
    //Selector cables for first level MUXes
    wire s_2_equals_0;
    wire s_2_equals_1;    
    //s_0 and s_1 operations
    mux_4to1 for_s_2_equals_0(.i_0(i_0), .i_1(i_1), .i_2(i_2), .i_3(i_3), 
                              .s_0(s_0), .s_1(s_1), .o(s_2_equals_0));
    mux_4to1 for_s_2_equals_1(.i_0(i_4), .i_1(i_5), .i_2(i_6), .i_3(i_7), 
                              .s_0(s_0), .s_1(s_1), .o(s_2_equals_1));    
    //s_2 operations
    mux_2to1 for_s_2(.i_0(s_2_equals_0), .i_1(s_2_equals_1), .s_0(s_2), .o(o));        
endmodule

/**
    Fatih Baskýn, 150210710
    3:8 Decoder
    @input i_0  @input i_1  @input i_2
    @output o_0 output o_1  @output o_2 output o_3  
    @output o_4 output o_5  @output o_6 output o_7
    First, negates i_0, i_1, i_2 seperately
    Then for the scenarios of 000 001 010 011 100 101 110 111
    Makes necessary AND operations with inputs or their complements  
    
*/
module dec_3to8(i_0, i_1, i_2,
                o_0, o_1, o_2, o_3,
                o_4, o_5, o_6, o_7);
    //Inputs
    input wire i_0;
    input wire i_1;
    input wire i_2;    
    //Outputs
    output wire o_0; output wire o_1;
    output wire o_2; output wire o_3;
    output wire o_4; output wire o_5;
    output wire o_6; output wire o_7;    
    //Complements
    wire i_0_comp;
    not_gate not_i_0(.a(i_0), .b(i_0_comp));
    wire i_1_comp;
    not_gate not_i_1(.a(i_1), .b(i_1_comp));
    wire i_2_comp;
    not_gate not_i_2(.a(i_2), .b(i_2_comp));
    //Output operations    
    //  Output_0 (000)
    and_gate_3input output_0(.a(i_0_comp), .b(i_1_comp), .c(i_2_comp), .d(o_0));
    //  Output_1 (001)
    and_gate_3input output_1(.a(i_0), .b(i_1_comp), .c(i_2_comp), .d(o_1));
    //  Output_2 (010)
    and_gate_3input output_2(.a(i_0_comp), .b(i_1), .c(i_2_comp), .d(o_2));
    //  Output_3 (011)
    and_gate_3input output_3(.a(i_0), .b(i_1), .c(i_2_comp), .d(o_3));
    //  Output_4 (100)
    and_gate_3input output_4(.a(i_0_comp), .b(i_1_comp), .c(i_2), .d(o_4));
    //  Output_5 (101)
    and_gate_3input output_5(.a(i_0), .b(i_1_comp), .c(i_2), .d(o_5));
    //  Output_6 (110)
    and_gate_3input output_6(.a(i_0_comp), .b(i_1), .c(i_2), .d(o_6));
    //  Output_7 (111)
    and_gate_3input output_7(.a(i_0), .b(i_1), .c(i_2), .d(o_7));                    
endmodule

/**
    Fatih Baskýn, 150210710
    Circuit of PART 2
    @input a    @input b
    @input c    @input d
    @output o
    b'd' + a'bc + acd

*/
module part_2(a, b, c, d, o);
    //Inputs
    input wire a;
    input wire b;
    input wire c;
    input wire d;    
    //Output
    output wire o;    
    //b'd'
    wire b_comp;
    not_gate not_b(.a(b), .b(b_comp));
    wire d_comp;
    not_gate not_d(.a(d), .b(d_comp));
    wire intermediate_1;
    and_gate notB_notD(.a(b_comp), .b(d_comp), .c(intermediate_1));    
    //a'bc
    wire a_comp;
    not_gate not_a(.a(a), .b(a_comp));
    wire intermediate_2;
    and_gate_3input notA_b_c(.a(a_comp), .b(b), .c(c), .d(intermediate_2));    
    //acd
    wire intermediate_3;
    and_gate_3input a_c_d(.a(a), .b(c), .c(d), .d(intermediate_3));    
    //Final OR
    or_gate_3input final(.a(intermediate_1), .b(intermediate_2), .c(intermediate_3), .d(o));         
endmodule

/**
    Fatih Baskýn, 150210710
    Circuit of PART 3
    @input a    @input b
    @input c    @input d
    @output o
    Implemented PART 2 with NAND gates    
*/
module part_3(a, b, c, d, o);
    //Inputs
    input wire a;
    input wire b;
    input wire c;
    input wire d;
    //Output
    output wire o;    
    //Complements
    wire a_comp;
    nand_gate not_a(.a(a), .b(a), .c(a_comp));
    wire b_comp;
    nand_gate not_b(.a(b), .b(b), .c(b_comp));    
    wire d_comp;
    nand_gate not_d(.a(d), .b(d), .c(d_comp));    
    //Intermediate NAND operations
    //  b'd'
    wire intermediate_1;
    nand_gate b_d(.a(b_comp), .b(d_comp), .c(intermediate_1));
    //  a'bc    
    wire intermediate_2;
    nand_gate_3input a_b_c(.a(a_comp), .b(b), .c(c), .d(intermediate_2));
    //  acd
    wire intermediate_3;
    nand_gate_3input a_c_d(.a(a), .b(c), .c(d), .d(intermediate_3));    
    //Fýnal NAND operation
    nand_gate_3input FINAL(.a(intermediate_1), .b(intermediate_2),
                           .c(intermediate_3), .d(o));
endmodule

/**
    Fatih Baskýn, 150210710
    Circuit of PART 4
    @input a    @input b
    @input c    @input d
    @output o
    Implemented PART 2 with 8:1 MUX and NOT gate.   
    i_0 = d', i_1 = d', i_2 = 0 , i_3 = 1 ,
    i_4 = d', i_5 = 1 , i_6 = 0 , i_7 = d ,
*/
module part_4(a ,b ,c, d, o);
    //Inputs
    input wire a;
    input wire b;
    input wire c;
    input wire d;    
    //Outputs
    output wire o;    
    //Complements
    wire d_comp;
    not_gate not_d(.a(d), .b(d_comp));    
    //0 and 1 inputs to MUX
    //  dd' = 0 (Law of Dominance)
    wire wire_0;
    and_gate zero(.a(d), .b(d_comp), .c(wire_0));
    //  d + d' = 1 (Law of Inverse)
    wire wire_1;
    or_gate one(.a(d), .b(d_comp), .c(wire_1));    
    //MUX i_0 = d', i_1 = d', i_2 = 0 , i_3 = 1 ,
    //    i_4 = d', i_5 = 1 , i_6 = 0 , i_7 = d ,
    mux_8to1 MUX(.i_0(d_comp), .i_1(d_comp), .i_2(wire_0), .i_3(wire_1),
                 .i_4(d_comp), .i_5(wire_1), .i_6(wire_0), .i_7(d),
                 .s_0(c), .s_1(b), .s_2(a), .o(o));        
endmodule

/**
    Fatih Baskýn, 150210710
    Circuit of PART 4
    @input a    @input b    @input c
    @output f_2 @output f_3
    Function 2 = a'bc + ab'c
    Function 3 = abc' + ab (abc' and abc)
    for f_2, decoder's outputs are o_3 and o_5, OR them get f_2
    for f_2, decoder's outputs are o_6 and o_7, OR them get f_3
*/
module part_5(a, b, c, f_2, f_3);
    //Inputs
    input wire a;
    input wire b;
    input wire c;    
    //Outputs
    output wire f_2;
    output wire f_3;    
    //Intermediate wires
    wire output_3;
    wire output_5;
    wire output_6;
    wire output_7;    
    //Decoder
    dec_3to8 decoder(.i_0(c), .i_1(b), .i_2(a),
                     .o_3(output_3), .o_5(output_5),
                     .o_6(output_6), .o_7(output_7));    
    //Function 2 = a'bc + ab'c
    or_gate func_2(.a(output_3), .b(output_5), .c(f_2));    
    //Function 3 = abc' + ab
    or_gate func_3(.a(output_6), .b(output_7), .c(f_3));    
endmodule

/**
    Elvan Teke, 150190102
    Half Adder circuit
    @input a    @input b
    @output s   @output c
    sums a and b, gives s sum and c carry   
*/
module half_adder(a, b, s, c);
    //Inputs
    input wire a;
    input wire b;
    //Outputs
    output wire s;
    output wire c;
    //Operations
    and_gate carry(.a(a), .b(b), .c(c));
    xor_gate half(.a(a), .b(b), .c(s));
endmodule

/**
    Elvan Teke, 150190102
    One Bit Full Adder circuit
    @input a    @input b    @input cin
    @output s   @output cout
    sums a and b, gives ab and c1, 
    then sums s1 and cin (carry in) gives s and c2
    ors c1 and c2 to get cout (carry out)
*/
module one_bit_full_adder(a, b, cin, s, cout);
    //Inputs
    input wire a;
    input wire b;
    input wire cin;
    //Outputs
    output wire s;
    output wire cout;
    //Intermediate wires
    wire ab;
    wire c1;
    wire c2;
    //Operations
    half_adder inter_add(.a(a), .b(b), .s(ab), .c(c1)); //ADDs a and b
    half_adder one_full_adder(.a(ab), .b(cin), .s(s), .c(c2)); //ADDs ab and cin (carry in)
    or_gate one_carry(.a(c1), .b(c2), .c(cout)); //ORs carries of two half adders
endmodule

/**
    Elvan Teke, 150190102
    Four Bit Full Adder circuit
    @input A (4-bit)
    @input B (4-bit)  
    @input Cin (1-bit)
    @output S (4-bit)
    @output cout (1-bit)
    works by connecting 4 one-bit-full-adders in series
*/
module four_bit_full_adder(
    input [3:0] A,
    input [3:0] B,
    input [0:0] Cin,
    output [3:0] S,
    output [0:0] Cout
    );
    //Intermediate wires
    wire c1;
    wire c2;
    wire c3;
    //Adders
    one_bit_full_adder add_one(.a(A[0]), .b(B[0]), .cin(Cin),.s(S[0]), .cout(c1));
    one_bit_full_adder add_two(.a(A[1]), .b(B[1]), .cin(c1),.s(S[1]), .cout(c2));
    one_bit_full_adder add_three(.a(A[2]), .b(B[2]), .cin(c2),.s(S[2]), .cout(c3));
    one_bit_full_adder add_four(.a(A[3]), .b(B[3]), .cin(c3),.s(S[3]), .cout(Cout));
endmodule

/**
    Elvan Teke, 150190102
    Eight Bit Full Adder circuit
    @input A (8-bit)
    @input B (8-bit)  
    @input Cin (1-bit)
    @output S (8-bit)
    @output cout (1-bit)
    works by connecting 8 one-bit-full-adders in series
*/
module eight_bit_full_adder(
    input [7:0] A,
    input [7:0] B,
    input [0:0] Cin,
    output [7:0] S,
    output [0:0] Cout
    );
    //Intermediate wires
    wire c1, c2, c3, c4, c5, c6, c7;
    //Adders        
    one_bit_full_adder first_adder(.a(A[0]), .b(B[0]), .cin(Cin),.s(S[0]), .cout(c1));
    one_bit_full_adder second_adder(.a(A[1]), .b(B[1]), .cin(c1),.s(S[1]), .cout(c2));
    one_bit_full_adder third_adder(.a(A[2]), .b(B[2]), .cin(c2),.s(S[2]), .cout(c3));
    one_bit_full_adder fourth_adder(.a(A[3]), .b(B[3]), .cin(c3),.s(S[3]), .cout(c4));
    one_bit_full_adder fifth_adder(.a(A[4]), .b(B[4]), .cin(c4),.s(S[4]), .cout(c5));
    one_bit_full_adder sixth_adder(.a(A[5]), .b(B[5]), .cin(c5),.s(S[5]), .cout(c6));
    one_bit_full_adder seventh_adder(.a(A[6]), .b(B[6]), .cin(c6),.s(S[6]), .cout(c7));
    one_bit_full_adder eighth_adder(.a(A[7]), .b(B[7]), .cin(c7),.s(S[7]), .cout(Cout));
endmodule

/**
    Elvan Teke, 150190102
    Sixteen Bit Adder/Subtractor circuit
    @input A (16-bit)
    @input B (16-bit)  
    @input Cin (1-bit)
    @output S (16-bit)
    @output cout (1-bit)
    works by connecting 2 8-bit-full-adders in series and 
    XORing input bits of B with Cin
    B XOR 0 = B, B XOR 1 = B' (1's complement)
    IF Cin = 0, A + B
    IF Cin = 1, A + B' + 1 = A - B  
*/
module Adder_Subtractor(
    input [15:0] A,
    input [15:0] B,
    input [0:0] Cin,
    output [15:0] S,
    output [0:0] Cout
    );
    //intermediate wires
    wire [15:0] b_xor, c1; //c1 for connecting two 8-bit adder
    //XORs
    xor_gate b0_xor(.a(B[0]), .b(Cin), .c(b_xor[0]));
    xor_gate b1_xor(.a(B[1]), .b(Cin), .c(b_xor[1]));
    xor_gate b2_xor(.a(B[2]), .b(Cin), .c(b_xor[2]));
    xor_gate b3_xor(.a(B[3]), .b(Cin), .c(b_xor[3]));
    xor_gate b4_xor(.a(B[4]), .b(Cin), .c(b_xor[4]));
    xor_gate b5_xor(.a(B[5]), .b(Cin), .c(b_xor[5]));
    xor_gate b6_xor(.a(B[6]), .b(Cin), .c(b_xor[6]));
    xor_gate b7_xor(.a(B[7]), .b(Cin), .c(b_xor[7]));
    xor_gate b8_xor(.a(B[8]), .b(Cin), .c(b_xor[8]));
    xor_gate b9_xor(.a(B[9]), .b(Cin), .c(b_xor[9]));
    xor_gate b10_xor(.a(B[10]), .b(Cin), .c(b_xor[10]));
    xor_gate b11_xor(.a(B[11]), .b(Cin), .c(b_xor[11]));
    xor_gate b12_xor(.a(B[12]), .b(Cin), .c(b_xor[12]));
    xor_gate b13_xor(.a(B[13]), .b(Cin), .c(b_xor[13]));
    xor_gate b14_xor(.a(B[14]), .b(Cin), .c(b_xor[14]));
    xor_gate b15_xor(.a(B[15]), .b(Cin), .c(b_xor[15]));
    //Adders    
    eight_bit_full_adder first_adder(.A(A[7:0]), .B(b_xor[7:0]), .Cin(Cin), .S(S[7:0]), .Cout(c1));
    eight_bit_full_adder second_adder(.A(A[15:8]), .B(b_xor[15:8]), .Cin(c1), .S(S[15:8]), .Cout(Cout));
endmodule

/**
    Fatih Baskýn, 150210710
    PART 11 circuit
    @input A (16-bit)
    @input B (16-bit)
    @output S (16-bit)
    @output Cout (1-bit)
    B - 2A
    Shift A to left to multiply by two
    After shift operation connect B and shift
    into sixteen-bit-adder-subtractor
    give 1 to carry of addder-subtractor so it subtracts    
*/
module part_11(
    input [15:0] A,
    input [15:0] B,
    output [15:0] S,
    output [0:0] Cout);
    //One and Zero
    wire one, zero, a_0_comp;
    not_gate not_a_0(.a(A[0]), .b(a_0_comp));
    and_gate generate_zero(.a(A[0]), .b(a_0_comp), .c(zero)); //xx' = 0 (Dominance Law)
    or_gate generate_one(.a(A[0]), .b(a_0_comp), .c(one)); //x + x' = 0 (Inverse Law)
    //Shifting A to left
    wire [15:0] shift;  assign shift[0] = zero;
    assign shift[1]= A[0];      assign shift[2]= A[1];      assign shift[3]= A[2];
    assign shift[4]= A[3];      assign shift[5]= A[4];      assign shift[6]= A[5];
    assign shift[7]= A[6];      assign shift[8]= A[7];      assign shift[9]= A[8];
    assign shift[10]= A[9];     assign shift[11]= A[10];    assign shift[12]= A[11];
    assign shift[13]= A[12];    assign shift[14]= A[13];    assign shift[15]= A[14];
    //Adder-Subtractor, note that I shift A right and give zero as A[0] and one to Cin
    Adder_Subtractor part_11(.A(B[15:0]), .B(shift[15:0]), 
                             .Cin(one), .S(S[15:0]), .Cout(Cout));    
endmodule