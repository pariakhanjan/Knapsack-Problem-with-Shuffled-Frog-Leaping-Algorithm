clear;
clc;

values = [8, 6, 3, 7, 6, 9, 8, 5, 6];
weights = [5, 4, 3, 9, 5, 7, 6, 3, 2];
capacity = 15;

while true
    disp('Welcome to the SFLA Control System!');
    disp('Choose an option:');
    disp('1. Run SFLA with default parameters');
    disp('2. Tune SFLA parameters');
    disp('3. Visualize results');
    disp('4. Exit');
   
    option = input('Enter your choice: ');
   
    switch option
        case 1
            runSFLA(10, 100, 0.5); 
           
        case 2
            tuneParameters();
           
        case 3
            visualizeResults();
           
        case 4
            disp('Exiting...');
            break; 
           
        otherwise
            disp('Invalid option. Please try again.');
    end
end

function runSFLA(numFrogs, numIterations, mutationProb)
    executablePath = 'D:/Mahta/SoftandHard/project/Project/Project/x64/Debug/Project.exe';

    if exist(executablePath, 'file') == 2
        system(sprintf('%s %d %d %f', executablePath, numFrogs, numIterations, mutationProb));

        if exist('best_solution.txt', 'file')
            bestSolution = fileread('best_solution.txt'); 
            bestSolution = str2num(bestSolution); 
            disp('Best Solution (Selected Items):');
            disp(bestSolution);
        else
            disp('Error: best_solution.txt not found.');
        end

        if exist('best_cost.txt', 'file')
            bestCost = fileread('best_cost.txt'); 
            bestCost = str2double(bestCost); 
            disp('Best Cost (Total Value of Selected Items):');
            disp(bestCost);
        else
            disp('Error: best_cost.txt not found.');
        end

        if exist('convergence_data.txt', 'file')
            convergenceData = load('convergence_data.txt');
            figure;
            plot(convergenceData, '-o', 'LineWidth', 2);
            xlabel('Iteration');
            ylabel('Best Cost');
            title('Convergence of SFLA');
            grid on;
        else
            disp('No convergence data found.');
        end
    else
        disp('Error: SystemC executable not found. Please ensure the executable is in the correct path.');
    end
end

function tuneParameters()
    executablePath = 'D:/Mahta/SoftandHard/project/Project/Project/x64/Debug/Project.exe';
   
    if exist(executablePath, 'file') ~= 2
        disp('Error: SystemC executable not found. Please ensure the executable is in the correct path.');
        return;
    end

    numFrogsList = [10, 20, 30, 40, 50];
    numIterationsList = [50, 100, 150, 200];
    mutationProbList = [0.1, 0.3, 0.5, 0.7];

    results = zeros(length(numFrogsList), length(numIterationsList), length(mutationProbList));

    for i = 1:length(numFrogsList)
        for j = 1:length(numIterationsList)
            for k = 1:length(mutationProbList)
                system(sprintf('%s %d %d %f', executablePath, numFrogsList(i), numIterationsList(j), mutationProbList(k)));

                if exist('best_cost.txt', 'file')
                    bestCost = load('best_cost.txt');
                   
                    results(i, j, k) = bestCost;
                else
                    disp('Error: best_cost.txt not found for current simulation.');
                end
            end
        end
    end

    figure;
    surf(numIterationsList, numFrogsList, results(:, :, 1)); 
    xlabel('Number of Iterations');
    ylabel('Number of Frogs');
    zlabel('Best Cost');
    title('Parameter Tuning for SFLA (Mutation Probability = 0.1)');
end

function visualizeResults()
    if exist('convergence_data.txt', 'file')
        convergenceData = load('convergence_data.txt');

        figure;
        plot(convergenceData, '-o', 'LineWidth', 2);
        xlabel('Iteration');
        ylabel('Best Cost');
        title('Convergence of SFLA');
        grid on;
    else
        disp('Error: convergence_data.txt not found.');
    end

    if exist('best_solution.txt', 'file')
        bestSolution = load('best_solution.txt');
       
        figure;
        bar(bestSolution);
        xlabel('Item Index');
        ylabel('Selected (1) or Not Selected (0)');
        title('Best Solution');
    else
        disp('Error: best_solution.txt not found.');
    end
end