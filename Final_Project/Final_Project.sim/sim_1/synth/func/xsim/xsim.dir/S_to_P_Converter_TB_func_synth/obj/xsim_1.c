/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
typedef void (*funcp)(char *, char *);
extern int main(int, char**);
extern void execute_2(char*, char *);
extern void execute_3(char*, char *);
extern void execute_4(char*, char *);
extern void execute_5(char*, char *);
extern void execute_6(char*, char *);
extern void execute_7(char*, char *);
extern void execute_8(char*, char *);
extern void execute_9(char*, char *);
extern void execute_35(char*, char *);
extern void execute_36(char*, char *);
extern void vlog_const_rhs_process_execute_0_fast_no_reg_no_agg(char*, char*, char*);
extern void execute_55(char*, char *);
extern void execute_59(char*, char *);
extern void execute_60(char*, char *);
extern void execute_39(char*, char *);
extern void execute_40(char*, char *);
extern void execute_41(char*, char *);
extern void execute_18(char*, char *);
extern void execute_42(char*, char *);
extern void execute_22(char*, char *);
extern void execute_44(char*, char *);
extern void execute_45(char*, char *);
extern void execute_46(char*, char *);
extern void execute_24(char*, char *);
extern void execute_25(char*, char *);
extern void execute_26(char*, char *);
extern void execute_47(char*, char *);
extern void execute_48(char*, char *);
extern void execute_28(char*, char *);
extern void execute_29(char*, char *);
extern void execute_30(char*, char *);
extern void execute_49(char*, char *);
extern void execute_50(char*, char *);
extern void vlog_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_32(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_33(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_34(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_35(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_36(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_37(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_38(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_39(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_41(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_44(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_46(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_50(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_55(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_60(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_62(char*, char*, unsigned, unsigned, unsigned);
funcp funcTab[49] = {(funcp)execute_2, (funcp)execute_3, (funcp)execute_4, (funcp)execute_5, (funcp)execute_6, (funcp)execute_7, (funcp)execute_8, (funcp)execute_9, (funcp)execute_35, (funcp)execute_36, (funcp)vlog_const_rhs_process_execute_0_fast_no_reg_no_agg, (funcp)execute_55, (funcp)execute_59, (funcp)execute_60, (funcp)execute_39, (funcp)execute_40, (funcp)execute_41, (funcp)execute_18, (funcp)execute_42, (funcp)execute_22, (funcp)execute_44, (funcp)execute_45, (funcp)execute_46, (funcp)execute_24, (funcp)execute_25, (funcp)execute_26, (funcp)execute_47, (funcp)execute_48, (funcp)execute_28, (funcp)execute_29, (funcp)execute_30, (funcp)execute_49, (funcp)execute_50, (funcp)vlog_transfunc_eventcallback, (funcp)transaction_32, (funcp)transaction_33, (funcp)transaction_34, (funcp)transaction_35, (funcp)transaction_36, (funcp)transaction_37, (funcp)transaction_38, (funcp)transaction_39, (funcp)transaction_41, (funcp)transaction_44, (funcp)transaction_46, (funcp)transaction_50, (funcp)transaction_55, (funcp)transaction_60, (funcp)transaction_62};
const int NumRelocateId= 49;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/S_to_P_Converter_TB_func_synth/xsim.reloc",  (void **)funcTab, 49);
	iki_vhdl_file_variable_register(dp + 15976);
	iki_vhdl_file_variable_register(dp + 16032);


	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/S_to_P_Converter_TB_func_synth/xsim.reloc");
}

void simulate(char *dp)
{
	iki_schedule_processes_at_time_zero(dp, "xsim.dir/S_to_P_Converter_TB_func_synth/xsim.reloc");
	// Initialize Verilog nets in mixed simulation, for the cases when the value at time 0 should be propagated from the mixed language Vhdl net

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 21008, dp + 21680, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 21064, dp + 21624, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 21120, dp + 21848, 0, 0, 0, 0, 1, 1);
	iki_execute_processes();

	// Schedule resolution functions for the multiply driven Verilog nets that have strength
	// Schedule transaction functions for the singly driven Verilog nets that have strength

}
#include "iki_bridge.h"
void relocate(char *);

void sensitize(char *);

void simulate(char *);

int main(int argc, char **argv)
{
    iki_heap_initialize("ms", "isimmm", 0, 2147483648) ;
    iki_set_sv_type_file_path_name("xsim.dir/S_to_P_Converter_TB_func_synth/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/S_to_P_Converter_TB_func_synth/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/S_to_P_Converter_TB_func_synth/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}
