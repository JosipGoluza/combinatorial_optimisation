# Homework 1 - Solving the Decision Knapsack Problem Exactly

## Instructions

To have the homework accepted, the following tasks must be accomplished:

### Tasks
1. **Write a program solving the decision version of the 0/1 knapsack problem**:
   - Use a brute force approach (i.e., evaluate all combinations).
   - Any method can be used (iterative, recursion, BFS).
   - Implement the **branch & bound method**.
   - Note: Be careful, it is a decision problem. However, pruning by cost can be used here as well. How? Describe the algorithm in the report.

2. **Perform experimental evaluation**:
   - Use the provided instances (decision versions).
   - Observe the dependency of the computational complexity on the instance size.
   - Measure computational complexity by the number of visited nodes in the decision tree (or the number of recursion calls), not the runtime.
   - There are 500 instances for each instance size. Observe both the average and maximum complexity as a function of the instance size.
   - Note: Do not try to solve the biggest instances now. For this homework, use instances up to the size your computing power allows.

3. **Create summary tables and graphs**:
   - Process the two instance sets (**NR**, **ZR**) separately.
   - Identify and describe any differences you observe.

4. **Frequency analysis**:
   - For at least one instance size (choose instances with at least 10 items), observe the frequency of the measured values.
   - Draw a histogram:
     - **X-axis**: Time complexities.
     - **Y-axis**: Frequency.

5. **Write a report**:
   - Include the measured dependencies.
   - Submit the source code along with the report as a separate "zipped" file.


### Notes
- Nice summary tables and graphs will be appreciated.
- Ensure your report is clear and well-structured.