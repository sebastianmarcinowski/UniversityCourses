from GA import *

if __name__ == "__main__":
    n = 50
    scale = 2000
    populationSize = 100
    T = 100
    crossoverProbability = 0.9
    mutationProbability = 0.01

    selectionMethod = "roulette"
    crossoverMethod = "doublePoint"

    price, weights, C = generateDKP(n, scale)

    # GA with harsh penalty
    gaHarsh = GA(n, prepareDKPHarsh, (price, weights, C), populationSize, T, crossoverProbability, mutationProbability)
    bestIndividualHarsh, bestFitnessHarsh = gaHarsh.fit(selectionMethod=selectionMethod, crossoverMethod=crossoverMethod)

    # GA with soft penalty
    gaSoft = GA(n, prepareDKPSoft, (price, weights, C), populationSize, T, crossoverProbability, mutationProbability)
    bestIndividualSoft, bestFitnessSoft = gaSoft.fit(selectionMethod=selectionMethod, crossoverMethod=crossoverMethod)

    # Exact solution
    exactValue, exactSolution = DKP(price, weights, C)

    # Comparison
    ratioHarsh, bitwiseAgreementHarsh = compareSolutions(bestFitnessHarsh, exactValue, bestIndividualHarsh, exactSolution)
    ratioSoft, bitwiseAgreementSoft = compareSolutions(bestFitnessSoft, exactValue, bestIndividualSoft, exactSolution)

    print("Best Individual (Genetic - Harsh):", bestIndividualHarsh)
    print("Best Fitness (Genetic - Harsh):", bestFitnessHarsh)
    print("Best Individual (Genetic - Soft):", bestIndividualSoft)
    print("Best Fitness (Genetic - Soft):", bestFitnessSoft)
    print("Best Value (Exact):", exactValue)
    print("Exact Solution:", exactSolution)
    print("Ratio (Genetic/Exact - Harsh):", ratioHarsh)
    print("Bitwise Agreement (% - Harsh):", bitwiseAgreementHarsh)
    print("Ratio (Genetic/Exact - Soft):", ratioSoft)
    print("Bitwise Agreement (% - Soft):", bitwiseAgreementSoft)

    plotFitness(gaHarsh.fitnessHistory, selectionMethod, crossoverMethod)
    plotFitness(gaSoft.fitnessHistory, selectionMethod, crossoverMethod)