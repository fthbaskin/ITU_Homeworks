module mux_2to1_1bit(
    input wire s,
    input wire i0,
    input wire i1,
    output wire o
    );
    wire s_neg;
    assign s_neg = !s;
    wire i0_sel; // select i0
    assign i0_sel = s_neg & i0;
    wire i1_sel; // select i1
    assign i1_sel = s & i1;
    // final or
    assign o = i0_sel | i1_sel;
endmodule

module mux_2to1_8bit (s, i0, i1, o);
    input wire s;
    input wire [7:0]i0;
    input wire [7:0]i1;
    output wire [7:0]o;    
    generate
        genvar x;
        for(x = 0; x < 8; x = x + 1)
        begin: mux_2to1_8bit
            mux_2to1_1bit mux(.s(s), .i0(i0[x]), .i1(i1[x]), .o(o[x]));
        end
    endgenerate    
endmodule

module mux_4to1_8bit(
    input wire [1:0] s,
    input wire [7:0] i0,
    input wire [7:0] i1,
    input wire [7:0] i2,
    input wire [7:0] i3,
    output wire [7:0] o
    );
    // intermediate wires
    wire [7:0] k1;
    wire [7:0] k2;
    // level 1 MUXes
    mux_2to1_8bit MUX1_0(.s(s[0]), .i0(i0), .i1(i1), .o(k1));
    mux_2to1_8bit MUX1_1(.s(s[0]), .i0(i2), .i1(i3), .o(k2));
    // level 2 MUX
    mux_2to1_8bit MUX2_0(.s(s[1]), .i0(k1), .i1(k2), .o(o));
endmodule

module mux_2to1_16bit (s, i0, i1, o);
    input wire s;
    input wire [15:0]i0;
    input wire [15:0]i1;
    output wire [15:0]o;
    generate
        genvar x;
        for(x = 0; x < 16; x = x + 1)
        begin: mux_2to1_16bit
            mux_2to1_1bit mux(.s(s), .i0(i0[x]), .i1(i1[x]), .o(o[x]));
        end
    endgenerate
endmodule

module mux_4to1_16bit(
    input wire [1:0] s,
    input wire [15:0] i0,
    input wire [15:0] i1,
    input wire [15:0] i2,
    input wire [15:0] i3,
    output wire [15:0] o
    );
    // intermediate wires
    wire [15:0] k1;
    wire [15:0] k2;
    // level 1 MUXes
    mux_2to1_16bit MUX1_0(.s(s[0]), .i0(i0), .i1(i1), .o(k1));
    mux_2to1_16bit MUX1_1(.s(s[0]), .i0(i2), .i1(i3), .o(k2));
    // level 2 MUX
    mux_2to1_16bit MUX2_0(.s(s[1]), .i0(k1), .i1(k2), .o(o));
endmodule

module mux_16to1_8bit(
    input wire [7:0] i0,
    input wire [7:0] i1,
    input wire [7:0] i2,
    input wire [7:0] i3,
    input wire [7:0] i4,
    input wire [7:0] i5,
    input wire [7:0] i6,
    input wire [7:0] i7,
    input wire [7:0] i8,
    input wire [7:0] i9,
    input wire [7:0] i10,
    input wire [7:0] i11,
    input wire [7:0] i12,
    input wire [7:0] i13,
    input wire [7:0] i14,
    input wire [7:0] i15,
    input wire [3:0] s,
    output wire [7:0] o);
    // Level 1 MUXes
    wire [7:0] mux1;
    wire [7:0] mux2;
    wire [7:0] mux3;
    wire [7:0] mux4;
    mux_4to1_8bit M1(.i0(i0), .i1(i1), .i2(i2),
                     .i3(i3), .s(s[1:0]), .o(mux1));
    mux_4to1_8bit M2(.i0(i4), .i1(i5), .i2(i6),
                     .i3(i7), .s(s[1:0]), .o(mux2));
    mux_4to1_8bit M3(.i0(i8), .i1(i9), .i2(i10),
                     .i3(i11), .s(s[1:0]), .o(mux3));  
    mux_4to1_8bit M4(.i0(i12), .i1(i13), .i2(i14),
                     .i3(i15), .s(s[1:0]), .o(mux4));
    // Level 2 MUX
    mux_4to1_8bit M5(.i0(mux1), .i1(mux2), .i2(mux3),
                     .i3(mux4), .s(s[3:2]), .o(o));
