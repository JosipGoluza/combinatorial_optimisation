# Homework 4 - Solving the Knapsack Problem by an Advanced Iterative Method

## Motivation

The aim of this homework is to familiarize yourself with one of the advanced heuristics by solving a simple Knapsack problem. By experimenting with the parameters of the heuristic, you will gain a better understanding of its principles and behavior. 

In **Homework 5** (part of the exam), you will solve a much more difficult problem (weighted max-SAT). Completing this homework will help you make better decisions in the next one.

---

## Possible Algorithm Choices

You can choose one of the following advanced heuristics:

- **Simulated Annealing**
- **Genetic Algorithm**
- **Tabu Search**

---

## Instructions

1. **Choose an Advanced Heuristic**:
   - Select one of the advanced heuristics to solve the 0/1 Knapsack problem.

2. **Implement the Heuristic**:
   - Write a program implementing the chosen heuristic.

3. **Experiment with Parameters**:
   - Test different algorithm parameters, such as:
     - **Simulated Annealing**: Initial temperature, cooling schedule.
     - **Genetic Algorithm**: Crossover and mutation rate, elitism, selection pressure.
     - **Tabu Search**: Tabu attributes, tabu tenure, aspiration criteria.

4. **Evaluate Algorithm Efficiency**:
   - Observe:
     - **Runtime**.
     - **Relative error** of the solutions obtained.
   - Conduct experiments using:
     - Standard problem instances (preferably the largest ones).
     - Randomly generated instances (with at least 30 variables).

5. **Achieve Near-Optimal Results**:
   - For the Knapsack problem and a well-tuned heuristic, you should almost always reach the optimum or a slightly suboptimal result.
   - Note: The runtime may be relatively high.

6. **Optimize Parameters**:
   - Determine optimal and universal (flexible) parameter settings.
   - Consider scalability with instance size and possible adaptation mechanisms.

---

## Report Requirements

Your report should include:

1. **Algorithm Description**:
   - Provide a clear explanation of the chosen heuristic.

2. **Experimental Results**:
   - Analyze the influence of individual parameters on:
     - Runtime.
     - Result quality.

3. **Iterative Power**:
   - Measure and discuss the iterative power of the heuristic.

4. **Discussion and Conclusions**:
   - Summarize your findings and insights.

5. **Source Code**:
   - Include a link to the source code.

---

### Notes
- Ensure your report is clear and well-structured.
- Use graphs and tables to present results effectively.