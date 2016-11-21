// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vtop_H_
#define _Vtop_H_

#include "verilated.h"
#include "verilated_cov.h"
#include<vector>
class Vtop__Syms;

//----------

VL_MODULE(Vtop) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(req_0,0,0);
    VL_IN8(req_1,0,0);
    VL_OUT8(gnt_0,0,0);
    VL_OUT8(gnt_1,0,0);
    //char	__VpadToAlign6[2];
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(ex1__DOT__state,2,0);
    VL_SIG8(ex1__DOT__next_state,2,0);
    //char	__VpadToAlign14[2];
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vfunc_ex1__DOT__fsm_function__0__Vfuncout,2,0);
    VL_SIG8(__Vfunc_ex1__DOT__fsm_function__0__state,2,0);
    VL_SIG8(__Vfunc_ex1__DOT__fsm_function__0__req_0,0,0);
    VL_SIG8(__Vfunc_ex1__DOT__fsm_function__0__req_1,0,0);
    VL_SIG8(__Vclklast__TOP__clock,0,0);
    //char	__VpadToAlign25[3];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop__Syms*	__VlSymsp;		// Symbol table
  private:
    // Coverage
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
	const char* hierp, const char* pagep, const char* commentp);
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
  public:
    
    // CONSTRUCTORS
  private:
    Vtop& operator= (const Vtop&);	///< Copying not allowed
    Vtop(const Vtop&);	///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible WRT DPI scope names.
    Vtop(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop();
    
    // USER METHODS
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    static QData	_change_request(Vtop__Syms* __restrict vlSymsp);
  public:
    static void	_combo__TOP__2(Vtop__Syms* __restrict vlSymsp);
  private:
    void	_ctor_var_reset();
  public:
    static void	_eval(Vtop__Syms* __restrict vlSymsp);
    static void	_eval_initial(Vtop__Syms* __restrict vlSymsp);
    static void	_eval_settle(Vtop__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__1(Vtop__Syms* __restrict vlSymsp);
    void set_input_with_reset (vector<bool> vecIn);
    uint32_t get_cov_pt_value(uint32_t id);
    void sim_init();
    void toggle_clock();
    uint32_t num_branch_cov_pts();
} VL_ATTR_ALIGNED(128);

#endif  /*guard*/
