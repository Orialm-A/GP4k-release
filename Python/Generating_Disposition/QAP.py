import time
import numpy as np
from deap import base, creator, tools, algorithms
import multiprocessing

# Define the QAP objective function
def qap_cost(individual, D, F):
    return sum(D[i][j] * F[individual[i]][individual[j]] for i in range(len(D)) for j in range(len(D))),


# Initialize the DEAP toolbox for GA
def setup_toolbox(D, F):
    creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
    creator.create("Individual", list, fitness=creator.FitnessMin)

    toolbox = base.Toolbox()
    toolbox.register("indices", np.random.permutation, len(D))
    toolbox.register("individual", tools.initIterate, creator.Individual, toolbox.indices)
    toolbox.register("population", tools.initRepeat, list, toolbox.individual)

    toolbox.register("evaluate", qap_cost, D=D, F=F)
    toolbox.register("mate", tools.cxPartialyMatched)
    toolbox.register("mutate", tools.mutShuffleIndexes, indpb=0.05)
    toolbox.register("select", tools.selTournament, tournsize=6)

    return toolbox


# Function to solve QAP with GA
def solve_qap(D, F):
    toolbox = setup_toolbox(D, F)
    population = toolbox.population(n=400)  # Population size
    halloffame = tools.HallOfFame(1)
    stats = tools.Statistics(lambda ind: ind.fitness.values)
    stats.register("avg", np.mean)
    stats.register("min", np.min)

    with multiprocessing.Pool() as pool:
        toolbox.register("map", pool.map)
        start_time = time.time()
        algorithms.eaSimple(population, toolbox, cxpb=0.9, mutpb=0.4, ngen=400,  # Number of generations
                            stats=stats, halloffame=halloffame, verbose=False)
        end_time = time.time()

    best_solution = halloffame[0]
    best_cost = best_solution.fitness.values[0]
    elapsed_time = end_time - start_time

    return best_solution, best_cost, elapsed_time
