module Gowin_rPLL (clkout, clkin, lock_o, reset, reset_p, clkfb, clkoutd_o, fdiv, idiv);
output wire clkout;
output wire lock_o;
input wire clkin;
input wire reset;
input wire reset_p;
input wire clkfb;
output wire clkoutd_o;
input wire [5:0] fdiv;
input wire [5:0] idiv;

parameter DEVICE = "GW1N-1",
	      FCLKIN = "16",
	      FBDIV_SEL = 0,
		  IDIV_SEL =  0,
	      ODIV_SEL =  8,
	      DYN_ODIV_SEL="false",
          DYN_FBDIV_SEL="false",
          DYN_IDIV_SEL="false",
	      DYN_SDIV_SEL=2,
          PSDA_SEL="0000";

wire clkoutp_o;
wire clkoutd3_o;
wire gw_gnd;
wire gw_vcc;

assign gw_gnd = 1'b0;
assign gw_vcc = 1'b1;

rPLL rpll_inst (
    .CLKOUT(clkout),
    .LOCK(lock_o),
    .CLKOUTP(clkoutp_o),
    .CLKOUTD(clkoutd_o),
    .CLKOUTD3(clkoutd3_o),
    .RESET(reset),
    .RESET_P(reset_p),
    .CLKIN(clkin),
    .CLKFB(gw_gnd),
    .FBDSEL(fdiv),
    .IDSEL(idiv),
    .ODSEL({gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd}),
    .PSDA({gw_gnd,gw_gnd,gw_gnd,gw_gnd}),
    .DUTYDA({gw_gnd,gw_gnd,gw_gnd,gw_gnd}),
    .FDLY({gw_gnd,gw_gnd,gw_gnd,gw_gnd})
);

defparam rpll_inst.DEVICE = DEVICE;
defparam rpll_inst.FCLKIN = FCLKIN;
defparam rpll_inst.FBDIV_SEL = FBDIV_SEL;
defparam rpll_inst.DYN_IDIV_SEL = DYN_IDIV_SEL;
defparam rpll_inst.IDIV_SEL = IDIV_SEL;
defparam rpll_inst.DYN_FBDIV_SEL = DYN_FBDIV_SEL;
defparam rpll_inst.DYN_ODIV_SEL = DYN_ODIV_SEL;
defparam rpll_inst.ODIV_SEL = ODIV_SEL;
defparam rpll_inst.PSDA_SEL = PSDA_SEL;
defparam rpll_inst.DYN_DA_EN = "false";
defparam rpll_inst.DUTYDA_SEL = "0100";
defparam rpll_inst.CLKOUT_FT_DIR = 1'b1;
defparam rpll_inst.CLKOUTP_FT_DIR = 1'b1;
defparam rpll_inst.CLKOUT_DLY_STEP = 0;
defparam rpll_inst.CLKOUTP_DLY_STEP = 0;
defparam rpll_inst.CLKFB_SEL = "internal";
defparam rpll_inst.CLKOUT_BYPASS = "false";
defparam rpll_inst.CLKOUTP_BYPASS = "false";
defparam rpll_inst.CLKOUTD_BYPASS = "false";
defparam rpll_inst.DYN_SDIV_SEL = DYN_SDIV_SEL;
defparam rpll_inst.CLKOUTD_SRC = "CLKOUTP";
defparam rpll_inst.CLKOUTD3_SRC = "CLKOUTP";

endmodule //Gowin_rPLL


/**

    f_clkout = f_clkin * FBDIV / IDIV
    f_vco  = f_clkout * ODIV
    f_clkoutd = f_clkout / SDIV
    
    Desired behaviour clkin = 16
     clkoutd = 8
     clkout = clkin * 4 
     
    FBDIV / IDIV = 4
    FBDIV / (IDIV * SDIV) = 0.5
    
    VCO = FCLKIN*(FBDIV_SEL+1)*ODIV_SEL/(IDIV_SEL+1) = 1024.0MHz not in range 400 - 900MHz
    
    for fbdiv_sel in [0..63]:
        for idiv_sel in [0..63]:
        
        
**/

`define PLL_DEVICE "GW1N-1"
`define PLL_FCLKIN "16"
`define PLL_FBDIV_SEL 1
`define PLL_IDIV_SEL  1
`define PLL_ODIV_SEL  32
`define DYN_SDIV_SEL  2

module ser_pll (output fast_clock, output rx_clock, input clkin);
	wire VCC;
	wire GND;
	assign VCC = 1'b1;
	assign GND = 1'b0;

	wire [5:0]fdiv;
	assign fdiv = 6'd0;
	wire [5:0]idiv;
	assign idiv = 6'd0;

    wire lock;
    reg reset = 0;
    
	Gowin_rPLL pll0(
		.clkout(fast_clock),
		.clkfb(GND),
		.clkin(clkin),
		.clkoutd_o(rx_clock),
		.lock_o(lock),
		.fdiv(fdiv),
		.idiv(idiv),
		.reset(GND),
		.reset_p(GND)
	);
	defparam pll0.DEVICE = `PLL_DEVICE;
	defparam pll0.FCLKIN = `PLL_FCLKIN;
	defparam pll0.FBDIV_SEL = `PLL_FBDIV_SEL;
	defparam pll0.IDIV_SEL =  `PLL_IDIV_SEL;
	defparam pll0.ODIV_SEL =  `PLL_ODIV_SEL;

	defparam pll0.DYN_FBDIV_SEL="false";
	defparam pll0.DYN_IDIV_SEL="false";

	defparam pll0.DYN_ODIV_SEL="false";
	defparam pll0.DYN_SDIV_SEL=`DYN_SDIV_SEL;
	defparam pll0.PSDA_SEL="0000";

endmodule //ser_pll
