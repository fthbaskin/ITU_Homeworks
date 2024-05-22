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