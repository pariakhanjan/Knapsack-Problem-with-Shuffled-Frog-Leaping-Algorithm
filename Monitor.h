#ifndef MONITOR_H
#define MONITOR_H

#include <systemc.h>
#include <iostream>
#include <iomanip>

SC_MODULE(Monitor) {

    sc_in<sc_int<32>> best_solution_0;
    sc_in<sc_int<32>> best_solution_1;
    sc_in<sc_int<32>> best_solution_2;
    sc_in<sc_int<32>> best_solution_3;
    sc_in<sc_int<32>> best_solution_4;
    sc_in<sc_int<32>> best_solution_5;
    sc_in<sc_int<32>> best_solution_6;
    sc_in<sc_int<32>> best_solution_7;
    sc_in<sc_int<32>> best_solution_8;

    sc_in<sc_int<32>> best_cost;

    sc_in<bool> Clk;

    void monitor() {
        while (true) {
            std::cout << "Best Solution: ";
            std::cout << best_solution_0.read() << " ";
            std::cout << best_solution_1.read() << " ";
            std::cout << best_solution_2.read() << " ";
            std::cout << best_solution_3.read() << " ";
            std::cout << best_solution_4.read() << " ";
            std::cout << best_solution_5.read() << " ";
            std::cout << best_solution_6.read() << " ";
            std::cout << best_solution_7.read() << " ";
            std::cout << best_solution_8.read() << " ";
            std::cout << " | Best Cost: " << best_cost.read() << std::endl;
            wait(); 
        }
    }

    SC_CTOR(Monitor) {
        SC_THREAD(monitor);
        sensitive << Clk.pos();
    }
};

#endif 