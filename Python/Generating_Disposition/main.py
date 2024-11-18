import BigramsHandling as bg
import numpy as np
import QAP as qap
from collections import defaultdict, Counter

# Load bigram list and define constants
bigram_list = bg.Pdist(bg.datafile('count_2l.txt'))
alphabet = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
            "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
            "w", "x", "y", "z"]
alphabet_size = len(alphabet)

# Create Flow Matrix based on bigram list
flow_matrix = np.zeros((alphabet_size, alphabet_size), dtype=int)
for idx1, letter1 in enumerate(alphabet):
    for idx2, letter2 in enumerate(alphabet[idx1+1:], start=idx1+1):
        bigram_left = letter1 + letter2
        bigram_right = letter2 + letter1
        flow_value = bigram_list(bigram_left) + bigram_list(bigram_right)
        flow_matrix[idx1, idx2] = flow_value
        flow_matrix[idx2, idx1] = flow_value

# Define Distance Matrix
A = np.ones((6, 6), dtype=int)
B = np.ones((5, 5), dtype=int)
C = np.ones((6, 5), dtype=int) * 2
E = np.ones((5, 6), dtype=int) * 2
F = np.ones((5, 5), dtype=int) * 2
distance_matrix = np.block([
    [A, C, C, C, C],
    [E, B, F, F, F],
    [E, F, B, F, F],
    [E, F, F, B, F],
    [E, F, F, F, B]
])

# Parameters for finding and storing solutions
max_solutions = 10
target_cost = 2.15e13 - 1
solutions = []
costs = []

# Loop to find multiple solutions
while len(solutions) < max_solutions:
    solution, cost, solving_time = qap.solve_qap(distance_matrix, flow_matrix)
    print(f"Solution found with cost {cost:.2e}")
    if cost < target_cost:
        print("Solution meets cost threshold and is saved.")
        solutions.append(solution)
        costs.append(cost)

# Display collected solutions and their costs
print("\nCollected Solutions:")
for i, (sol, cost) in enumerate(zip(solutions, costs)):
    print(f"Solution {i+1} with cost {cost:.2e}: {sol}")

# Compute the "best solution" as an average of the 10 solutions
location_counts = [Counter() for _ in range(alphabet_size)]

# Count occurrences of each letter at each location across solutions
for solution in solutions:
    for location, letter_index in enumerate(solution):
        location_counts[location][letter_index] += 1

# Generate the "best solution" by choosing the most frequent unique letter at each location
assigned_letters = set()
best_solution = [None] * alphabet_size

for location, loc_count in enumerate(location_counts):
    # Find the most common letter for this location that hasn't been assigned yet
    for letter_index, _ in loc_count.most_common():
        if letter_index not in assigned_letters:
            best_solution[location] = letter_index
            assigned_letters.add(letter_index)
            break

# Display the "best solution" using the alphabet
print("\nBest Solution (Average of Collected Solutions):")
for loc, letter_index in enumerate(best_solution):
    print(f"Location {loc}: {alphabet[letter_index]}")

# Final output of the "best solution" in alphabetical format
print("\nFinal Best Solution in Alphabetical Format:")
print([alphabet[i] for i in best_solution])
