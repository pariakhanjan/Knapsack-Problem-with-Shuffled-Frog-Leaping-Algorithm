#ifndef SYSTEMC_MODULE_H
#define SYSTEMC_MODULE_H

#include <systemc.h>
#include "FrogLeaping.h"

SC_MODULE(FrogLeapingController) {

    sc_in<sc_int<32>> numFrogs;
    sc_in<sc_int<32>> numIterations; 
    sc_in<bool> start; 

    sc_out<sc_int<32>> best_solution_0;
    sc_out<sc_int<32>> best_solution_1;
    sc_out<sc_int<32>> best_solution_2; 
    sc_out<sc_int<32>> best_solution_3; 
    sc_out<sc_int<32>> best_solution_4; 
    sc_out<sc_int<32>> best_solution_5; 
    sc_out<sc_int<32>> best_solution_6;
    sc_out<sc_int<32>> best_solution_7;
    sc_out<sc_int<32>> best_solution_8; 

    sc_out<sc_int<32>> best_cost;

    FrogLeaping* frogLeaping;

    SC_CTOR(FrogLeapingController);

    void runAlgorithm();
};

#endif 