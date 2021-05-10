#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../include/graphs.h"

#define DATA_TYPE pair
#include "../include/vector.inl"

 /*   *   *   *   *   *   *
Team 35:

# Risk averse routing

Arguments
    -d specifies that the graph input is for a directed graph
    -u specifies that the graph input is for an undirected graph
    Pass the name of the input file as a parameter as well after the -d/-u flag

Upon launch the program will ask you for your desired source and destination vertex. 
Once input is given it will enter interactive mode.

Advance path
    'n' will show the path to be taken from the current node along the 
    shortest path to the destination node

Show the entire path
    'e' will list out all the paths to be taken from the current node to 
    the destination node

Visualize the map
    'g' will graph the entire map according to mapped traffic data and will highlight 
    the path covered so far with bold edges
*   *   *   *   *   *   *   */

//Error handles scanf input
void check_scanf(int CODE){
    if(CODE <= 0){
        char ch = getchar();
        if(ch=='q' || ch=='Q') exit(0);
        printf("Invalid input. Error.\n");
        exit(0);
    }
}

FILE* create_path_file(bool undirected){
    //Resets path file for safety
    remove("src/data/path.txt");
    FILE *pathptr = fopen("src/data/path.txt", "a");
    if(!pathptr){
        printf("Couldn't create temporary trafficmap. Insufficient memory/permissions.\n");
        exit(0);
    }

    //Sets up path file
    fprintf(pathptr, "%d\n", !undirected);
    return pathptr;
}

int main(int argc, char *argv[])
{
    // Define allowable arguments
    char *filters = "du";

    // Ensure proper usage
    char filter = getopt(argc, argv, filters);
    if (filter == '?' || filter == -1 || argc != optind + 1){
        fprintf(stderr, "Invalid arguments. \nUsage: ./routing [directed/undirected] inputfile.\n");
        return 1;
    }

    bool undirected, isRouting = false;
    // Choose graph type
    switch (filter){
        case 'u':
            undirected = true;
            break;
        case 'd':
            undirected = false;
            break;
    }

    // Remember filename
    char *infile = argv[optind];
    // Open input file
    FILE *fptr;
    fptr = fopen(infile, "r"); 
    if(fptr==NULL){
        fprintf(stderr, "Unable to open input file.\n");
        return 2;
    }

    // Read input
    // intersections : no. of nodes
    // roads: no. of edges
    // cars: amount of traffic data
    int intersections, roads, cars, source, destination;
    char yes_no = 0;

    // Read in file header input
    int RET_CODE;
    RET_CODE = fscanf(fptr, "%*d %d %d %d %*d", &intersections, &roads, &cars);
    check_scanf(RET_CODE);

    //Create graph
    Graph G;
    create_graph(&G, intersections, roads, undirected);
    G.read(&G, fptr);
    G.read_weights(&G, cars, fptr);

    //Will store path after dijkstra
    vector_pair path;
    create_pair_vector(&path, 5);

    //Outputs traffic data for graph visualizer
    G.output(&G);

    FILE *pathptr;
    do{
        //If routing not in progress ask for input
        if(!isRouting){
            printf("Source vertex: ");
            RET_CODE = scanf("%d", &source);
            check_scanf(RET_CODE);
            printf("Destination vertex: ");
            RET_CODE = scanf("%d", &destination);
            check_scanf(RET_CODE);
            pair *p = calloc(1, sizeof(pair)*intersections);

            //Run dijkstra and pick complexity dynamically
            int *dis;
            if(G.e_lim <= G.size*G.size/12)
                dis = G.dijkstra(&G, source, p);
            else
                dis = G.dense_dijkstra(&G, source, p);

            isRouting = true;

            //Setup path vector or say no path exists
            if(dis[destination] != INFTY){
                pair i;
                for(i=p[destination]; i.first != source; i=p[i.first]){
                    path.push_back(&path, i);
                }
                path.push_back(&path, i);
                path.reverse(&path);

                pathptr = create_path_file(undirected);
                for(int i=0; i<path.size(&path); i++){
                    fprintf(pathptr, "%d ", path.get(&path, i).first);
                }

                fprintf(pathptr, "%d ", destination);
                fflush(pathptr);
                path.reverse(&path);
                isRouting = true;       
            }
            else{
                printf("No such route exists. Try again.\n\n");
                isRouting = false;
            }
        }
        else{
            // Enter interactive mode
            printf("(routing) ");

            if(path.size(&path) <= 0){
                isRouting = false;
                printf("You have arrived at your destination.\n\n");
                continue;
            }

            RET_CODE = scanf(" %c", &yes_no);
            check_scanf(RET_CODE);

            // Give interactive output according to user input
            pair road;
            switch(yes_no){
                case 'n':
                case 'N':
                    road = path.pop_back(&path);
                    uint32_t stri = G.roads[road.second].stri;
                    printf("\nFrom node %d, travel via %s for %dm", road.first, &G.r_names[stri], G.roads[road.first].len);
                    printf(" [%d paths left to cover.]\n\n", path.size(&path));
                break;

                case 'e':
                case 'E':
                    while(path.size(&path) > 0){
                        road = path.pop_back(&path);
                        uint32_t stri = G.roads[road.second].stri;
                        printf("\nFrom node %d, travel via %s for %dm", road.first, &G.r_names[stri], G.roads[road.first].len);
                        printf(" [%d paths left to cover.]\n\n", path.size(&path));
                        }
                    break;
                case 'g':
                    system("python3 src/viz_random.py");
                    break;
                case 'G':
                    system("python3 src/viz_kamada.py");
                    break;
            }
        }
    }while(yes_no != 'q' && yes_no != 'Q');
    
    fclose(pathptr);
    destroy_graph(&G);
}
