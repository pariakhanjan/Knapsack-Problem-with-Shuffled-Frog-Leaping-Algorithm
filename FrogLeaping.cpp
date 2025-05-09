#include "FrogLeaping.h"
#include <algorithm>
#include <random>
#include <numeric> 

FrogLeaping::FrogLeaping(sc_module_name name, const std::vector<sc_int<32>>& values, const std::vector<sc_int<32>>& weights, sc_int<32> capacity)
    : sc_module(name), values(values), weights(weights), capacity(capacity) {
    SC_METHOD(runAlgorithm);
    sensitive << start.pos();
    dont_initialize();
}

sc_int<32> FrogLeaping::fitnessFunction(const std::vector<sc_int<32>>& solution) {
    sc_int<32> totalValue = 0;
    sc_int<32> totalWeight = 0;

    for (size_t i = 0; i < solution.size(); ++i) {
        if (solution[i] == 1) {
            totalValue += values[i];
            totalWeight += weights[i];
        }
    }

    return (totalWeight > capacity) ? sc_int<32>(0) : totalValue;
}

void FrogLeaping::runAlgorithm() {
    if (start.read()) {
        sc_int<32> numFrogs_val = numFrogs.read();
        sc_int<32> numIterations_val = numIterations.read();

        std::vector<std::vector<sc_int<32>>> frogs(numFrogs_val, std::vector<sc_int<32>>(values.size()));
        std::vector<sc_int<32>> bestSolution(values.size());
        sc_int<32> bestValue = 0;

        std::vector<int> convergenceData;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        for (auto& frog : frogs) {
            for (auto& gene : frog) {
                gene = dis(gen);
            }
        }

        const sc_int<32> S_max = 10;
        const sc_int<32> epsilon = 1; 
        sc_int<32> previousBestValue = 0; 

        for (sc_int<32> iteration = 0; iteration < numIterations_val; ++iteration) {
            std::vector<sc_int<32>> fitnessScores(numFrogs_val);
            for (int i = 0; i < numFrogs_val; ++i) {
                fitnessScores[i] = fitnessFunction(frogs[i]);
            }

            std::vector<int> indices(numFrogs_val);
            std::iota(indices.begin(), indices.end(), 0);
            std::sort(indices.begin(), indices.end(), [&fitnessScores](int a, int b) {
                return fitnessScores[a] > fitnessScores[b];
                });

            std::vector<double> probabilities(numFrogs_val);
            for (int j = 0; j < numFrogs_val; ++j) {
                probabilities[j] = 2.0 * (numFrogs_val + 1 - (j + 1)) / (numFrogs_val * (numFrogs_val + 1));
            }
            std::discrete_distribution<> weightedDist(probabilities.begin(), probabilities.end());

            for (int i = 0; i < numFrogs_val; ++i) {
                int selectedFrogIndex = indices[weightedDist(gen)];
                std::vector<sc_int<32>> worstFrog = frogs[indices[numFrogs_val - 1]];
                std::vector<sc_int<32>> newFrog = worstFrog;

                std::uniform_real_distribution<> stepDist(0.0, 1.0);
                double r = stepDist(gen);
                sc_int<32> stepSize = static_cast<sc_int<32>>(std::min(r * (bestValue - fitnessScores[indices[numFrogs_val - 1]]), static_cast<double>(S_max)));

                for (size_t j = 0; j < newFrog.size(); ++j) {
                    newFrog[j] = worstFrog[j] + stepSize;
                }

                if (fitnessFunction(newFrog) > fitnessFunction(worstFrog)) {
                    frogs[indices[numFrogs_val - 1]] = newFrog;
                }
                else {
                    stepSize = static_cast<sc_int<32>>(std::min(r * (bestValue - fitnessScores[indices[numFrogs_val - 1]]), static_cast<double>(S_max)));
                    for (size_t j = 0; j < newFrog.size(); ++j) {
                        newFrog[j] = bestSolution[j] + stepSize;
                    }

                    if (fitnessFunction(newFrog) > fitnessFunction(worstFrog)) {
                        frogs[indices[numFrogs_val - 1]] = newFrog;
                    }
                    else {
                        for (auto& gene : newFrog) {
                            gene = dis(gen);
                        }
                        frogs[indices[numFrogs_val - 1]] = newFrog;
                    }
                }
                convergenceData.push_back(bestValue);
            }

            if (fitnessFunction(frogs[indices[0]]) > bestValue) {
                bestValue = fitnessFunction(frogs[indices[0]]);
                bestSolution = frogs[indices[0]];
            }

            if (iteration > 0 && std::abs(bestValue - previousBestValue) < epsilon) {
                break;
            }
            previousBestValue = bestValue;
        }

        best_solution_0.write(bestSolution[0]);
        best_solution_1.write(bestSolution[1]);
        best_solution_2.write(bestSolution[2]);
        best_solution_3.write(bestSolution[3]);
        best_solution_4.write(bestSolution[4]);
        best_solution_5.write(bestSolution[5]);
        best_solution_6.write(bestSolution[6]);
        best_solution_7.write(bestSolution[7]);
        best_solution_8.write(bestSolution[8]);
        best_cost.write(bestValue);

        std::ofstream solutionFile("best_solution.txt");
        for (int gene : bestSolution) {
            solutionFile << gene << " ";
        }
        solutionFile.close();

        std::ofstream costFile("best_cost.txt");
        costFile << bestValue;
        costFile.close();

        std::ofstream convergenceFile("convergence_data.txt");
        for (int cost : convergenceData) {
            convergenceFile << cost << std::endl;
        }
        convergenceFile.close();
    }
}