/**
    Fatih Baskýn, 150210710
    simulation of NOT gate
*/
module not_gate_sim();
    //Inputs
    reg A;    
    //Outputs
    wire B;    
    //Module
    not_gate uut(.a(A), .b(B));    
    //Test phase
    initial begin
        A = 0; #250;
        A = 1; #250;
        //End
    end        
 endmodule
 
/**
     Fatih Baskýn, 150210710
     simulation of two input AND gate
 */ 
 module and_gate_sim();
     //Inputs
     reg A;
     reg B;     
     //Outputs
     wire C;     
     //Module    
     and_gate uut(.a(A), .b(B), .c(C));     
     //Test Phase    
     initial begin
         A = 0; B = 0; #250;
         A = 0; B = 1; #250;
         A = 1; B = 0; #250;
         A = 1; B = 1; #250;
         //End
     end     
 endmodule
 
/**
    Fatih Baskýn, 150210710
    simulation of three input AND gate
*/ 
module and_gate_3input_sim();
    //Inputs
    reg A;
    reg B;
    reg C;    
    //Outputs
    wire D;    
    //Module
    and_gate_3input uut(.a(A), .b(B), .c(C), .d(D));
    //Test Phase    
    initial begin
        A = 0; B = 0; C = 0; #10; A = 0; B = 0; C = 1; #10;
        A = 0; B = 1; C = 0; #10; A = 0; B = 1; C = 1; #10;
        A = 1; B = 0; C = 0; #10; A = 1; B = 0; C = 1; #10;
        A = 1; B = 1; C = 0; #10; A = 1; B = 1; C = 1; #10;
        //End of test
        A = 0; B = 0; C = 0; #10;    
    end     
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of two input OR gate
*/ 
module or_gate_sim();
    //Inputs
    reg A;
    reg B;    
    //Outputs
    wire C;    
    //Module    
    or_gate uut(.a(A), .b(B), .c(C));    
    //Test phase    
    initial begin
        A = 0; B = 0; #250;
        A = 0; B = 1; #250;
        A = 1; B = 0; #250;
        A = 1; B = 1; #250;
    end    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of three input OR gate
*/ 
module or_gate_3input_sim();
    //Inputs
    reg A;
    reg B;
    reg C;    
    //Outputs
    wire D;    
    //Module
    or_gate_3input uut(.a(A), .b(B), .c(C), .d(D));
    //Test phase    
    initial begin
        A = 0; B = 0; C = 0; #10; A = 0; B = 0; C = 1; #10;
        A = 0; B = 1; C = 0; #10; A = 0; B = 1; C = 1; #10;
        A = 1; B = 0; C = 0; #10; A = 1; B = 0; C = 1; #10;
        A = 1; B = 1; C = 0; #10; A = 1; B = 1; C = 1; #10;
        //end of test
        A = 0; B = 0; C = 0; #10;    
    end     
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of two input NAND gate
*/ 
module nand_gate_sim();
    //Inputs
    reg A;
    reg B;    
    //Outputs
    wire C;    
    //Module    
    nand_gate uut(.a(A), .b(B), .c(C));    
    //Test phase    
    initial begin
        A = 0; B = 0; #250;
        A = 0; B = 1; #250;
        A = 1; B = 0; #250;
        A = 1; B = 1; #250;
    end
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of three input NAND gate
*/ 
module nand_gate_3input_sim();
    //Inputs
    reg A;
    reg B;
    reg C;    
    //Outputs
    wire D;    
    //Module
    nand_gate_3input uut(.a(A), .b(B), .c(C), .d(D));    
    initial begin
        A = 0; B = 0; C = 0; #10; A = 0; B = 0; C = 1; #10;
        A = 0; B = 1; C = 0; #10; A = 0; B = 1; C = 1; #10;
        A = 1; B = 0; C = 0; #10; A = 1; B = 0; C = 1; #10;
        A = 1; B = 1; C = 0; #10; A = 1; B = 1; C = 1; #10;
        //end of test
        A = 0; B = 0; C = 0; #10;    
    end     
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of two input XOR gate
*/ 
module xor_gate_sim();
    //Inputs
    reg A;
    reg B;    
    //Outputs
    wire C;    
    //Module    
    xor_gate uut(.a(A), .b(B), .c(C));    
    //Test phase    
    initial begin
        A = 0; B = 0; #250;
        A = 0; B = 1; #250;
        A = 1; B = 0; #250;
        A = 1; B = 1; #250;
    end    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of 2:1 Multiplexer
    Tested every possible case I_0, I_1 and S_0 can take, 2^3 = 8 cases    
