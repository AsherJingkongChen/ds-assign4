# Study the Properties of "Small World" and Compare Different Data Structures

*Due: 1/17 23:59:59*

1. Generate a cycle of 1000 nodes. Each edge has length 1.
2. Add X random edges. Each random edge has the same length Y. 
3. Sample Z pairs of source and destination, and compute the average shortest distance (D) of these Z source-destination pairs.

You need to use 2 different structures of heaps. **(In the report, give the name of the data structures that you use, e.g., array and binomial heap).**

**Your report should contain:**

1. A picture of the graph with X = 100.
2. Responses to the following questions: 
    - What is the relationship between X and D? 
    - What is the relationship between Y and D?
    - How to choose Z to obtain a reasonable approximation of the true average shortest distance between all pairs of source and destination?
    - Which implementation of Dijkstra's Algorithm is faster?

**You need to support your answers with experimental results.** 
**You also need to explain how you obtain the results.**
