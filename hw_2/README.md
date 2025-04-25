# Homework 2 - Exact and Heuristic Solutions of the Knapsack Problem

## Instructions

### Tasks
1. **Branch & Bound Method**:
   - Write a program solving the optimization version of the 0/1 knapsack problem using the branch & bound method.
   - Note: The problem is now an optimization problem, so there will be slight differences from Homework 1.

2. **Simple Cost/Weight Heuristic**:
   - Write a program solving the optimization version of the 0/1 knapsack problem using the simple cost/weight heuristic (see Lecture 4).
   - Observe:
     - Run-time.
     - Average and maximum errors for each instance size.

3. **Modified Cost/Weight Heuristic**:
   - Write a program solving the optimization version of the 0/1 knapsack problem using the modified (extended) cost/weight heuristic (see Lecture 4).
   - Observe:
     - Average and maximum errors for each instance size.
   - Compare these errors with the simple heuristic.

4. **Dynamic Programming**:
   - Write a program solving the optimization version of the 0/1 knapsack problem using dynamic programming.
   - Choose between decomposition by:
     - Knapsack capacity.
     - Total cost.
   - Observe:
     - Run-time as a function of the instance size.
   - Compare run-time with:
     - Branch & Bound from Homework 1.
     - Simple cost/weight heuristic.

5. **FPTAS Approximation Algorithm**:
   - Write a program solving the 0/1 knapsack problem using an FPTAS approximation algorithm.
   - Observe:
     - Dependency of the algorithm run-time and relative error (maximum, average) on the chosen precision.
   - Suggested instance size: 40 (or all instance sizes).
   - Note:
     - The FPTAS algorithm can be obtained by modifying the dynamic programming algorithm based on decomposition by total cost.
     - Decomposition by knapsack capacity **cannot** be used here, as the FPTAS property cannot be guaranteed.
   - Hint:
     - Exclude items with a higher weight than the knapsack capacity at the beginning of the algorithm.
     - Otherwise, the cost division factor may grow immensely, increasing the error.

### Testing
- Test the algorithms on the provided knapsack instances (optimization versions: **NK**, **ZKC**, **ZKW**).
- Conduct experiments on all these sets (processing all instances is not necessary, especially for B&B).
- Observe any differences in the benchmark sets.

---

### Notes
- For this homework, it is recommended to measure **run-time** instead of the number of configurations, as different algorithms are being compared.
- For specific purposes (e.g., comparison of similar algorithms), measuring the number of configurations is still acceptable.

---

## Report Requirements

The report should include:

1. **Descriptions of the Implemented Algorithms**:
   - Provide a clear explanation of each algorithm.

2. **Comparison of Run-Times**:
   - Compare the run-times of:
     - Branch & Bound.
     - Dynamic programming.
     - Cost/weight heuristic.

3. **Comparison of Relative Errors**:
   - Compare the average and maximum relative errors of:
     - Simple heuristic.
     - Extended heuristic.

4. **FPTAS Analysis**:
   - Include:
     - Measured run-times.
     - Maximum and average relative error dependencies on the instance size.
     - Comparison of the maximum allowed (set) and real (measured) maximum relative errors for selected precisions.

5. **Discussion and Conclusions**:
   - Summarize findings and insights.