*/
module mux_2to1_sim();
    //Inputs
    reg I_0;
    reg I_1;
    //Selectors
    reg S_0;    
    //Outputs
    wire O;    
    //Module    
    mux_2to1 uut(.i_0(I_0), .i_1(I_1), .s_0(S_0) , .o(O));    
    //Test phase    
    initial begin
        I_0 = 0; I_1 = 0; S_0 = 0; #25;
        I_0 = 0; I_1 = 1; S_0 = 0; #25;
        I_0 = 1; I_1 = 0; S_0 = 0; #25;
        I_0 = 1; I_1 = 1; S_0 = 0; #25;
        I_0 = 0; I_1 = 0; S_0 = 1; #25;
        I_0 = 0; I_1 = 1; S_0 = 1; #25;
        I_0 = 1; I_1 = 0; S_0 = 1; #25;
        I_0 = 1; I_1 = 1; S_0 = 1; #25;
        I_0 = 0; I_1 = 0; S_0 = 0; #25;
    end    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of 4:1 Multiplexer
    Tested for s_1 and s_0 corresponding inputs 1 or 0 to validate selects correctly
*/
module mux_4to1_sim();
    //Inputs
    reg I_0;
    reg I_1;
    reg I_2;
    reg I_3;
    //Selectors
    reg S_0;
    reg S_1;    
    //Outputs
    wire O;    
    //Module    
    mux_4to1 uut(.i_0(I_0), .i_1(I_1), .i_2(I_2), .i_3(I_3), .s_0(S_0), .s_1(S_1), .o(O));    
    //Test phase    
    initial begin
        //I_0 = 0, S_1_S_0 = 00
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        S_0 = 0; S_1 = 0; #10;
        //I_0 = 1, S_1_S_0 = 00
        I_0 = 1; I_1 = 0; I_2 = 0; I_3 = 0;
        S_0 = 0; S_1 = 0; #10;
        //I_1 = 0, S_1_S_0 = 01
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        S_0 = 1; S_1 = 0; #10;
        //I_1 = 1, S_1_S_0 = 01
        I_0 = 0; I_1 = 1; I_2 = 0; I_3 = 0;
        S_0 = 1; S_1 = 0; #10;   
        //I_2 = 0, S_1_S_0 = 10
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        S_0 = 0; S_1 = 1; #10;
        //I_2 = 1, S_1_S_0 = 010
        I_0 = 0; I_1 = 0; I_2 = 1; I_3 = 0;
        S_0 = 0; S_1 = 1; #10;
        //I_3 = 0, S_1_S_0 = 11
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        S_0 = 1; S_1 = 1; #10;
        //I_3 = 1, S_1_S_0 = 11
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 1;
        S_0 = 1; S_1 = 1; #10;        
        //End
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        S_0 = 0; S_1 = 0; #10;    
    end
    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of 8:1 Multiplexer
    Tested for s_2, s_1 and s_0 corresponding inputs 1 or 0 to validate selects correctly
