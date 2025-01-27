// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Thu May 16 10:46:14 2024
// Host        : Monica-Tablet running 64-bit major release  (build 9200)
// Command     : write_verilog -mode funcsim -nolib -force -file
//               C:/Users/Public/Documents/Final_Project/Final_Project.sim/sim_1/synth/func/xsim/S_to_P_Converter_TB_func_synth.v
// Design      : S_to_P_Converter
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7k70tfbv676-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* NotValidForBitStream *)
module S_to_P_Converter
   (clk,
    rst,
    data_input,
    data_output);
  input clk;
  input rst;
  input data_input;
  output data_output;

  wire clk;
  wire clk_IBUF;
  wire clk_IBUF_BUFG;
  wire data_input;
  wire data_input_IBUF;
  wire data_output;
  wire data_output_OBUF;
  wire \shift_reg_reg[30]_srl30_n_0 ;
  wire \shift_reg_reg_n_0_[0] ;
  wire \NLW_shift_reg_reg[30]_srl30_Q31_UNCONNECTED ;

  BUFG clk_IBUF_BUFG_inst
       (.I(clk_IBUF),
        .O(clk_IBUF_BUFG));
  IBUF clk_IBUF_inst
       (.I(clk),
        .O(clk_IBUF));
  IBUF data_input_IBUF_inst
       (.I(data_input),
        .O(data_input_IBUF));
  OBUF data_output_OBUF_inst
       (.I(data_output_OBUF),
        .O(data_output));
  FDRE #(
    .INIT(1'b0)) 
    \shift_reg_reg[0] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(data_input_IBUF),
        .Q(\shift_reg_reg_n_0_[0] ),
        .R(1'b0));
  (* srl_bus_name = "\shift_reg_reg " *) 
  (* srl_name = "\shift_reg_reg[30]_srl30 " *) 
  SRLC32E #(
    .INIT(32'h00000000)) 
    \shift_reg_reg[30]_srl30 
       (.A({1'b1,1'b1,1'b1,1'b0,1'b1}),
        .CE(1'b1),
        .CLK(clk_IBUF_BUFG),
        .D(\shift_reg_reg_n_0_[0] ),
        .Q(\shift_reg_reg[30]_srl30_n_0 ),
        .Q31(\NLW_shift_reg_reg[30]_srl30_Q31_UNCONNECTED ));
  FDRE #(
    .INIT(1'b0)) 
    \shift_reg_reg[31] 
       (.C(clk_IBUF_BUFG),
        .CE(1'b1),
        .D(\shift_reg_reg[30]_srl30_n_0 ),
        .Q(data_output_OBUF),
        .R(1'b0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
