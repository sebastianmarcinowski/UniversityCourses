from GA import *
# Generate a TSP problem
cities = 10
distanceMatrix = generateTSP(cities)
path, dist = solveTSP(distanceMatrix)
print("Optimal Path:", path)
print("Optimal Distance:", dist)

# Define the adaptation function
def adaptationTSP(path, distanceMatrix):
    return TSP(distanceMatrix, path)

# Initialize GA
gaTSP = GA(
    n=cities,
    adaptationFunc=adaptationTSP,
    adaptationFuncArgs=(distanceMatrix,),
    populationSize=100,
    T=200,
    crossoverProbability=0.9,
    mutationProbability=0.1,
    problem="TSP"
)

# Run GA
bestPath, bestDistance, bestOverallPath, bestOverallDistance, avgFitness = gaTSP.fitTSP(selectionMethod="roulette", crossoverMethod="partiallyMapped")
print("Best Path in current population:", bestPath)
print("Best Distance in current population:", bestDistance)
print("Best Path Overall:", bestOverallPath)
print("Best Distance Overall:", bestOverallDistance)
print("Average Distance:", avgFitness)

# Plot Fitness
plotFitnessTSP(gaTSP.fitnessHistory, gaTSP.fitnessAvg, gaTSP.fitnessBest,"roulette", "partiallyMapped")