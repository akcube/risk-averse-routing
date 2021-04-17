# Routing 
You have to develop risk averse routing algorithms on simulated city maps.

## Major Steps
You shall be expected to complete the following tasks:

1. Make a program to read in and manipulate graphs, take input from a file, etc. This should support insertion and deletion of edged, finding adjacency lists, finding the weight of an edge, etc.

2. Implement Dijkstra’s algorithm to find the shortest path between two nodes on the graph. Write tests for this algorithm and try it out on some sample city maps (hypothetical maps as graphs).

3. Use simulated traffic data, and estimate the weights of edges for fastest routing. Here you need to either manufacture data from a simulation or use the Google Hash Code 2021 traffic data (download-able from https://codingcompetitions.withgoogle.com/hashcode/archive), or preferably both.

4. Formulate a definition of congestion and safe routing. Use your new objectives to enhance your Dijkstra's algorithm. This formulation is left to your mathematical creativity and understanding of probabilistic modeling of roads. It can be as simple or complex as you want.

### Additional objectives:
1. Try to visualize the graphs you plot and the traffic on them using some graphing library. (C may not be the language of choice for this) 
2. See if you can get real world data from Google maps to test out if your heuristics work and research on better heuristics.


