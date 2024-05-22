// Group 62
// Fatih Baskın 150210710
`timescale 1ns / 1ps

module part_1_8bit_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end    
    // Inputs
    reg [7:0] I;
    reg [1:0] FunSel;
    reg E;
    // Output
    wire [7:0] Q;
    //Module
    part_1_8bit uut(.I(I), .Clk(Clk), .FunSel(FunSel), .E(E), .Q(Q));
    initial begin
        E = 1; I = 8'hff;
        FunSel = 2'b11; #25;
        FunSel = 2'b01; #120;
        FunSel = 2'b00; #80;
        FunSel = 2'b10; #20;
        FunSel = 2'b01; #20;
        FunSel = 2'b00; #80;
        FunSel = 2'b11; #20;
        E = 0; #20;
        FunSel = 2'b00; #20;
        FunSel = 2'b01; #20;
        FunSel = 2'b10; #20;
        FunSel = 2'b11; #20;
    end
endmodule

module part_1_16bit_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end    
    // Inputs
    reg [15:0] I;
    reg [1:0] FunSel;
    reg E;
    // Output
    wire [15:0] Q;
    //Module
    part_1_16bit uut(.I(I), .Clk(Clk), .FunSel(FunSel), .E(E), .Q(Q));
    initial begin
        E = 1; I = 16'hffff;
        FunSel = 2'b11; #25;
        FunSel = 2'b01; #120;
        FunSel = 2'b00; #80;
        FunSel = 2'b10; #20;
        FunSel = 2'b01; #20;
        FunSel = 2'b00; #80;
        FunSel = 2'b11; #20;
        E = 0; #20;
        FunSel = 2'b00; #20;
        FunSel = 2'b01; #20;
        FunSel = 2'b10; #20;
        FunSel = 2'b11; #20;
    end
endmodule

module part_2a_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg [7:0] I;
    reg [1:0] OutASel;
    reg [1:0] OutBSel;
    reg [1:0] FunSel;
    reg [3:0] RegSel;
    // Outputs
    wire [7:0] OutA;
    wire [7:0] OutB;
    // Unit
    part_2a uut(.Clk(Clk), .I(I), .OutASel(OutASel),
                .OutBSel(OutBSel), .FunSel(FunSel),
                .RegSel(RegSel), .OutA(OutA), .OutB(OutB));
    // Test
    initial begin
    // Clear Test
    RegSel = 4'b0000; FunSel= 2'b11; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #25;
    RegSel = 4'b1111; FunSel= 2'b10; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    // Increment Test
    RegSel = 4'b0111; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b0011; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b0001; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b0000; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b01; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    //Decrement Test
    RegSel = 4'b0111; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b0011; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b0001; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b0000; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b00; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    // Load Test
    RegSel = 4'b0111; FunSel= 2'b10; I = 8'hAA;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b10; I = 8'hAA;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b1011; FunSel= 2'b10; I = 8'hBB;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b10; I = 8'hBB;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b1101; FunSel= 2'b10; I = 8'hCC;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b10; I = 8'hCC;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    RegSel = 4'b1110; FunSel= 2'b10; I = 8'hDD;
    OutASel = 2'b00; OutBSel = 2'b01; #20;
    RegSel = 4'b1111; FunSel= 2'b10; I = 8'hDD;
    OutASel = 2'b10; OutBSel = 2'b11; #20;
    end
endmodule

module part_2b_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg [7:0] I;
    reg [1:0] OutCSel;
    reg [1:0] OutDSel;
    reg [1:0] FunSel;
    reg [2:0] RegSel;
    // Outputs
    wire [7:0] OutC;
    wire [7:0] OutD;
    // Unit
    part_2b uut(.Clk(Clk), .I(I), .OutCSel(OutCSel),
                .OutDSel(OutDSel), .FunSel(FunSel),
                .RegSel(RegSel), .OutC(OutC), .OutD(OutD));
    // Test
    initial begin
    // Clear Test
    RegSel = 3'b000; FunSel= 2'b11; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #25;
    RegSel = 3'b111; FunSel= 2'b10; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    // Increment Test
    RegSel = 3'b011; FunSel= 2'b01; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b01; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    RegSel = 3'b001; FunSel= 2'b01; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b01; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    RegSel = 3'b000; FunSel= 2'b01; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b01; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    // Decrement Test
    RegSel = 3'b011; FunSel= 2'b00; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b00; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    RegSel = 3'b001; FunSel= 2'b00; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b00; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    RegSel = 3'b000; FunSel= 2'b00; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b00; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    // Load Test
    RegSel = 3'b011; FunSel= 2'b10; I = 8'hAA;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b10; I = 8'hAA;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    RegSel = 3'b101; FunSel= 2'b10; I = 8'hBB;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b10; I = 8'hBB;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;
    RegSel = 3'b110; FunSel= 2'b10; I = 8'hCC;
    OutCSel = 2'b00; OutDSel = 2'b01; #20;
    RegSel = 3'b111; FunSel= 2'b10; I = 8'hCC;
    OutCSel = 2'b10; OutDSel = 2'b11; #20;         
    end
endmodule

module part_2c_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg [7:0] I;
    reg LH;
    reg E;
    reg [1:0] FunSel;
    // Output
    wire [15:0] IRout;
    // Unit
    part_2c uut(.Clk(Clk), .I(I), .LH(LH),
                .Enable(E), .FunSel(FunSel), .IRout(IRout));
    // Test
    initial begin
        // Clear Test
        E = 1; LH = 0; I = 8'haa;
        FunSel = 2'b11; #25;
        // Increment Test
        E = 1; LH = 0; I = 8'haa;
        FunSel = 2'b01; #20;  
        // Decrement Test
        E = 1; LH = 0; I = 8'haa;
        FunSel = 2'b00; #20;  
        // LSB Load Test
        E = 1; LH = 0; I = 8'haa;
        FunSel = 2'b10; #20;
        // MSB Load Test  
        E = 1; LH = 1; I = 8'hbb;
        FunSel = 2'b10; #20;    
        // Enable  
        E = 0; LH = 1; I = 8'hbb;
        FunSel = 2'b11; #20;   
        E = 1; LH = 1; I = 8'hbb;
        FunSel = 2'b11; #20;        
    end    
endmodule

module alu_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg [7:0] A, B;
    reg [3:0] FunSel;
    wire [7:0] OutALU;
    wire [3:0] zcno;
    // Unit
    ALU uut(.A(A), .B(B), .OutALU(OutALU), .Clk(Clk), .FunSel(FunSel), .zcno(zcno));
    // Test
    initial begin
        A = 8'haa; B = 8'hbb;
        FunSel = 4'h0; #10; FunSel = 4'h1; #20;
        FunSel = 4'h2; #20; FunSel = 4'h3; #20;
        FunSel = 4'h4; #20; FunSel = 4'h5; #20;
        FunSel = 4'h6; #20; FunSel = 4'h7; #20;
        FunSel = 4'h8; #20; FunSel = 4'h9; #20;
        FunSel = 4'ha; #20; FunSel = 4'hb; #20;
        FunSel = 4'hc; #20; FunSel = 4'hd; #20;
        FunSel = 4'he; #20; FunSel = 4'hf; #20;
    end
endmodule

module alu_sim2();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg [7:0] A, B;
    reg [3:0] FunSel;
    wire [7:0] OutALU;
    wire [3:0] zcno;
    // Unit
    ALU uut(.A(A), .B(B), .OutALU(OutALU), .Clk(Clk), .FunSel(FunSel), .zcno(zcno));
    // Test
    initial begin
        FunSel = 4'h4; A = 8'hff; B = 8'h01; #10;
        FunSel = 4'h5;
    end
endmodule

module control_unit_sim_h0_h1();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'h0000; #60;
    IR = 16'h1000; #60;
    IR = 16'h1100; #60;
    IR = 16'h1200; #60;
    IR = 16'h1300; #60;
    IR = 16'h1400; #60;
    IR = 16'h1500; #60;
    IR = 16'h1600; #60;
    IR = 16'h1700; #60;
    end            
endmodule

module control_unit_sim_h2_h3();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'h2000; #60;
    IR = 16'h2100; #60;
    IR = 16'h2200; #60;
    IR = 16'h2300; #60;
    IR = 16'h3040; #60;
    IR = 16'h3140; #60;
    IR = 16'h3240; #60;
    IR = 16'h3340; #60;
    IR = 16'h3400; #60;
    IR = 16'h3500; #60;
    IR = 16'h3600; #60;
    IR = 16'h3700; #60;
    end            
endmodule

module control_unit_sim_h3_h4();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'h3700; #60;
    IR = 16'h3710; #60;
    IR = 16'h3720; #60;
    IR = 16'h3730; #60;
    IR = 16'h3740; #60;
    IR = 16'h3750; #60;
    IR = 16'h3760; #60;
    IR = 16'h3770; #60;
    IR = 16'h3040; #60;
    IR = 16'h3050; #60;
    IR = 16'h3060; #60;
    IR = 16'h3070; #60;
    IR = 16'h4004; #60;
    IR = 16'h4005; #60;
    IR = 16'h4006; #60;
    IR = 16'h4007; #60;
    end            
endmodule

module control_unit_sim_h4();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'h4004; #60;
    IR = 16'h4014; #60;
    IR = 16'h4024; #60;
    IR = 16'h4034; #60;
    IR = 16'h4044; #60;
    IR = 16'h4054; #60;
    IR = 16'h4064; #60;
    IR = 16'h4074; #60;
    IR = 16'h4004; #60;
    IR = 16'h4104; #60;
    IR = 16'h4204; #60;
    IR = 16'h4304; #60;
    IR = 16'h4404; #60;
    IR = 16'h4504; #60;
    IR = 16'h4604; #60;
    IR = 16'h4704; #60;
    end            
endmodule

module control_unit_sim_h4_h5_h7_h6();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'h4004; #60;
    IR = 16'h5004; #60;
    IR = 16'h7004; #60;
    IR = 16'h6000; #60;
    IR = 16'h6100; #60;
    IR = 16'h6200; #60;
    IR = 16'h6300; #60;
    IR = 16'h6400; #60;
    IR = 16'h6500; #60;
    IR = 16'h6600; #60;
    IR = 16'h6700; #60;
    IR = 16'h6000; #60;
    IR = 16'h6010; #60;
    IR = 16'h6020; #60;
    IR = 16'h6030; #60;
    end            
endmodule

module control_unit_sim_h6_h9_ha();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'h6040; #60;
    IR = 16'h6050; #60;
    IR = 16'h6060; #60;
    IR = 16'h6070; #60;
    IR = 16'h9000; #60;
    IR = 16'ha000; #60;
    end            
endmodule

module control_unit_sim_hb_hc();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'hb000; #60;
    IR = 16'hb100; #60;
    IR = 16'hb200; #60;
    IR = 16'hb300; #60;
    IR = 16'hc000; #60;
    IR = 16'hc100; #60;
    IR = 16'hc200; #60;
    IR = 16'hc300; #60;
    end            
endmodule

module control_unit_sim_hd_he();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'hd040; #80;
    IR = 16'hd150; #80;
    IR = 16'hd260; #80;
    IR = 16'hd370; #80;
    IR = 16'hd400; #80;
    IR = 16'hd510; #80;
    IR = 16'hd620; #80;
    IR = 16'hd730; #80;
    IR = 16'hd740; #80;
    IR = 16'hd760; #80;
    IR = 16'hd770; #80;
    IR = 16'he000; #80;
    end            
endmodule

module control_unit_sim_hf();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'hf000; 
    ZCNO = 4'h0; #60;    
    ZCNO = 4'h1; #60;
    ZCNO = 4'h2; #60;
    ZCNO = 4'h3; #60;
    ZCNO = 4'h4; #60;
    ZCNO = 4'h5; #60;
    ZCNO = 4'h6; #60;
    ZCNO = 4'h7; #60;
    ZCNO = 4'h8; #60;
    ZCNO = 4'h9; #60;
    ZCNO = 4'ha; #60;
    ZCNO = 4'hb; #60;
    ZCNO = 4'hc; #60;
    ZCNO = 4'hd; #60;
    ZCNO = 4'he; #60;
    ZCNO = 4'hf; #60;
    end            
endmodule

module control_unit_sim_h8();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Inputs
    reg Res;
    reg [15:0] IR;
    reg [3:0] ZCNO;
    // Outputs
    wire [3:0] seq;
    wire [3:0] RF_RegSel;
    wire [2:0] ARF_RegSel;
    wire IR_Enable;
    wire Mem_CS;
    wire Mem_WR;
    wire IR_LH;
    wire [1:0] IR_Funsel;
    wire [1:0] ARF_FunSel;
    wire [1:0] RF_FunSel;
    wire [1:0] RF_OutASel;
    wire [1:0] RF_OutBSel;
    wire [1:0] ARF_OutCSel;
    wire [1:0] ARF_OutDSel;
    wire [1:0] MuxASel;
    wire [1:0] MuxBSel;
    wire MuxCSel;
    wire [3:0] ALU_FunSel;
    // Unit
    control_unit uut(.clock(Clk), .seq(seq), .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
                     .reset(Res), .IR(IR), .ZCNO(ZCNO), .IR_LH(IR_LH), .MuxCSel(MuxCSel),
                     .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .ARF_OutCSel(ARF_OutCSel),
                     .ARF_OutDSel(ARF_OutDSel), .MuxBSel(MuxBSel), .MuxASel(MuxASel),
                     .RF_RegSel(RF_RegSel), .ARF_RegSel(ARF_RegSel), .IR_Enable(IR_Enable),
                     .IR_Funsel(IR_Funsel), .ARF_FunSel(ARF_FunSel), .RF_FunSel(RF_FunSel), .ALU_FunSel(ALU_FunSel));
    initial begin
    Res = 1; #10; Res = 0; // Reset machine
    IR = 16'h8004; #100;
    IR = 16'h8005; #100;
    IR = 16'h8024; #100;
    IR = 16'h8044; #100;
    IR = 16'h8054; #100;
    IR = 16'h8204; #100; 
    IR = 16'h8404; #100;
    IR = 16'h8504; #100;
    end 
endmodule

module system_sim();
    // Inputs
    reg Clock;
    reg Reset;
    // Outputs
    wire [7:0] ALUOut;
    wire [3:0] ALUOutFlag;
    wire [15:0] IROut;
    wire [3:0] T;
    wire [7:0] R0;
    wire [7:0] R1;
    wire [7:0] R2;
    wire [7:0] R3;
    wire [7:0] SP;
    wire [7:0] AR;
    wire [7:0] PC;
    system uut(Clock, Reset, ALUOut, ALUOutFlag, IROut, T, R0, R1, R2, R3, SP, AR, PC);
    // Clock
    initial begin
        Clock = 0;
        forever begin
            #1;
            Clock = !Clock;
        end
    end
    // Test
    initial begin
        Reset = 1; #1; Reset = 0;
    end
endmodule