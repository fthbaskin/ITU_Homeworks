// Fatih Baskýn 150210710
module nor_gate(
                input wire a,
                input wire b,
                output wire c);
    // Operation
    assign c = !(a|b);
endmodule

// Fatih Baskýn 150210710
module sr_latch_no_enable(
                            input wire S,
                            input wire R,
                            output wire Q,
                            output wire Q_neg);
    // S NOR
    nor_gate input_S(.a(S), .b(Q), .c(Q_neg));
    // R NOR
    nor_gate input_R(.a(R), .b(Q_neg), .c(Q));
endmodule

// Fatih Baskýn 150210710
module nand_gate(
                    input wire a,
                    input wire b,
                    output wire c);
    // Operation
    assign c = !(a&b);
endmodule

// Fatih Baskýn
module sr_latch_enable( 
                        input wire S,
                        input wire R,
                        input wire E,
                        output wire Q,
                        output wire Q_neg);
    // S NAND Enable
    wire s_nand;
    nand_gate s_enable(.a(S), .b(E), .c(s_nand));
    // R NAND
    wire r_nand;
    nand_gate r_enable(.a(R), .b(E), .c(r_nand));
    // NAND Q
    nand_gate for_q(.a(s_nand), .b(Q_neg), .c(Q));
    // NAND Q_comp
    nand_gate for_q_neg(.a(r_nand), .b(Q), .c(Q_neg));
endmodule

// Fatih Baskýn
module d_latch_enable(
                        input wire D,
                        input wire E,
                        output wire Q,
                        output wire Q_neg);
    // D complement
    wire D_neg;
    nand_gate d_complement(.a(D), .b(D), .c(D_neg));
    // D NAND Enable
    wire D_nand;
    nand_gate q_enable(.a(D), .b(E), .c(D_nand));
    // D_comp NAND Enable
    wire D_neg_nand;
    nand_gate q_neg_enable(.a(D_neg), .b(E), .c(D_neg_nand));
    // NAND Q
    nand_gate for_q(.a(D_nand), .b(Q_neg), .c(Q));
    // NAND Q_comp
    nand_gate for_q_neg(.a(D_neg_nand), .b(Q), .c(Q_neg));
endmodule

// Fatih Baskýn
module d_flip_flop_posedge(
                            input wire D,
                            input wire Clk,
                            output wire Q,
                            output wire Q_neg);
    // Clock wires
    wire Clk_neg;
    nand_gate clk_comp(.a(Clk), .b(Clk), .c(Clk_neg));
    wire Clk_neg_neg;
    nand_gate clk_comp_comp(.a(Clk_neg), .b(Clk_neg), .c(Clk_neg_neg));
    // D_latch_1
    wire Q_int;
    d_latch_enable d_1(.D(D), .E(Clk_neg), .Q(Q_int));
    // D_latch 2
    d_latch_enable d_2(.D(Q_int), .E(Clk_neg_neg), .Q(Q), .Q_neg(Q_neg));    
endmodule

// Fatih Baskýn
module sr_flip_flop_posedge(
                            input wire S,
                            input wire R,
                            input wire Clk,
                            output wire Q,
                            output wire Q_neg);
    // Clock wires
    wire Clk_neg;
    nand_gate clk_comp(.a(Clk), .b(Clk), .c(Clk_neg));
    wire Clk_neg_neg;
    nand_gate clk_comp_comp(.a(Clk_neg), .b(Clk_neg), .c(Clk_neg_neg));
    // SR Latch 1
    wire Q_int;
    wire Q_neg_int;
    sr_latch_enable sr_1(.S(S), .R(R), .E(Clk_neg), .Q(Q_int), .Q_neg(Q_neg_int));
    // SR Latch 2
    sr_latch_enable sr_2(.S(Q_int), .R(Q_neg_int), .E(Clk_neg_neg), .Q(Q), .Q_neg(Q_neg));
endmodule

// Fatih Baskýn 150210710
module jk_flip_flop_posedge(
                            input wire J,
                            input wire K,
                            input wire Clk,
                            output wire Q,
                            output wire Q_neg);
    // J and K
    wire K_comp;
    nand_gate K_complement(.a(K), .b(K), .c(K_comp));
    wire J_Q_neg;
    nand_gate J_nand_Q_neg(.a(J), .b(Q_neg), .c(J_Q_neg));
    wire K_comp_Q;
    nand_gate K_comp_nand_Q(.a(K_comp), .b(Q), .c(K_comp_Q));
    wire JK;
    nand_gate J_K(.a(J_Q_neg) , .b(K_comp_Q), .c(JK));
    wire JK_comp;
    nand_gate J_K_comp(.a(JK), .b(JK), .c(JK_comp));
    // Module
    sr_flip_flop_posedge JK_FF(.S(JK), .R(JK_comp), .Clk(Clk), .Q(Q), .Q_neg(Q_neg));
endmodule

// Elvan Teke 150190102
module not_gate(a, b);
    //Inputs
    input wire a;    
    //Outputs
    output wire b;    
    //Operations
    assign b = !a;
endmodule
module and_gate(a, b, c);
    //Inputs
    input wire a;
    input wire b;    
    //Outputs
    output wire c;
    //Operations
    assign c = a & b;     
endmodule
module or_gate(a, b, c);
    //inputs
    input wire a;
    input wire b;    
    //outputs
    output wire c;    
    //operations
    assign c = a | b;     
endmodule
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
module three_input_and_gate(a, b, c, d);
    //Inputs
    input wire a;
    input wire b;
    input wire c;    
    //Outputs
    output wire d;
    //Operations
    assign d = a & b & c;     
