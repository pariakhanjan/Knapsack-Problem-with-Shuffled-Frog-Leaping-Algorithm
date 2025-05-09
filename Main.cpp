#include <systemc.h>
#include "FrogLeaping.h"
#include "Driver.h"
#include "Monitor.h"

int sc_main(int argc, char* argv[]) {
    sc_clock Clk("Clk", 10, SC_NS);
    sc_signal<bool> start;
    sc_signal<sc_int<32>> best_cost;
    sc_signal<sc_int<32>> numFrogs, numIterations;

    sc_signal<sc_int<32>> best_solution_0;
    sc_signal<sc_int<32>> best_solution_1;
    sc_signal<sc_int<32>> best_solution_2;
    sc_signal<sc_int<32>> best_solution_3;
    sc_signal<sc_int<32>> best_solution_4;
    sc_signal<sc_int<32>> best_solution_5;
    sc_signal<sc_int<32>> best_solution_6;
    sc_signal<sc_int<32>> best_solution_7;
    sc_signal<sc_int<32>> best_solution_8;

    std::vector<sc_int<32>> values = { 8, 6, 3, 7, 6, 9, 8, 5, 6 };
    std::vector<sc_int<32>> weights = { 5, 4, 3, 9, 5, 7, 6, 3, 2 };
    int capacity = 15;

    FrogLeaping frogLeaping("FrogLeaping", values, weights, capacity);
    Driver driver("Driver");
    Monitor monitor("Monitor");

    frogLeaping.numFrogs(numFrogs);
    frogLeaping.numIterations(numIterations);
    frogLeaping.start(start);
    frogLeaping.best_cost(best_cost);

    frogLeaping.best_solution_0(best_solution_0);
    frogLeaping.best_solution_1(best_solution_1);
    frogLeaping.best_solution_2(best_solution_2);
    frogLeaping.best_solution_3(best_solution_3);
    frogLeaping.best_solution_4(best_solution_4);
    frogLeaping.best_solution_5(best_solution_5);
    frogLeaping.best_solution_6(best_solution_6);
    frogLeaping.best_solution_7(best_solution_7);
    frogLeaping.best_solution_8(best_solution_8);

    driver.start(start);
    driver.Clk(Clk);

    monitor.best_cost(best_cost);
    monitor.Clk(Clk);

    monitor.best_solution_0(best_solution_0);
    monitor.best_solution_1(best_solution_1);
    monitor.best_solution_2(best_solution_2);
    monitor.best_solution_3(best_solution_3);
    monitor.best_solution_4(best_solution_4);
    monitor.best_solution_5(best_solution_5);
    monitor.best_solution_6(best_solution_6);
    monitor.best_solution_7(best_solution_7);
    monitor.best_solution_8(best_solution_8);

    numFrogs.write(10);
    numIterations.write(100);

    sc_start(100, SC_NS); 

    return 0;
}