*/
module mux_8to1_sim();
    //Inputs
    reg I_0; reg I_1; reg I_2; reg I_3;
    reg I_4; reg I_5; reg I_6; reg I_7;
    //Selectors
    reg S_0; reg S_1; reg S_2;
    //Outputs
    wire O;    
    //Module
    mux_8to1 uut(.i_0(I_0), .i_1(I_1), .i_2(I_2), .i_3(I_3),
                 .i_4(I_4), .i_5(I_5), .i_6(I_6), .i_7(I_7),
                 .s_0(S_0), .s_1(S_1), .s_2(S_2), .o(O));    
    //Test phase
    initial begin
        //I_0 = 0, S_2_S_1_S_0 = 000
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 0; S_2 = 0; #10;
        //I_0 = 1, S_2_S_1_S_0 = 000
        I_0 = 1; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 0; S_2 = 0; #10;
        //I_1 = 0, S_2_S_1_S_0 = 001
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 1; S_1 = 0; S_2 = 0; #10;
        //I_1 = 1, S_2_S_1_S_0 = 001
        I_0 = 0; I_1 = 1; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 1; S_1 = 0; S_2 = 0; #10;   
        //I_2 = 0, S_2_S_1_S_0 = 010
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 1; S_2 = 0; #10;
        //I_2 = 1, S_2_S_1_S_0 = 010
        I_0 = 0; I_1 = 0; I_2 = 1; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 1; S_2 = 0; #10;
        //I_3 = 0, S_2_S_1_S_0 = 011
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 1; S_1 = 1; S_2 = 0; #10;
        //I_3 = 1, S_2_S_1_S_0 = 011
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 1;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 1; S_1 = 1; S_2 = 0; #10;
        //I_4 = 0, S_2_S_1_S_0 = 100
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 0; S_2 = 1; #10;
        //I_4 = 1, S_2_S_1_S_0 = 100
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 1; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 0; S_2 = 1; #10;
        //I_5 = 0, S_2_S_1_S_0 = 101
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 1; S_1 = 0; S_2 = 1; #10;
        //I_5 = 1, S_2_S_1_S_0 = 101
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 1; I_6 = 0; I_7 = 0;
        S_0 = 1; S_1 = 0; S_2 = 1; #10;   
        //I_6 = 0, S_2_S_1_S_0 = 110
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 1; S_2 = 1; #10;
        //I_6 = 1, S_2_S_1_S_0 = 110
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 1; I_7 = 0;
        S_0 = 0; S_1 = 1; S_2 = 1; #10;
        //I_7 = 0, S_2_S_1_S_0 = 111
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 1; S_1 = 1; S_2 = 1; #10;
        //I_7 = 1, S_2_S_1_S_0 = 111
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 1;
        S_0 = 1; S_1 = 1; S_2 = 1; #10;
        //End
        I_0 = 0; I_1 = 0; I_2 = 0; I_3 = 0;
        I_4 = 0; I_5 = 0; I_6 = 0; I_7 = 0;
        S_0 = 0; S_1 = 0; S_2 = 0; #10;            
    end    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of 3:8 Decoder
    Tested all possible inputs
*/
module dec_3to8_sim();
    //Inputs
    reg i_0;
    reg i_1;
    reg i_2;    
    //Outputs
    wire o_0;   wire o_1;        
    wire o_2;   wire o_3;
    wire o_4;   wire o_5; 
    wire o_6;   wire o_7;    
    //Module
    dec_3to8 uut(.i_0(i_0), .i_1(i_1), .i_2(i_2),
                 .o_0(o_0), .o_1(o_1), .o_2(o_2), .o_3(o_3),
                 .o_4(o_4), .o_5(o_5), .o_6(o_6), .o_7(o_7));
    //Test phase
    initial begin
        i_0 = 0; i_1 = 0; i_2 = 0; #20;
        i_0 = 1; i_1 = 0; i_2 = 0; #20;
        i_0 = 0; i_1 = 1; i_2 = 0; #20;
        i_0 = 1; i_1 = 1; i_2 = 0; #20;
        i_0 = 0; i_1 = 0; i_2 = 1; #20;
        i_0 = 1; i_1 = 0; i_2 = 1; #20;
        i_0 = 0; i_1 = 1; i_2 = 1; #20;
        i_0 = 1; i_1 = 1; i_2 = 1; #20;
        //End
        i_0 = 0; i_1 = 0; i_2 = 0; #20;    
    end         
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of PART 2
    b'd' + a'bc + acd
    Expecting positive outputs in cases of:
    0, 2, 6, 7, 8, 10, 11, 15
    Don't care conditions at:
    4
*/
module part_2_sim();
    //Inputs
    reg A;
    reg B;
    reg C;
    reg D;    
    //Outputs
    wire O;    
    //Module
    part_2 uut(.a(A), .b(B), .c(C), .d(D), .o(O));
    //Test phase    
    initial begin
        //0000 = 0                  0001 = 1
        A = 0; B = 0; C = 0; D = 0; #10; A = 0; B = 0; C = 0; D = 1; #10;
        //0010 = 2                  0011 = 3
        A = 0; B = 0; C = 1; D = 0; #10; A = 0; B = 0; C = 1; D = 1; #10;
        //0100 = 4                  0101 = 5
        A = 0; B = 1; C = 0; D = 0; #10; A = 0; B = 1; C = 0; D = 1; #10;
        //0110 = 6                  0111 = 7
        A = 0; B = 1; C = 1; D = 0; #10; A = 0; B = 1; C = 1; D = 1; #10; 
        //1000 = 8                  1001 = 9   
        A = 1; B = 0; C = 0; D = 0; #10; A = 1; B = 0; C = 0; D = 1; #10;
        //1010 = 10                 1011 = 11   
        A = 1; B = 0; C = 1; D = 0; #10; A = 1; B = 0; C = 1; D = 1; #10;
        //1100 = 12                 1101 = 13 
        A = 1; B = 1; C = 0; D = 0; #10; A = 1; B = 1; C = 0; D = 1; #10;
        //1110 = 14                 1111 = 15  
        A = 1; B = 1; C = 1; D = 0; #10; A = 1; B = 1; C = 1; D = 1; #10;     
        //END 
        A = 0; B = 0; C = 0; D = 0; #10;       
    end    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of PART 3
    b'd' + a'bc + acd
    Expecting positive outputs in cases of:
    0, 2, 6, 7, 8, 10, 11, 15
    Don't care conditions at:
    4
