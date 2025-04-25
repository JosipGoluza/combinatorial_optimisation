# Homework 5 - MAX-SAT Solution Using an Advanced Iterative Method

## Problem Definition

Given a Boolean formula **F** having **n** variables, \( X = (x_1, x_2, \dots, x_n) \), in a Conjunctive Normal Form (CNF), and integer weights of the **n** variables \( W = (w_1, w_2, \dots, w_n) \), your task is to find an assignment \( Y = (y_1, y_2, \dots, y_n) \) of input variables \( x_1, x_2, \dots, x_n \) such that:

- \( F(Y) = 1 \) (the formula evaluates to true), and
- The sum \( S \) of weights of variables set to 1 is maximized.

### Notes:
- It is highly suggested to reduce the problem to the **weighted 3-SAT problem**, where each clause consists of exactly 3 variables (literals). The complexity of this problem is the same, but it is easier to program.
- The provided instances are already in 3-SAT format.

---

## Example

Let \( n = 4 \), \( F = (x_1 + x_3' + x_4) \cdot (x_1' + x_2 + x_3') \cdot (x_3 + x_4) \cdot (x_1 + x_2 + x_3' + x_4') \cdot (x_2' + x_3) \cdot (x_3' + x_4') \), and \( W = (2, 4, 1, 6) \).

### Feasible Configurations:
- \( X = \{0, 0, 0, 1\}, S = 6 \)
- \( X = \{1, 0, 0, 1\}, S = 2 + 6 = 8 \) (optimum solution)
- \( X = \{1, 1, 1, 0\}, S = 2 + 4 + 1 = 7 \)

### DIMACS CNF Format:
The above instance is described as follows:
c CNF Example c 4 variables, 6 clauses c each clause is terminated by '0' (not by the end of line) p cnf 4 6 1 -3 4 0 -1 2 -3 0 3 4 0 1 2 -3 -4 0 -2 3 0 -3 -4 0

### MWCNF Format:
For this homework, we use the **MWCNF** format:
c MWCNF Example c 4 variables, 6 clauses c each clause is terminated by '0' (not by the end of line) p mwcnf 4 6 c zero-terminated weights follow w 2 4 1 6 0 1 -3 4 0 -1 2 -3 0 3 4 0 1 2 -3 -4 0 -2 3 0 -3 -4 0


---

## Instructions

Solve the MAX-SAT problem using one of the following advanced iterative heuristics:

- **Simulated Annealing**
- **Genetic Algorithm**
- **Tabu Search**

### Key Objectives:
1. **Parameter Adjustment**:
   - Experiment with and determine optimum and universal (adaptive) parameter settings.
   - Verify the properties of the heuristic through experimental evaluation.

2. **Efficiency Evaluation**:
   - Document the efficiency of the heuristic, especially when using non-standard techniques.
   - Answer questions such as:
     - Does the algorithm return satisfactory solutions?
     - Does it work for instances of any size? How does the error grow with instance size?
     - Does the algorithm converge correctly and have sufficient iterative power?
     - Is the algorithm adequately fast? Can it be stopped earlier to avoid unnecessary overhead?

3. **Adaptive Mechanisms**:
   - Use reasonable adaptive mechanisms to improve performance.

---

## Report Requirements

Your report should document your rational approach to the problem, including:

1. **White-Box Testing**:
   - Efficient parameter adjustment process.

2. **Black-Box Testing**:
   - Final experimental evaluation.

3. **Experimental Results**:
   - Present results in a compact form (e.g., tables, graphs).
   - Justify any non-standard approaches with experimental evidence.

4. **Discussion and Conclusions**:
   - Summarize findings and insights.

5. **Source Code**:
   - Include the source code for your implementation.


## Evaluation

This homework is part of the final exam and is worth **up to 28 points out of 100**.

### Key Evaluation Criteria:
- **Experimental Results**:
  - The experimental part is the most important.
  - Present results clearly and concisely using tables and graphs.
- **Implementation**:
  - Implementation aspects are of minor concern but should be well-documented.
- **Non-Standard Approaches**:
  - Justify any non-standard techniques with experiments.

### Ideal Outcome:
An algorithm capable of solving a wide spectrum of instances with reasonable error and efficiency.
