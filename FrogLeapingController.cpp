#include "FrogLeapingController.h"

FrogLeapingController::FrogLeapingController(sc_module_name name) : sc_module(name) {

    std::vector<sc_int<32>> values = { 8, 6, 3, 7, 6, 9, 8, 5, 6 };
    std::vector<sc_int<32>> weights = { 5, 4, 3, 9, 5, 7, 6, 3, 2 };

    int capacity = 15;

    frogLeaping = new FrogLeaping("FrogLeaping", values, weights, capacity);

    frogLeaping->numFrogs(numFrogs);
    frogLeaping->numIterations(numIterations);
    frogLeaping->start(start);
    frogLeaping->best_cost(best_cost);

    frogLeaping->best_solution_0(best_solution_0);
    frogLeaping->best_solution_1(best_solution_1);
    frogLeaping->best_solution_2(best_solution_2);
    frogLeaping->best_solution_3(best_solution_3);
    frogLeaping->best_solution_4(best_solution_4);
    frogLeaping->best_solution_5(best_solution_5);
    frogLeaping->best_solution_6(best_solution_6);
    frogLeaping->best_solution_7(best_solution_7);
    frogLeaping->best_solution_8(best_solution_8);
}

void FrogLeapingController::runAlgorithm() {
    frogLeaping->runAlgorithm();

    std::cout << "Best solution: ";
    std::cout << best_solution_0.read() << " ";
    std::cout << best_solution_1.read() << " ";
    std::cout << best_solution_2.read() << " ";
    std::cout << best_solution_3.read() << " ";
    std::cout << best_solution_4.read() << " ";
    std::cout << best_solution_5.read() << " ";
    std::cout << best_solution_6.read() << " ";
    std::cout << best_solution_7.read() << " ";
    std::cout << best_solution_8.read() << " ";
    std::cout << std::endl;

    sc_int<32> bestCost = best_cost.read();
    std::cout << "Best cost (total value of selected items): " << bestCost << std::endl;
}