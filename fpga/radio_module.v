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
    // Set up a counter
    reg [25:0] ctr_q = 0;

    always @(posedge DATA_CLK)
    begin
        ctr_q <= ctr_q + 1;
        DATA_OUT <= ctr_q[23];
    end

endmodule
