`include "ser_pll.v"



module top (
    input DATA_CLK,
    input [1:0] R1_I,
    input [1:0] R1_Q,
    input [1:0] R0_I,
    input [1:0] R0_Q,
    output reg DATA_OUT,
    
    output SYNC,
    output MISC,

    output CLK_OUT1,
    output CLK_OUT2,
    output CLK_OUT3
);
    wire rx_clk; // 8 MHz data clock from radios
    wire fast_clk; // serial clock
    
    reg[7:0] tx_data;
    
    // Set up a the output clock for 
    
    assign CLK_OUT1 = DATA_CLK;   // Clock for Radio 0
    assign CLK_OUT2 = DATA_CLK;   // Clock for Radio 1
    
    // Set up PLL for the serialized data
    // input is 16.368 MHz GPS clock. Output is
    // the serialized data clock.
    ser_pll pll_x10(.clkout(fast_clk),
                    .clkoutd(rx_clk), 
                    .clkin(DATA_CLK));
    
    reg [3:0] ptr = 0;

    always @(posedge rx_clk)
    begin
        tx_data <= {R0_I, R0_0, R1_I, R1_Q };
    end

    always @(posedge fast_clk)
    begin
        DATA_OUT <= tx_data[ptr];
        ptr = ptr + 1;
    end

endmodule