endmodule

module mux_16to1_1bit(
    input wire [15:0]i,
    input wire [3:0] s,
    output wire o);
    //Level 1 MUXes:
    wire [7:0] level_1;
    generate
        genvar x;
        for (x = 0; x < 8; x = x + 1)
        begin:L1
            mux_2to1_1bit mux(.i0(i[x + x]), .i1(i[x + x + 1]), 
            .s(s[0]), .o(level_1[x]));
        end
    endgenerate
    // Level 2 MUXes:
    wire [3:0] level_2;
    generate
        genvar y;
        for (y = 0; y < 4; y = y + 1)
        begin:L2
            mux_2to1_1bit mux(.i0(level_1[y + y]),
            .i1(level_1[y + y + 1]), .s(s[1]), .o(level_2[y]));
        end
    endgenerate
    // Level 3 MUXes:
    wire [1:0] level_3;
    generate
        genvar z;
        for (z = 0; z < 2; z = z + 1)
        begin:L3
            mux_2to1_1bit mux(.i0(level_2[z + z]),
            .i1(level_2[z + z + 1]), .s(s[2]), .o(level_3[z]));
        end
    endgenerate
    // Level 4 MUX:
    mux_2to1_1bit L4(.i0(level_3[0]), .i1(level_3[1]), .s(s[3]), .o(o));    
endmodule

module reg_8bit (D, clk, reset, enable, Q);
    input wire [7:0] D; // Data input
    input wire clk,reset,enable;
    output reg [7:0] Q; // output Q
    always @(posedge clk or posedge reset)
    begin
        if(reset)
            Q <= 8'd0;
        else if (enable)
            Q <= D;
    end
endmodule

module reg_16bit (D, clk, reset, enable, Q);
    input wire [15:0] D; // Data input
    input wire clk,reset,enable;
    output reg [15:0] Q; // output Q
    always @(posedge clk or posedge reset)
    begin
        if(reset)
            Q <= 16'd0;
        else if (enable)
            Q <= D;
    end
endmodule

module reg_1bit(D, clk, enable, Q);
    input wire D, clk, enable;
    output reg Q;
    always @(posedge clk)
    begin
        if (enable)
            Q <= D;
    end            
endmodule

module part_1_8bit(I, Clk, E, FunSel, Q);
    input wire [7:0] I;
    input wire Clk;
    input wire E;
    input wire [1:0] FunSel;
    output wire [7:0] Q;
    // Reset
    wire reset;
    assign reset = E & FunSel[1] & FunSel[0];
    // Register
    wire [7:0] mux_to_reg;
    reg_8bit register(.D(mux_to_reg), .clk(Clk), .enable(E), .reset(reset), .Q(Q));
    // Multiplexer
    wire [7:0] mux_i0;
    assign mux_i0[7:0] = Q[7:0] - 8'd1; // Decrement
    wire [7:0] mux_i1;
    assign mux_i1[7:0] = Q[7:0] + 8'd1; // Increment
    wire [7:0] mux_i3;
    assign mux_i3 = 8'd0; // Load 0
    mux_4to1_8bit mux(.i0(mux_i0), .i1(mux_i1), .i2(I), 
                      .i3(mux_i3), .s(FunSel) ,.o(mux_to_reg));    
endmodule

module part_1_16bit(I, Clk, E, FunSel, Q);
    input wire [15:0] I;
    input wire Clk;
    input wire E;
    input wire [1:0] FunSel;
    output wire [15:0] Q;
    // Reset
    wire reset;
    assign reset = E & FunSel[1] & FunSel[0];
    // Register
    wire [15:0] mux_to_reg;
    reg_16bit register(.D(mux_to_reg), .clk(Clk), .enable(E), .reset(reset), .Q(Q));
    // Multiplexer
    wire [15:0] mux_i0;
    assign mux_i0[15:0] = Q[15:0] - 8'd1; // Decrement
    wire [15:0] mux_i1;
    assign mux_i1[15:0] = Q[15:0] + 8'd1; // Increment
    wire [15:0] mux_i3;
    assign mux_i3 = 8'd0; // Load 0
    mux_4to1_16bit mux(.i0(mux_i0), .i1(mux_i1), .i2(I), 
                      .i3(mux_i3), .s(FunSel) ,.o(mux_to_reg));    