*/
module part_3_sim();
    //Inputs
    reg A;
    reg B;
    reg C;
    reg D;    
    //Outputs
    wire O;    
    //Module
    part_3 uut(.a(A), .b(B), .c(C), .d(D), .o(O));
    //Test phase
    initial begin
        //0000 = 0                  0001 = 1
        A = 0; B = 0; C = 0; D = 0; #10; A = 0; B = 0; C = 0; D = 1; #10;
        //0010 = 2                  0011 = 3
        A = 0; B = 0; C = 1; D = 0; #10; A = 0; B = 0; C = 1; D = 1; #10;
         //0100 = 4                  0101 = 5
        A = 0; B = 1; C = 0; D = 0; #10; A = 0; B = 1; C = 0; D = 1; #10;
        //0110 = 6                  0111 = 7
        A = 0; B = 1; C = 1; D = 0; #10; A = 0; B = 1; C = 1; D = 1; #10; 
        //1000 = 8                  1001 = 9   
        A = 1; B = 0; C = 0; D = 0; #10; A = 1; B = 0; C = 0; D = 1; #10;
        //1010 = 10                 1011 = 11   
        A = 1; B = 0; C = 1; D = 0; #10; A = 1; B = 0; C = 1; D = 1; #10;
        //1100 = 12                 1101 = 13 
        A = 1; B = 1; C = 0; D = 0; #10; A = 1; B = 1; C = 0; D = 1; #10;
        //1110 = 14                 1111 = 15  
        A = 1; B = 1; C = 1; D = 0; #10; A = 1; B = 1; C = 1; D = 1; #10;     
        //END 
        A = 0; B = 0; C = 0; D = 0; #10;    
    end    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of PART 4
    b'd' + a'bc + acd
    Expecting positive outputs in cases of:
    0, 2, 6, 7, 8, 10, 11, 15
    Don't care conditions at:
    4
*/
module part_4_sim();
    //Inputs
    reg A;
    reg B;
    reg C;
    reg D;    
    //Outputs
    wire O;    
    //Module
    part_4 uut(.a(A), .b(B), .c(C), .d(D), .o(O));
    //Test phase
    initial begin
        //0000 = 0                  0001 = 1
        A = 0; B = 0; C = 0; D = 0; #10; A = 0; B = 0; C = 0; D = 1; #10;
        //0010 = 2                  0011 = 3
        A = 0; B = 0; C = 1; D = 0; #10; A = 0; B = 0; C = 1; D = 1; #10;
        //0100 = 4                  0101 = 5
        A = 0; B = 1; C = 0; D = 0; #10; A = 0; B = 1; C = 0; D = 1; #10;
        //0110 = 6                  0111 = 7
        A = 0; B = 1; C = 1; D = 0; #10; A = 0; B = 1; C = 1; D = 1; #10; 
        //1000 = 8                  1001 = 9   
        A = 1; B = 0; C = 0; D = 0; #10; A = 1; B = 0; C = 0; D = 1; #10;
        //1010 = 10                 1011 = 11   
        A = 1; B = 0; C = 1; D = 0; #10; A = 1; B = 0; C = 1; D = 1; #10;
        //1100 = 12                 1101 = 13 
        A = 1; B = 1; C = 0; D = 0; #10; A = 1; B = 1; C = 0; D = 1; #10;
        //1110 = 14                 1111 = 15  
        A = 1; B = 1; C = 1; D = 0; #10; A = 1; B = 1; C = 1; D = 1; #10;     
        //END 
        A = 0; B = 0; C = 0; D = 0; #10;    
    end    
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of PART 5
    Function 2 = a'bc + ab'c
    Function 3 = abc' + ab (abc' and abc)
    for f_2, decoder's outputs are o_3 and o_5, expecting positive when 011 101
    for f_2, decoder's outputs are o_6 and o_7, expecting positive when 110 111
