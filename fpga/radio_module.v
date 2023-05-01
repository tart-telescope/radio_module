


module radio_module (
        input SYS_CLK, // 16.368 MHz global clock
        input R0_D0,
        input R0_D1,
        input R0_D2,
        input R0_D3,
        
        input R1_D0,
        input R1_D1,
        input R1_D2,
        input R1_D3,
        output reg DATA_OUT,
        
        output SYNC,
        output MISC,

        output CLK_OUT1,  // clock to radio 1
        output CLK_OUT2,  // clock to radio 2
        output CLK_OUT3   // clk to uC
    );
    wire DSP_DATA_0;
    wire DSP_CLK_0;
    
    // Set up a the output clock for 
    
    assign CLK_OUT1 = SYS_CLK;   // Clock for Radio 0
    assign CLK_OUT2 = SYS_CLK;   // Clock for Radio 1
    assign CLK_OUT3 = SYS_CLK;   // Clock for CPU
        
    reg tog = 0;
    
    always @(posedge SYS_CLK)
    begin
        DATA_OUT <= R0_D0;
        tog <= !tog;
    end

endmodule
