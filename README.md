# FrogLeapingOptimizer  

## Overview  
A hybrid SystemC-MATLAB implementation of the Shuffled Frog Leaping Algorithm (SFLA) for solving the 0/1 Knapsack Problem. The project combines:  
- **SystemC** for hardware-aware simulation  
- **MATLAB** for algorithm control and visualization  
- **Metaheuristic optimization** via SFLA  

---

## Key Features  
### SystemC Core  
- Implements SFLA with configurable frogs/iterations  
- Generates three output files:  
  - `best_solution.txt` (binary selection vector)  
  - `best_cost.txt` (maximized value)  
  - `convergence_data.txt` (optimization trajectory)  

### MATLAB Interface (`sfla_control.m`)  
Interactive menu with four functions:  
1. **Run SFLA** with default parameters  
2. **Tune parameters** (automated grid search)  
3. **Visualize results** (plots and analysis)  
4. **Exit program**  

---

## Project Files  

### SystemC Modules  
| File | Description |  
|------|-------------|  
| `FrogLeaping.(h/cpp)` | Core SFLA implementation |  
| `FrogLeapingController.(h/cpp)` | SystemC module wrapper |  
| `Main.cpp` | Simulation environment setup |  
| `Driver.h` | Clock-driven stimulus |  
| `Monitor.h` | Real-time solution logger |  

### MATLAB Script  
```matlab
function runSFLA(numFrogs, numIterations, mutationProb)
% Executes SystemC binary and analyzes results
% Features:
% - Parameter sweeps (frogs: 10-50, iterations: 50-200)
% - Convergence plotting
% - Solution visualization
```

---

## Getting Started  

### 1. Compile SystemC  
```bash
g++ -I. -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 \
    -lsystemc -lm Main.cpp FrogLeaping.cpp \
    FrogLeapingController.cpp Driver.cpp Monitor.cpp \
    -o FrogLeapingOptimizer
```

### 2. Run MATLAB Interface  
```matlab
>> sfla_control % Launch interactive menu
```

---

## Usage Examples  

### Parameter Tuning  
```matlab
>> tuneParameters() % Tests combinations:
                    % Frogs = [10,20,30,40,50]
                    % Iterations = [50,100,150,200]
                    % Mutation = [0.1,0.3,0.5,0.7]
```
Generates 3D performance surface plot  

### Result Visualization  
```matlab
>> visualizeResults() % Creates:
                      % 1. Convergence curve plot
                      % 2. Solution binary vector plot
```

---

## Configuration  

### Key Parameters  
| Parameter | Location | Default |  
|-----------|----------|---------|  
| Capacity | `Main.cpp` | 15 |  
| Values/Weights | `Main.cpp` | [8,6,...], [5,4,...] |  
| Frogs/Iterations | `sfla_control.m` | 10, 100 |  

### MATLAB Customization  
1. Update executable path:  
```matlab
executablePath = 'your_path/Project.exe'; % Line 12
```  
2. Adjust parameter ranges in `tuneParameters()`  

---

## Dependencies  
- SystemC 2.3.3+  
- MATLAB (optional)  
- C++11 compiler  

---

## License  
MIT License  
