from cProfile import label

import numpy as np
import matplotlib.pyplot as plt
from itertools import permutations
from sympy.utilities.iterables import multiset_permutations

# Dyskretny problem plecakowy
def DKP(price, weights, C):
    n = len(price)
    f = np.zeros((n + 1, C + 1))
    keep = np.zeros((n + 1, C + 1), dtype=int)

    for i in range(1, n + 1):
        for w in range(1, C + 1):
            if weights[i - 1] <= w:
                if price[i - 1] + f[i - 1][w - weights[i - 1]] > f[i - 1][w]:
                    f[i][w] = price[i - 1] + f[i - 1][w - weights[i - 1]]
                    keep[i][w] = 1
                else:
                    f[i][w] = f[i - 1][w]
            else:
                f[i][w] = f[i - 1][w]

    solution = np.zeros(n, dtype=int)
    K = C
    for i in range(n, 0, -1):
        if keep[i][K] == 1:
            solution[i - 1] = 1
            K -= weights[i - 1]

    return f[n][C], solution

def generateDKP(n, scale):
    items = np.ceil(scale * np.random.rand(n, 2)).astype("int32")
    C = int(np.ceil(0.5 * 0.5 * n * scale))
    v = items[:, 0]
    c = items[:, 1]
    return v, c, C

def prepareDKPHarsh(backpack, price, weights, C):
    f = np.dot(backpack, price)
    w = np.dot(backpack, weights)
    if w > C:
        return 0
    return f

def prepareDKPSoft(backpack, price, weights, C):
    f = np.dot(backpack, price)
    w = np.dot(backpack, weights)
    if w > C:
        return f - (w - C)  # Soft penalty
    return f

def compareSolutions(genetic_value, exact_value, genetic_solution, exact_solution):
    ratio = genetic_value / exact_value
    bitwise_agreement = np.sum(genetic_solution == exact_solution) / len(genetic_solution) * 100
    return ratio, bitwise_agreement

def plotFitness(fitnessHistory, selectionMethod, crossoverMethod):
    plt.plot(fitnessHistory)
    plt.xlabel('Generation')
    plt.ylabel('Fitness Value')
    plt.title('Fitness over Generations - Selection: ' + selectionMethod + ", Crossover: " + crossoverMethod)
    plt.show()

# Komiwojażer
def generateTSP(n):
    distanceMatrix = np.random.randint(0,10, size=(n, n))
    distanceMatrix = 2 * np.abs(distanceMatrix - distanceMatrix.T)
    # print (distanceMatrix)
    return distanceMatrix

def TSP(distanceMatrix, path):
    n = len(path)
    totalDistance = 0
    for i in range(n):
        totalDistance += distanceMatrix[int(path[i - 1])][int(path[i])]
    return totalDistance

def solveTSP(distancesMatrix):
    n = len(distancesMatrix)
    minDistance = np.inf
    minPath = None
    for path in multiset_permutations(range(n)):
        distance = TSP(distancesMatrix, path)
        if distance < minDistance:
            minDistance = distance
            minPath = path
    return minPath, minDistance

def plotFitnessTSP(fitnessHistory, avgFitness, bestFitness, selectionMethod, crossoverMethod):
    plt.plot(fitnessHistory, label="Best in current populations")
    plt.plot(avgFitness, label="Average in current populations")
    plt.plot(bestFitness, label="Best overall")
    plt.title(f"Fitness History ({selectionMethod} selection, {crossoverMethod} crossover)")
    plt.xlabel("Generation")
    plt.ylabel("Fitness")
    plt.legend()
    plt.show()

