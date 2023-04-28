`include "radio_module.v"



module radio_module_tb;

    reg SYS_CLK = 0;
    reg [1:0] R1_I;
    reg [1:0] R1_Q;
    reg [1:0] R0_I;
    reg [1:0] R0_Q;
    wire DATA_OUT;
    
    wire SYNC;
    wire MISC;

    wire CLK_OUT1;  // clock to radio 1
    wire CLK_OUT2;  // clock to radio 2
    wire CLK_OUT3;   // clk to uC
    
    
    always #10 SYS_CLK = !SYS_CLK;
    
    initial begin
        $dumpfile("./radio_module_tb.lx2");
        $dumpvars(-1, radio_module_tb);
        $dumpon();
        
        R0_I = 2'b00;
        R0_Q = 2'b01;
        R1_I = 2'b10;
        R1_Q = 2'b11;

        #300 $finish();
        $dumpoff();
    end
    
    radio_module dut(
        .SYS_CLK(SYS_CLK),
        .R0_I(R0_I),
        .R0_Q(R0_Q),
        .R1_I(R1_I),
        .R1_Q(R1_Q),
        .DATA_OUT(DATA_OUT),
    
        .SYNC(SYNC),
        .MISC(MISC),

        .CLK_OUT1(CLK_OUT1),  // clock to radio 1
        .CLK_OUT2(CLK_OUT2),  // clock to radio 2
        .CLK_OUT3(CLK_OUT3));

endmodule