endmodule

module part_2a(
    I,
    Clk,
    OutASel,
    OutBSel,
    OutA,
    OutB,
    FunSel,
    RegSel);
    // Data input
    input wire [7:0] I;
    // Register outputs
    wire [7:0] reg_1;
    wire [7:0] reg_2;
    wire [7:0] reg_3;
    wire [7:0] reg_4;
    // Clock
    input wire Clk;
    // OutA
    input wire [1:0] OutASel;
    output wire [7:0] OutA;
    mux_4to1_8bit outA(.i0(reg_1), .i1(reg_2), .i2(reg_3),
                       .i3(reg_4), .s(OutASel), .o(OutA));
    // OutB
    input wire [1:0] OutBSel;
    output wire [7:0] OutB;
    mux_4to1_8bit outB(.i0(reg_1), .i1(reg_2), .i2(reg_3),
                       .i3(reg_4), .s(OutBSel), .o(OutB));
    // FunSel
    input wire [1:0] FunSel;
    // RegSel
    input wire [3:0] RegSel;
    wire select_R1;
    assign select_R1 = !RegSel[3];
    wire select_R2;
    assign select_R2 = !RegSel[2];
    wire select_R3;
    assign select_R3 = !RegSel[1];
    wire select_R4;
    assign select_R4 = !RegSel[0];
    // Registers
    part_1_8bit R1(.E(select_R1), .Q(reg_1),
                   .FunSel(FunSel), .Clk(Clk), .I(I));
    part_1_8bit R2(.E(select_R2), .Q(reg_2),
                   .FunSel(FunSel), .Clk(Clk), .I(I));
    part_1_8bit R3(.E(select_R3), .Q(reg_3),
                   .FunSel(FunSel), .Clk(Clk), .I(I));
    part_1_8bit R4(.E(select_R4), .Q(reg_4),
                   .FunSel(FunSel), .Clk(Clk), .I(I));   
endmodule

module part_2b(
    I,
    Clk,
    OutCSel,
    OutDSel,
    OutC,
    OutD,
    FunSel,
    RegSel);
    // Data input
    input wire [7:0] I;
    // Register outputs
    wire [7:0] pc;
    wire [7:0] ar;
    wire [7:0] sp;
    // Clock
    input wire Clk;
    // OutC
    input wire [1:0] OutCSel;
    output wire [7:0] OutC;
    mux_4to1_8bit outC(.i0(pc), .i1(pc), .i2(ar),
                       .i3(sp), .s(OutCSel), .o(OutC));
    // OutD
    input wire [1:0] OutDSel;
    output wire [7:0] OutD;
    mux_4to1_8bit outD(.i0(pc), .i1(pc), .i2(ar),
                       .i3(sp), .s(OutDSel), .o(OutD));
    // FunSel
    input wire [1:0] FunSel;
    // RegSel
    input wire [2:0] RegSel;
    wire select_PC;
    assign select_PC = !RegSel[2];
    wire select_AR;
    assign select_AR = !RegSel[1];
    wire select_SP;
    assign select_SP = !RegSel[0];
    // Registers
    part_1_8bit PC(.E(select_PC), .Q(pc),
                   .FunSel(FunSel), .Clk(Clk), .I(I));
    part_1_8bit AR(.E(select_AR), .Q(ar),
                   .FunSel(FunSel), .Clk(Clk), .I(I));
    part_1_8bit SP(.E(select_SP), .Q(sp),
                   .FunSel(FunSel), .Clk(Clk), .I(I));
endmodule

module part_2c(
    I,
    LH,
    Enable,
    Clk,
    FunSel,
    IRout);
    // Data input
    input wire [7:0] I;
    // Low High
    input wire LH;
    wire [15:0] ir_data;
    mux_2to1_8bit low(.i0(I), .i1(IRout[7:0]), .o(ir_data[7:0]), .s(LH));
    mux_2to1_8bit high(.i0(IRout[15:8]), .i1(I), .o(ir_data[15:8]), .s(LH));
    // Enable
    input wire Enable;
    // FunSel
    input wire [1:0] FunSel;
    // Output
    output wire [15:0] IRout;
    // Register
    input wire Clk;
    part_1_16bit IR(.Clk(Clk), .E(Enable), .Q(IRout),
                    .FunSel(FunSel), .I(ir_data));    
endmodule