*/
module part_5_sim();
    //Inputs
    reg A;
    reg B;
    reg C;    
    //Outputs
    wire func_2;
    wire func_3;    
    //Module
    part_5 uut(.a(A), .b(B), .c(C), .f_2(func_2), .f_3(func_3));
    //Test phase    
    initial begin
        //000 = 0            001 = 1
        A = 0; B = 0; C = 0; #10; A = 0; B = 0; C = 1; #10;
        //010 = 2            011 = 3
        A = 0; B = 1; C = 0; #10; A = 0; B = 1; C = 1; #10;
        //100 = 4            101 = 5
        A = 1; B = 0; C = 0; #10; A = 1; B = 0; C = 1; #10;
        //110 = 6            111 = 7
        A = 1; B = 1; C = 0; #10; A = 1; B = 1; C = 1; #10;
        //End of test
        A = 0; B = 0; C = 0; #10;          
    end
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of Half Adder
    try different numbers as input
    0 + 0 ==> s = 0, c = 0
    0 + 1 ==> s = 1, c = 0
    1 + 0 ==> s = 1, c = 0
    1 + 1 ==> s = 0, c = 1
*/
module half_adder_sim();
    //Inputs
    reg A;
    reg B;
    //Outputs
    wire Sum;
    wire Carry;
    //Module
    half_adder uut(.a(A), .b(B), .s(Sum), .c(Carry));
    //Test phase
    initial begin
        A = 0; B = 0; #100;
        A = 0; B = 1; #100;
        A = 1; B = 0; #100;
        A = 1; B = 1; #100;
        //End
        A = 0; B = 0; #100;
    end
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of One Bit Full Adder
    try different numbers as input (A, B, Cin respectively)
    0 + 0 + 0 ==> s = 0, c = 0
    0 + 0 + 1 ==> s = 1, c = 0
    0 + 1 + 0 ==> s = 1, c = 0
    0 + 1 + 1 ==> s = 0, c = 1    
    1 + 0 + 0 ==> s = 1, c = 0
    1 + 0 + 1 ==> s = 0, c = 1
    1 + 1 + 0 ==> s = 0, c = 1
    1 + 1 + 1 ==> s = 1, c = 1    
*/
module one_bit_full_adder_sim();
    //Inputs
    reg A;
    reg B;
    reg Cin;
    //Outputs
    wire Sum;
    wire Cout;
    //Module
    one_bit_full_adder uut(.a(A), .b(B), .cin(Cin), .s(Sum), .cout(Cout));
    //Test phase
    initial begin
        A = 0; B = 0; Cin = 0; #100;    A = 0; B = 0; Cin = 1; #100;
        A = 0; B = 1; Cin = 0; #100;    A = 0; B = 1; Cin = 1; #100;
        A = 1; B = 0; Cin = 0; #100;    A = 1; B = 0; Cin = 1; #100;
        A = 1; B = 1; Cin = 0; #100;    A = 1; B = 1; Cin = 1; #100;
        //End
        A = 0; B = 0; Cin = 0; #100;
    end
endmodule

/*
    Fatih Baskýn, 150210710
    simulation of Four Bit Full Adder
    simulation of different numbers as input
    8 + 1 = 9   14 + 5 = 19 (overflow) = 3 (Cout = 1)
    4 + 5 = 9   11 + 10 = 21 (overflow) = 5 (Cout = 1)
    2 + 7 = 9   15 + 9 = 24 (overflow) = 8 (Cout = 1)
    6 + 3 = 9   8 + 12 = 20 (overflow) = 4 (Cout = 1)
*/
module four_bit_full_adder_sim();
    //Inputs
    reg [3:0] A;
    reg [3:0] B;
    reg Cin;
    //Outputs
    wire [3:0] Sum;
    wire Cout;
    //Module
    four_bit_full_adder uut(.A(A), .B(B), .Cin(Cin), .S(Sum), .Cout(Cout));
    //Test phase
    initial begin
        Cin = 0;
        A = 4'd8; B = 4'd1; #100;   A = 4'd14; B = 4'd5; #100;
        A = 4'd4; B = 4'd5; #100;   A = 4'd11; B = 4'd10; #100;
        A = 4'd2; B = 4'd7; #100;   A = 4'd15; B = 4'd9; #100;
        A = 4'd6; B = 4'd3; #100;   A = 4'd8; B = 4'd12; #100;
        //End
        A = 4'd0; B = 4'd0; #100;   
    end   
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of Eight Bit Full Adder
    simulation of different numbers as input
    29 + 5 = 34     51 + 92 = 143
    17 + 28 = 45    191 + 2 = 193    
    49 + 25 = 74    43 + 59 = 102
    200 + 95 = 295 (overflow) = 39 (Cout = 1)
    78 + 255 = 333 (0verflow) = 77 (Cout = 1)        
