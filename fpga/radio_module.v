`include "ser_pll.v"



module top (
    input SYS_CLK, // 16.368 MHz global clock
    input [1:0] R1_I,
    input [1:0] R1_Q,
    input [1:0] R0_I,
    input [1:0] R0_Q,
    output reg DATA_OUT,
    
    output SYNC,
    output MISC,

    output CLK_OUT1,  // clock to radio 1
    output CLK_OUT2,  // clock to radio 2
    output CLK_OUT3   // clk to uC
);
    wire rx_clk; // 8 MHz data clock from radios
    wire fast_clk; // serial clock
    
    reg[7:0] tx_data;
    
    // Set up a the output clock for 
    
    assign CLK_OUT1 = SYS_CLK;   // Clock for Radio 0
    assign CLK_OUT2 = SYS_CLK;   // Clock for Radio 1
    assign CLK_OUT3 = SYS_CLK;   // Clock for CPU
    
    // Set up PLL for the serialized data
    // input is 16.368 MHz GPS clock. Output is
    // the serialized data clock.
    //ser_pll pll_x10(.clkout(fast_clk),
    //                .clkoutd(rx_clk), 
    //                .clkin(SYS_CLK));
    assign fast_clk = SYS_CLK;
    
    reg [2:0] ptr = 0;

    always @(posedge SYS_CLK)
    begin
        // latch the tx data
        tx_data <= {R0_I, R0_Q, R1_I, R1_Q };
    end

    always @(posedge fast_clk)
    begin
        DATA_OUT <= tx_data[ptr];
        ptr <= ptr + 1;
    end

endmodule