module full_adder(
    input wire A, 
    input wire B,
    input wire Cin,
    output wire Cout,
    output wire Out);
    // Out
    wire AxorB;
    assign AxorB = A ^ B;
    assign Out = AxorB ^ Cin;
    // Cout
    wire AxorB_and_Cin;
    wire AandB;
    assign AandB = A & B;
    assign AxorB_and_Cin = AxorB & Cin;
    assign Cout = AandB | AxorB_and_Cin;
endmodule

module RPA_8bit(
    input wire [7:0] A,
    input wire [7:0] B,
    input wire Cin,
    output wire Cout,
    output wire [7:0] Out);
    wire [8:0]int_carry;
    assign int_carry[0] = Cin;
    generate
        genvar x;
        for (x = 0; x < 8; x = x +1)
        begin: RPA
            full_adder RPA(.A(A[x]), .B(B[x]), .Out(Out[x]),
            .Cin(int_carry[x]), .Cout(int_carry[x+1])); 
        end       
    endgenerate
    assign Cout = int_carry[8];
endmodule

module not_8bit(
    input wire [7:0] A,
    output wire [7:0] B);
    generate
        genvar x;
        for (x = 0; x < 8; x = x + 1)
        begin: NOT
            assign B[x] = !A[x];
        end    
    endgenerate
endmodule

module and_8bit(
    input wire [7:0] A,
    input wire [7:0] B,
    output wire [7:0] C);
    generate
        genvar x;
        for (x = 0; x < 8; x = x + 1)
        begin: AND
            assign C[x] = A[x] & B[x];
        end    
    endgenerate
endmodule

module or_8bit(
    input wire [7:0] A,
    input wire [7:0] B,
    output wire [7:0] C);
    generate
        genvar x;
        for (x = 0; x < 8; x = x + 1)
        begin: AND
            assign C[x] = A[x] | B[x];
        end    
    endgenerate
endmodule

module xor_8bit(
    input wire [7:0] A,
    input wire [7:0] B,
    output wire [7:0] C);
    generate
        genvar x;
        for (x = 0; x < 8; x = x + 1)
        begin: AND
            assign C[x] = A[x] ^ B[x];
        end    
    endgenerate
endmodule

module zero_check(
    input wire [7:0] A,
    output wire B);
    wire [7:0] int;
    assign int[0] = A[0];
    generate
        genvar x;
        for (x = 1; x < 8; x = x + 1)
        begin: OR
            assign int[x] = int[x - 1] | A[x];        
        end
    endgenerate
    assign B = !int[7];
endmodule

module dec_4to16(
    input wire [3:0] I,
    output reg [15:0] O);
    always @(*)
            case(I)
            4'h0: begin O = 16'h0001; end
            4'h1: begin O = 16'h0002; end
            4'h2: begin O = 16'h0004; end
            4'h3: begin O = 16'h0008; end
            4'h4: begin O = 16'h0010; end
            4'h5: begin O = 16'h0020; end
            4'h6: begin O = 16'h0040; end
            4'h7: begin O = 16'h0080; end   
            4'h8: begin O = 16'h0100; end
            4'h9: begin O = 16'h0200; end
            4'ha: begin O = 16'h0400; end
            4'hb: begin O = 16'h0800; end
            4'hc: begin O = 16'h1000; end
            4'hd: begin O = 16'h2000; end
            4'he: begin O = 16'h4000; end
            4'hf: begin O = 16'h8000; end                                  
            default: begin O = 16'h0000; end            
        endcase      
endmodule

module dec_16bit_or(
    input wire [15:0] A,
    output wire B);
    wire [15:0] int;
    assign int[0] = A[0];
    generate
        genvar x;
        for (x = 0; x < 16; x = x + 1)
        begin: OR
           assign int[x] = int[x - 1] | A[x];
        end
    endgenerate
    assign B = int[15];
endmodule