endmodule

module asynchronous_up_counter(
                               input wire Clk, 
                               input wire Set,
                               output wire [3:0] Q);                                  
    wire [3:0] Q_comp;
    wire J, J_comp;
    three_input_and_gate and_output(.a(Q[1]), .b(Q[2]), .c(Q[3]), .d(J_comp));
    not_gate not_0(.a(J_comp), .b(J));
    // JK 0
    wire jk_jin, jk_cin;
    mux_2to1 jk0_j(.i_0(J), .i_1(0), .s_0(Set), .o(jk_jin));
    jk_flip_flop_posedge jk_0(.J(jk_jin), .K(1), .Clk(Clk), .Q(Q[0]), .Q_neg(Q_comp[0]));
    wire Clk_1;
    mux_2to1 mux(.i_0(Q_comp[0]), .i_1(Clk), .s_0(J_comp), .o(Clk_1));
    // JK 1
    wire jk1_clk;
    mux_2to1 jk1(.i_0(Clk_1), .i_1(Clk), .s_0(Set), .o(jk1_clk));
    jk_flip_flop_posedge jk_1(.J(jk_jin), .K(1), .Clk(jk1_clk), .Q(Q[1]), .Q_neg(Q_comp[1]));
    // JK 2
    wire jk2_clk;
    mux_2to1 jk2(.i_0(Q_comp[1]), .i_1(Clk), .s_0(Set), .o(jk2_clk));    
    jk_flip_flop_posedge jk_2(.J(jk_jin), .K(1), .Clk(jk2_clk), .Q(Q[2]), .Q_neg(Q_comp[2]));
    // JK 3
    wire jk3_clk;
   mux_2to1 jk3(.i_0(Q_comp[2]), .i_1(Clk), .s_0(Set), .o(jk3_clk));
    jk_flip_flop_posedge jk_3(.J(jk_jin), .K(1), .Clk(jk3_clk), .Q(Q[3]), .Q_neg(Q_comp[3]));
endmodule

module synchronous_up_counter(
                               input wire Clk,
                               input wire Set, 
                               output wire [3:0] Q);
    // VCC and GRD
    supply1 const_1;
    supply0 const_0;
    
    wire [3:0] J;
    wire J_comp;
    // Reset at 14
    three_input_and_gate and_out(.a(Q[1]), .b(Q[2]), .c(Q[3]), .d(J_comp));
    not_gate not_0(.a(J_comp), .b(J[0]));
    // JK 0
    wire jk0_jin, jk0_kin; 
    mux_2to1 jk0_j(.i_0(J[0]), .i_1(const_0), .s_0(Set), .o(jk0_jin));
    mux_2to1 jk0_k(.i_0(J[0]), .i_1(const_1), .s_0(Set), .o(jk0_kin));
    jk_flip_flop_posedge jk0(.J(jk0_jin), .K(jk0_kin), .Clk(Clk), .Q(Q[0]), .Q_neg());
    wire [2:0] or_inp;
    // JK 1
    and_gate and_0(.a(Q[0]), .b(J[0]), .c(or_inp[0]));
    or_gate or_0(.a(or_inp[0]), .b(J_comp), .c(J[1]));
    wire jk1_jin, jk1_kin; 
    mux_2to1 jk1_j(.i_0(J[1]), .i_1(const_0), .s_0(Set), .o(jk1_jin));
    mux_2to1 jk1_k(.i_0(J[1]), .i_1(const_1), .s_0(Set), .o(jk1_kin));
    jk_flip_flop_posedge jk1(.J(jk1_jin), .K(jk1_kin), .Clk(Clk), .Q(Q[1]), .Q_neg());
    // JK 2
    and_gate and_1(.a(Q[1]), .b(J[1]), .c(or_inp[1]));
    or_gate or_1(.a(or_inp[1]), .b(J_comp), .c(J[2]));
    wire jk2_jin, jk2_kin; 
    mux_2to1 jk2_j(.i_0(J[2]), .i_1(const_0), .s_0(Set), .o(jk2_jin));
    mux_2to1 jk2_k(.i_0(J[2]), .i_1(const_1), .s_0(Set), .o(jk2_kin));
    jk_flip_flop_posedge jk2(.J(jk2_jin), .K(jk2_kin), .Clk(Clk), .Q(Q[2]), .Q_neg());
    // JK 3
    and_gate and_2(.a(Q[2]), .b(J[2]), .c(or_inp[2]));
    or_gate or_2(.a(or_inp[2]), .b(J_comp), .c(J[3]));
    wire jk3_jin, jk3_kin; 
    mux_2to1 jk3_j(.i_0(J[3]), .i_1(const_0), .s_0(Set), .o(jk3_jin));
    mux_2to1 jk3_k(.i_0(J[3]), .i_1(const_1), .s_0(Set), .o(jk3_kin));
    jk_flip_flop_posedge jk3(.J(jk3_jin), .K(jk3_kin), .Clk(Clk), .Q(Q[3]), .Q_neg());
endmodule

module part_7(
                               input wire [7:0] loaded, 
                               input wire Clk,
                               input wire load, 
                               output wire out);
                               
    reg [7:0] bits;
    always @(posedge Clk) begin
        if(load) begin
            bits <= loaded;
        end
        else begin
            bits [0] <= bits[7];
            bits [7] <= bits[6];
            bits [6] <= bits[5];
            bits [5] <= bits[4];
            bits [4] <= bits[3];
            bits [3] <= bits[2];
            bits [2] <= bits[1];
            bits [1] <= bits[0];
        end
    end
    assign out = bits[7];
endmodule