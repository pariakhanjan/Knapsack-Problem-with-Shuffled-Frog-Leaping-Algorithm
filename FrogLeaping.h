#ifndef FROG_LEAPING_H
#define FROG_LEAPING_H

#include <systemc.h>
#include <vector>

SC_MODULE(FrogLeaping) {

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

    std::vector<sc_int<32>> values; 
    std::vector<sc_int<32>> weights; 
    sc_int<32> capacity; 

    FrogLeaping(sc_module_name name, const std::vector<sc_int<32>>&values, const std::vector<sc_int<32>>&weights, sc_int<32> capacity);

    void runAlgorithm();

    sc_int<32> fitnessFunction(const std::vector<sc_int<32>>&solution);
};

#endif 