module ALU(
    input wire [7:0] A,
    input wire [7:0] B,
    input wire [3:0] FunSel,
    output wire [7:0] OutALU,
    output wire [3:0] zcno,
    input wire Clk);
    // Decode FunSel
    wire [15:0] inst;
    dec_4to16 instruction_decoder(.I(FunSel), .O(inst));
    // A B complement
    wire [7:0] A_neg;
    wire [7:0] B_neg;
    not_8bit a_neg(.A(A), .B(A_neg));
    not_8bit b_neg(.A(B), .B(B_neg));
    // Adder
    wire [7:0] RPAout, RPA_A, RPA_B;
    mux_4to1_8bit rpa_a(.o(RPA_A), .s(FunSel[1:0]), 
    .i0(A), .i1(A), .i2(A));
    mux_4to1_8bit rpa_b(.o(RPA_B), .s(FunSel[1:0]), 
    .i0(B), .i1(B), .i2(B_neg));
    wire cin;
    wire cout;
    assign cin = inst[6] | (inst[5] & zcno[2]);
    RPA_8bit adder(.Out(RPAout), .A(RPA_A), .B(RPA_B),
    .Cin(cin), .Cout(cout));
    // Logic Operations
    wire [7:0] AandB, AorB, AxorB; 
    and_8bit a_and_b(.A(A), .B(B), .C(AandB));
    or_8bit a_or_b(.A(A), .B(B), .C(AorB));
    xor_8bit a_xor_b(.A(A), .B(B), .C(AxorB));
    // Zero Flag
    wire zc;
    zero_check zero_flag(.A(OutALU), .B(zc));
    reg_1bit Z(.clk(Clk), .Q(zcno[3]),
    .enable(1), .D(zc));
    // Carry Flag
    wire carry_flag_enable;
    wire [15:0] cfo;
    assign cfo[4] = inst[4], cfo[5] = inst[5], cfo[6] = inst[6],
    cfo[10] = inst[10], cfo[11] = inst[11], cfo[14] = inst[14], cfo[15] = inst[15];
    dec_16bit_or carry_en(.A(cfo), .B(carry_flag_enable));
    wire carry_flag_input;
    wire [15:0] carry_flag_input_mux;
    assign carry_flag_input_mux[4] = cout, 
    carry_flag_input_mux[5] = cout, carry_flag_input_mux[6] = cout,
    carry_flag_input_mux[10] = A[7], carry_flag_input_mux[11] = A[0], 
    carry_flag_input_mux[14] = A[7], carry_flag_input_mux[15] = A[0];
    mux_16to1_1bit carry_flag_input_MUX(.i(carry_flag_input_mux), 
    .o(carry_flag_input), .s(FunSel));
    reg_1bit C(.clk(Clk), .Q(zcno[2]), .enable(carry_flag_enable), .D(carry_flag_input));
    // Negative Flag
    wire neg_flag_enable = !inst[13];    
    reg_1bit N(.clk(Clk), .Q(zcno[1]),
    .enable(neg_flag_enable), .D(OutALU[7]));   
    // Overflow Flag
    wire ls_overflow = (A[7] ^ A[6]) & (inst[12] | inst[14]);
    wire rs_overflow = (A[7] ^ zcno[2]) & inst[15];
    wire add_overflow = ((A[7] & B[7] & !RPAout[7]) | (!A[7] & !B[7] & RPAout[7]))
    & (inst[4]| inst[5]);
    wire sub_overflow = ((!A[7] & B[7] & RPAout[7]) | (A[7] & !B[7] & !RPAout[7]))
    & inst[6];    
    wire overflow_flag = rs_overflow | ls_overflow | add_overflow | sub_overflow;        
    wire ovf_enable;
    wire [15:0] ofe;
    assign ofe[4] = inst[4], ofe[5] = inst[5], ofe[6] = inst[6],
    ofe[12] = inst[12], ofe[14] = inst[14], ofe[15] = inst[15];
    dec_16bit_or ovf_en(.A(ofe), .B(ovf_enable));
    reg_1bit O(.D(overflow_flag), .enable(ovf_enable), .clk(Clk), .Q(zcno[0]));
    // Logic and Circular Shifts
    wire [7:0] lsl;
    assign lsl[0] = 0, lsl[1] = A[0], lsl[2] = A[1], lsl[3] = A[2],
    lsl[4] = A[3], lsl[5] = A[4], lsl[6] = A[5], lsl[7] = A[6];
    wire [7:0] lsr;
    assign lsr[0] = A[1], lsr[1] = A[2], lsr[2] = A[3], lsr[3] = A[4],
    lsr[4] = A[5], lsr[5] = A[6], lsr[6] = A[7], lsr[7] = 0;
    wire [7:0] csl;
    assign csl[0] = zcno[2], csl[1] = A[0], csl[2] = A[1], csl[3] = A[2],
    csl[4] = A[3], csl[5] = A[4], csl[6] = A[5], csl[7] = A[6];
    wire [7:0] csr;
    assign csr[0] = A[1], csr[1] = A[2], csr[2] = A[3], csr[3] = A[4],
    csr[4] = A[5], csr[5] = A[6], csr[6] = A[7], csr[7] = zcno[2];
    // Arithmetic Shift
    wire [7:0] asl;
    assign asl[7] = A[6], asl[6] = A[5], asl[5] = A[4], asl[4] = A[3],
    asl[3] = A[2], asl[2] = A[1], asl[1] = A[0], asl[0] = 0;
    wire [7:0] asr;
    assign asr[7]= A[7], asr[6]= A[7], asr[5]= A[6], asr[4]= A[5],
    asr[3]= A[4], asr[2]= A[3], asr[1]= A[2], asr[0]= A[1];
    // ALU MUX
    mux_16to1_8bit  ALU(.s(FunSel), .o(OutALU),
    .i0(A), .i1(B), .i2(A_neg), .i3(B_neg), .i4(RPAout),
    .i5(RPAout), .i6(RPAout), .i7(AandB), .i8(AorB),
    .i9(AxorB), .i10(lsl), .i11(lsr), .i12(asl),
    .i13(asr), .i14(csl), .i15(csr));    