# Algorytm genetyczny
class GA:
    def __init__(self,n,adaptationFunc, adaptationFuncArgs=(), populationSize=1000, T=100, crossoverProbability=0.9, mutationProbability=1e-3, problem="DKP"):
        self.n = n
        self.adaptationFunc = adaptationFunc
        self.adaptationFuncArgs = adaptationFuncArgs
        self.populationSize = populationSize
        self.T = T # liczba iteracji głownej pętli genetycznej
        self.crossoverProbability = crossoverProbability
        self.mutationProbability = mutationProbability
        self.problem = problem
        if self.problem == "DKP":
            self.population = np.random.randint(2, size=(self.populationSize, self.n))
        elif self.problem == "TSP":
            self.population = np.array([np.random.permutation(self.n) for _ in range(self.populationSize)])
        self.fitnessHistory = []
        self.fitnessBest = []
        self.fitnessAvg = []

    def rouletteSelection(self, fitnessValues):
        total = np.sum(fitnessValues)
        probabilities = fitnessValues / total
        cumulativeProbabilities = np.cumsum(probabilities)
        selectedIndices = []
        for _ in range(self.populationSize):
            r = np.random.rand()
            for i, cumulativeProbability in enumerate(cumulativeProbabilities):
                if r < cumulativeProbability:
                    selectedIndices.append(i)
                    break
        return self.population[selectedIndices]

    def rankSelection(self, fitnessValues):
        sortedIndices = np.argsort(fitnessValues)
        rankWeights = np.arange(1, self.populationSize + 1)
        totalRank = np.sum(rankWeights)
        probabilities = rankWeights / totalRank
        cumulativeProbabilities = np.cumsum(probabilities)
        selectedIndices = []
        for _ in range(self.populationSize):
            r = np.random.rand()
            for i, cumulativeProbability in enumerate(cumulativeProbabilities):
                if r < cumulativeProbability:
                    selectedIndices.append(sortedIndices[i])
                    break
        return self.population[selectedIndices]

    def singlePointCrossover(self, parent1, parent2):
        point = np.random.randint(self.n)
        child1 = np.concatenate((parent1[:point], parent2[point:]))
        child2 = np.concatenate((parent2[:point], parent1[point:]))
        return child1, child2

    def doublePointCrossover(self, parent1, parent2):
        point1, point2 = sorted(np.random.randint(1, self.n, 2))
        child1 = np.concatenate((parent1[:point1], parent2[point1:point2], parent1[point2:]))
        child2 = np.concatenate((parent2[:point1], parent1[point1:point2], parent2[point2:]))
        return child1, child2

    def partiallyMappedCrossover(self, parent1, parent2):
        # Losowanie punktów przecięcia
        point1, point2 = sorted(np.random.randint(0, len(parent1), 2))

        # Tworzenie kopii dzieci
        child1, child2 = parent1.copy(), parent2.copy()

        # Mapowanie środkowego segmentu
        child1[point1:point2], child2[point1:point2] = parent2[point1:point2], parent1[point1:point2]
        def fix_mapping(child, parent, point1, point2):
            mapping = {parent[i]: child[i] for i in range(point1, point2)}
            reverse_mapping = {v: k for k, v in mapping.items()}
            for i in range(len(child)):
                # Pomijamy segment środkowy
                if point1 <= i < point2:
                    continue
                # Naprawiamy konflikt w mapowaniu
                while child[i] in reverse_mapping:
                    child[i] = reverse_mapping[child[i]]
            return child
        # Naprawa dzieci
        child1 = fix_mapping(child1, parent1, point1, point2)
        child2 = fix_mapping(child2, parent2, point1, point2)
        if len(set(child1)) != len(child1):
            print(child1, parent1)
            assert False
        if len(set(child2)) != len(child2):
            print(child2, parent2)
            assert False
        return child1, child2

    def mutation(self, individual):
        for i in range(len(individual)):
            if np.random.rand() < self.mutationProbability:
                individual[i] = 1 - individual[i]  # Flip the bit
        return individual

    def mutationTSP(self, individual):
        if np.random.rand() < self.mutationProbability:
            point1, point2 = sorted(np.random.randint(0, len(individual), 2))
            individual[point1:point2] = individual[point1:point2][::-1]  # Reverse the segment
        return individual

    def fit(self, selectionMethod = "roulette", crossoverMethod = "singlePoint"):
        for _ in range(self.T):
            # Evaluate fitness
            fitnessValues = np.array([self.adaptationFunc(ind, *self.adaptationFuncArgs) for ind in self.population])
            self.fitnessHistory.append(np.max(fitnessValues))
            
            # Selection
            if selectionMethod == "roulette":
                selectedPopulation = self.rouletteSelection(fitnessValues)
            elif selectionMethod == "rank":
                selectedPopulation = self.rankSelection(fitnessValues)
            else:
                raise ValueError("No selection method")

            # Crossover
            newPopulation = []
            for i in range(0, self.populationSize, 2):
                parent1, parent2 = selectedPopulation[i], selectedPopulation[i + 1]
                if np.random.rand() < self.crossoverProbability:
                    if crossoverMethod == "singlePoint":
                        child1, child2 = self.singlePointCrossover(parent1, parent2)
                    elif crossoverMethod == "doublePoint":
                        child1, child2 = self.doublePointCrossover(parent1, parent2)
                    else:
                        raise ValueError("No crossover method")
                else:
                    child1, child2 = parent1, parent2
                newPopulation.extend([child1, child2])

            # Mutation
            self.population = np.array([self.mutation(ind) for ind in newPopulation])

        # Return the best individual
        fitnessValues = np.array([self.adaptationFunc(ind, *self.adaptationFuncArgs) for ind in self.population])
        bestIndex = np.argmax(fitnessValues)
        return self.population[bestIndex], fitnessValues[bestIndex]

    def fitTSP(self, selectionMethod="roulette", crossoverMethod="partiallyMapped"):
        bestOverall = None
        bestOverallFitness = np.inf
        avgFitness = 0
        for _ in range(self.T):
            # Evaluate fitness
            fitnessValues = np.array([self.adaptationFunc(ind, *self.adaptationFuncArgs) for ind in self.population])
            self.fitnessHistory.append(np.min(fitnessValues))
            self.fitnessAvg.append(np.mean(fitnessValues))

            currentBest = np.argmin(fitnessValues)
            currentBestFitness = fitnessValues[currentBest]
            if currentBestFitness < bestOverallFitness:
                bestOverallFitness = currentBestFitness
                bestOverall = self.population[currentBest]
            self.fitnessBest.append(bestOverallFitness)

            avgFitness += np.sum(fitnessValues)

            # Selection
            if selectionMethod == "roulette":
                selectedPopulation = self.rouletteSelection(fitnessValues)  # Minimize
            elif selectionMethod == "rank":
                selectedPopulation = self.rankSelection(fitnessValues)  # Minimize
            else:
                raise ValueError("No selection method")

            # Crossover
            newPopulation = []
            for i in range(0, self.populationSize, 2):
                parent1, parent2 = selectedPopulation[i], selectedPopulation[i + 1]
                if np.random.rand() < self.crossoverProbability:
                    if crossoverMethod == "partiallyMapped":
                        child1, child2 = self.partiallyMappedCrossover(parent1, parent2)
                    else:
                        raise ValueError("No crossover method for TSP")
                else:
                    child1, child2 = parent1, parent2
                newPopulation.extend([child1, child2])

            # Mutation
            self.population = np.array([self.mutationTSP(ind) for ind in newPopulation])

        # Return the best individual
        avgFitness = avgFitness / (self.T*self.populationSize)
        fitnessValues = np.array([self.adaptationFunc(ind, *self.adaptationFuncArgs) for ind in self.population])
        bestIndex = np.argmin(fitnessValues)  # Minimize distance
        return self.population[bestIndex], fitnessValues[bestIndex], bestOverall, bestOverallFitness, avgFitness