`timescale 1ns / 1ps

// Fatih Baskýn 150210710
module sr_latch_no_enable_sim();
    // Inputs
    reg S, R;
    // Outputs
    wire Q, Q_neg;
    // Unit
    sr_latch_no_enable uut(.S(S), .R(R), .Q(Q), .Q_neg(Q_neg));
    // Test
    initial begin;
        S = 1; R = 0; #10;
        S = 0; R = 0; #10;
        R = 1; S = 0; #10;
        R = 0; S = 0; #10;
        R = 1; S = 1; #10;
        R = 0; S = 0; #10;
        S = 1; R = 0; #10;
        R = 0; S = 0; #10;
        S = 0; R = 1;    
    end
endmodule

// Fatih Baskýn 150210710
module sr_latch_enable_sim();
    // Inputs
    reg S, R, E;
    // Outputs
    wire Q, Q_neg;
    // Unit
    sr_latch_enable uut(.S(S), .R(R), .E(E), .Q(Q), .Q_neg(Q_neg));
    // Test
    initial begin;
        S = 1; R = 0; E = 1; #10;
        S = 0; R = 1; E = 1; #10;
        S = 1; R = 0; E = 0; #10;
        S = 1; R = 0; E = 1; #10;
        S = 1; R = 0; E = 1; #10;
        S = 0; R = 1; E = 0; #10;
        S = 0; R = 1; E = 1; #10;
        S = 0; R = 1; E = 1; #10;
        S = 1; R = 1; E = 1; #10;
    end
endmodule

// Fatih Baskýn
module nor_gate_sim();
    // Inputs
    reg A,B;
    // Outputs
    wire C;
    // Module
    nor_gate uut(.a(A), .b(B), .c(C));
    // Test
    initial begin
        A = 0; B = 0; #10;
        A = 0; B = 1; #10;
        A = 1; B = 0; #10;
        A = 1; B = 1; #10;
        A = 0; B = 0; #10;
    end
endmodule

// Fatih Baskýn
module nand_gate_sim();
    // Inputs
    reg A,B;
    // Outputs
    wire C;
    // Module
    nand_gate uut(.a(A), .b(B), .c(C));
    // Test
    initial begin
        A = 0; B = 0; #10;
        A = 0; B = 1; #10;
        A = 1; B = 0; #10;
        A = 1; B = 1; #10;
        A = 0; B = 0; #10;
    end
endmodule

// Fatih Baskýn
module d_latch_enable_sim();
    // Inputs
    reg D, E;
    // Outputs
    wire Q, Q_neg;
    // Module
    d_latch_enable uut(.D(D), .E(E), .Q(Q), .Q_neg(Q_neg));
    // Test
    initial begin
        D = 1; E = 1; #10;
        D = 0; E = 0; #10;
        D = 0; E = 1; #10;
        D = 1; E = 0; #10;
        D = 1; E = 1; #10;
    end
endmodule

// Fatih Baskýn
module d_flip_flop_posedge_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
            #10;
            Clk = !Clk;
        end
    end
    // Input
    reg D;
    // Outputs
    wire Q, Q_neg;
    // Module
    d_flip_flop_posedge uut(.D(D), .Clk(Clk), .Q(Q), .Q_neg(Q_neg));
    // Test
    initial begin
        D = 0; #5;
        D = 1; #20;
        D = 0; #20;
        #5;
        D = 1; #20;
        D = 0; #20;
        #5;
        D = 1; #20;
        D = 0; #20;    
    end
endmodule

// Fatih Baskýn
module sr_flip_flop_posedge_sim();
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
    reg S, R;
    // Outputs
    wire Q, Q_neg;
    // Module
    sr_flip_flop_posedge uut(.S(S), .R(R), .Clk(Clk), .Q(Q), .Q_neg(Q_neg));
    // Test
    initial begin
        S = 0; R = 0; # 5;
        S = 1; R = 0; # 10; 
        S = 0; R = 0; # 10;
        S = 0; R = 0; # 20;
        S = 0; R = 1; # 10; 
        S = 0; R = 0; # 10;
        S = 0; R = 0; # 20;        
        S = 1; R = 1; # 10; 
        S = 0; R = 0; # 10;
        S = 0; R = 0; # 20;           
    end
endmodule

// Fatih Baskýn
module jk_flip_flop_posedge_sim();
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
    reg J, K;
    // Outputs
    wire Q, Q_neg;
    // Module
    jk_flip_flop_posedge uut(.J(J), .K(K), .Clk(Clk), .Q(Q), .Q_neg(Q_neg));
    // Test
    initial begin
        J = 0; K = 0; # 5;
        J = 0; K = 1; # 10; 
        J = 0; K = 0; # 10;
        J = 0; K = 0; # 20;
        J = 1; K = 0; # 10; 
        J = 0; K = 0; # 10;
        J = 0; K = 0; # 20;        
        J = 1; K = 1; # 10; 
        J = 0; K = 0; # 10;
        J = 0; K = 0; # 20;           
    end
endmodule

// Elvan Teke 150190102
module asynchronous_up_counter_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end
    // Output
    wire [3:0] Q;
    
    reg Set;
    // Module
    asynchronous_up_counter uut(.Clk(Clk), .Set(Set), .Q(Q));
    // Test
    initial begin
        #5;
        Set = 1; #10;
        Set = 0;         
    end
endmodule

module synchronous_up_counter_sim();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end
    // Output
    wire [3:0] Q;    
    // Set
    reg Set;
    // Module
    synchronous_up_counter uut(.Clk(Clk), .Set(Set), .Q(Q));
    // Test
    initial begin
            # 5;
            Set = 1; #10;
            Set = 0;                      
    end
endmodule

module part_7_sim_1_2_freq();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end
    //Inputs
    reg [7:0] A;
    reg load;
    //Outputs
    wire out;
    // Module
    part_7 uut(.loaded(A), .Clk(Clk), .load(load), .out(out));
    // Test
    initial begin
        #5;
        // 1/2 frequency
        A = 8'b01010101; load = 1'b1; # 10;
        load = 1'b0;
    end
endmodule

module part_7_sim_1_4_freq();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end
    //Inputs
    reg [7:0] A;
    reg load;
    //Outputs
    wire out;
    // Module
    part_7 uut(.loaded(A), .Clk(Clk), .load(load), .out(out));
    // Test
    initial begin
        #5;
        // 1/2 frequency
        A = 8'b00110011; load = 1'b1; # 10;
        load = 1'b0;
    end
endmodule

module part_7_sim_1_8_freq();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end
    //Inputs
    reg [7:0] A;
    reg load;
    //Outputs
    wire out;
    // Module
    part_7 uut(.loaded(A), .Clk(Clk), .load(load), .out(out));
    // Test
    initial begin
        #5;
        // 1/2 frequency
        A = 8'b00001111; load = 1'b1; # 10;
        load = 1'b0;
    end
endmodule

module part_7_sim_1_3_pulse();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end
    //Inputs
    reg [7:0] A;
    reg load;
    //Outputs
    wire out;
    // Module
    part_7 uut(.loaded(A), .Clk(Clk), .load(load), .out(out));
    // Test
    initial begin
        #5;
        // 1/2 frequency
        A = 8'b00010001; load = 1'b1; # 10;
        load = 1'b0;
    end
endmodule

module part_7_sim_1_7_pulse();
    // Clock
    reg Clk;
    initial begin
        Clk = 0;
        forever begin
        #10;
        Clk = !Clk;
        end
    end
    //Inputs
    reg [7:0] A;
    reg load;
    //Outputs
    wire out;
    // Module
    part_7 uut(.loaded(A), .Clk(Clk), .load(load), .out(out));
    // Test
    initial begin
        #5;
        // 1/2 frequency
        A = 8'b00000001; load = 1'b1; # 10;
        load = 1'b0;
    end
endmodule