*/
module eight_bit_full_adder_sim();
    //Inputs
    reg [7:0] A;
    reg [7:0] B;
    reg Cin;
    //Outputs
    wire [7:0] Sum;
    wire Cout;
    //Module
    eight_bit_full_adder uut(.A(A), .B(B), .Cin(Cin), .S(Sum), .Cout(Cout));
    //Test phase
    initial begin
       Cin = 0;
       A = 8'd29; B = 8'd5; #80;    A = 8'd51; B = 8'd92; #80;    
       A = 8'd17; B = 8'd28; #80;   A = 8'd191; B = 8'd2; #80;
       A = 8'd49; B = 8'd25; #80;   A = 8'd43; B = 8'd59; #80; 
       A = 8'd200; B = 8'd95; #80;  A = 8'd78; B = 8'd255; #80; 
       //End
       A = 8'd0; B = 8'd0; #80;
    end
endmodule

/*
    Fatih Baskýn, 150210710
    simulation of Sixteen Bit Adder Subtractor
    simulation of different numbers as input
    23 + 3 = 26     21 + 75 = 96
    16800 + 16900 = 33700
    Note: 16-bit unsigned integer limit = 65535 = 2^16 - 1
    69834 (overflow, = 4298) + 66500 (overflow, = 964) = 5262 
    (Cout = 0 since inputs overflowed in the begining.)  
    325 + 97 = 422  44 + 190 = 234
    463 + 241 = 704 86 + 572 = 658
*/
module Adder_Subtractor_sim();
    //Inputs
    reg [15:0] A;
    reg [15:0] B;
    reg Cin;
    //Outputs
    wire [15:0] Sum;
    wire Cout;
    //Module
    Adder_Subtractor uut(.A(A), .B(B), .Cin(Cin), .S(Sum), .Cout(Cout));
    initial begin
       Cin = 0;
       A = 16'd23; B = 16'd3; #80;  A = 16'd21; B = 75; #80;
       A = 16'd16800; B = 16'd16900; #80;
       A = 16'd69834; B = 16'd66500; #80;
       A = 16'd325; B = 16'd97; #80;    A = 16'd44; B = 16'd190; #80;
       A = 16'd463; B = 16'd241; #80;   A = 16'd86; B = 16'd572; #80;
       //End
       A = 16'd0; B = 16'd0; #80;
    end        
endmodule

/**
    Fatih Baskýn, 150210710
    simulation of PART 11
    B - 2A
    A = 32, B = 7 ==> -57    A = 21, B = 85 ==> 43
    A = 16, B = 36 ==> 4     A = 256 B = 5 ==> -507
    A = 200, B = 95 ==> -305 A = 45, B = 135 ==> 45
    A = 36, B = 255 ==> 183  A = 25, B = 65 ==> 15
*/
module part_11_sim();
    //Inputs
    reg [15:0] A;
    reg [15:0] B;
    //Outputs
    wire [15:0] Sum;
    wire Cout;
    //Module
    part_11 uut(.A(A), .B(B), .S(Sum), .Cout(Cout));
    //Test Phase
    initial begin
        A = 16'd32; B = 16'd7; #80;     A = 16'd21; B = 16'd85; #80;
        A = 16'd16; B = 16'd36; #80;    A = 16'd256; B = 16'd5; #80;
        A = 16'd200; B = 16'd95; #80;   A = 16'd45; B = 16'd135; #80;
        A = 16'd36; B = 16'd255; #80;   A = 16'd25; B = 16'd65; #80;
        //End
        A = 16'd0; B = 16'd0; #80;
    end    
endmodule    