endmodule

module ALUSystem(
    input wire [1:0] RF_OutASel,
    input wire [1:0] RF_OutBSel,
    input wire [1:0] RF_FunSel,
    input wire [3:0] RF_RegSel,
    input wire [3:0] ALU_FunSel,
    input wire [1:0] ARF_OutCSel,
    input wire [1:0] ARF_OutDSel,
    input wire [1:0] ARF_FunSel,
    input wire [2:0] ARF_RegSel,
    input wire IR_LH,
    input wire IR_Enable,
    input wire [1:0] IR_Funsel,
    input wire Mem_WR,
    input wire Mem_CS,
    input wire [1:0] MuxASel,
    input wire [1:0] MuxBSel,
    input wire MuxCSel,
    input wire Clock);
    // Wires
    wire [7:0] ALUOut;    
    // Mux Outputs
    wire [7:0] MuxAOut;
    wire [7:0] MuxBOut;
    wire [7:0] MuxCOut;    
    // IR
    wire [7:0] MemoryOut; 
    wire [7:0] IROut;   
    part_2c IR(.I(MemoryOut), .IRout(IROut), .Clk(Clock),
    .Enable(IR_Enable), .LH(IR_LH), .FunSel(IR_Funsel));
    // MUXB
    mux_4to1_8bit MUXB(.i1(IROut), .i2(MemoryOut),
    .i3(ALUOut), .o(MuxBOut), .s(MuxBSel));
    // ARF
    wire [7:0] Address;
    wire [7:0] ARF_COut;
    part_2b ARF(.Clk(Clock), .OutD(Address), .OutC(ARF_COut), .I(MuxBOut), .OutCSel(ARF_OutCSel),
    .OutDSel(ARF_OutDSel), .RegSel(ARF_RegSel), .FunSel(ARF_FunSel));
    // Memory
    Memory MEM(.address(Address), .clock(Clock), .o(MemoryOut),
    .data(ALUOut), .wr(Mem_WR), .cs(Mem_CS));
    // MUXA
    mux_4to1_8bit MUXA(.i0(IROut), .i1(MemoryOut), .i2(ARF_COut), 
    .i3(ALUOut), .s(MuxASel), .o(MuxAOut));
    // RF
    wire [7:0] AOut;
    wire [7:0] BOut;
    part_2a RF(.OutA(AOut), .OutB(BOut), .I(MuxAOut), .Clk(Clock),
    .FunSel(RF_FunSel), .OutASel(RF_OutASel), .OutBSel(RF_OutBSel), .RegSel(RF_RegSel));
    // MUXC
    mux_2to1_8bit MUXC(.i0(ARF_COut), .i1(AOut), .s(MuxCSel), .o(MuxCOut));
    //ALU
    wire [3:0] ALUOutFlag;
    ALU ALU(.A(MuxCOut), .B(BOut), .FunSel(ALU_FunSel), .Clk(Clock),
    .OutALU(ALUOut), .zcno(ALUOutFlag));    
endmodule