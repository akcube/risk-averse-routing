# risk-averse-routing
A risk averse routing algorithms on simulated city maps.

## Pre-requisites
You need to have python3 with matplotlib, networkx and scipy installed beforehand.
If not installed, run the following commands
1. `sudo apt-get install python3`
2. `sudo apt-get install python3-pip`
3. `pip3 install matplotlib`
4. `pip3 install networkx`
5. `pip3 install scipy`

## Usage

Clone the repo, and cd into it
Run:
1. `make`
2. `./routing [-d/-u] <inputfile.txt>`

Example: `./routing -d ../traffic-data/b.txt`

## Arguments
1. `-d` specifies that the graph input is for a directed graph
2. `-u` specifies that the graph input is for an undirected graph
3. Pass the name of the input file as a parameter as well after the `-d/-u` flag

 **NOTE**: Sample test cases are found in the `traffic-data/` directory.

## How to use the program

Upon launch the program will ask you for your desired source and destination vertex.
Once input is given it will enter interactive mode. 
Type, 

**Advance path**

> `n` will show the path to be taken from the current node along the shortest path to the destination node

**Show the entire path**

> `e` will list out all the paths to be taken from the current node to the destination node

**Visualize the map**

> `g` will graph the entire map according to mapped traffic data and will highlight the path covered so far with bold edges