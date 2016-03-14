# Cyclical Figurate Numbers

The tactic used to solve this problem was as follows:

1. First find all Figurate Numbers
2. Then form a graph between all the figurate numbers where each number is a vertex and the edges are connections between figurate numbers from the last two numbers matching the first two numbers.
3. Afterwards, find all cycles of lenght 6 in the resulting graph.
4. Find a Bipartite Match of 6 between the sets of figurate numbers and the cycle numbers.

Step 4 was accomplished by reducing the bipartite matching problem into a network flow problem. Afterwards, solve the network flow problm by using the Ford-Fulkerson algorithm.
