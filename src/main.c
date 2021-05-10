#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../include/graphs.h"

#define DATA_TYPE pair
#include "../include/vector.inl"

 /*   *   *   *   *   *   *

    num_intersections stores number of nodes / vertices in a graph 
    num_streets stores number of edges in a graph
    num_cars stores number of cars

    garbage1 and garbage2 are for storing first and last input values in the data (not used in the code)
    input array stores the input file name 

    yes_no is used to know whether the user wants to continue the program or exit 
    decision is used to know whether the user wants to continue with the same input file 
    flag is used for calling the functions to take a new input file if the decision is yes 

    Edge_Table stores starting vertex , ending vertex , name of the edge and weight of the edge
    location1 stores the starting location vertex 
    location2 stores the destination vertex

*   *   *   *   *   *   *   */

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

    bool directed, isRouting = false;
    // Choose graph type
    switch (filter){
        case 'd':
            directed = true;
            break;
        case 'u':
            directed = false;
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
    int intersections, roads, cars, source, destination;
    char yes_no = 0;
    fscanf(fptr, "%*d %d %d %d %*d", &intersections, &roads, &cars);

    Graph G;
    create_graph(&G, intersections, roads, directed);
    G.read(&G, fptr);
    G.read_weights(&G, cars, fptr);

    vector_pair path;
    create_pair_vector(&path, 5);

    G.output(&G, NULL);

    remove("data/path.txt");
    FILE *pathptr = fopen("data/path.txt", "a");
    if(!pathptr){
        printf("Couldn't create temporary trafficmap. Insufficient memory/permissions.\n");
        exit(0);
    }

    fprintf(pathptr, "%d 0\n", directed);
    do{
        if(!isRouting){
            printf("Source vertex: ");
            scanf("%d", &source);
            printf("Destination vertex: ");
            scanf("%d", &destination);
            pair *p = calloc(1, sizeof(pair)*intersections);
            int *dis = G.dijkstra(&G, source, p);
            isRouting = true;

            if(dis[destination] != INFTY){
                pair i;
                for(i=p[destination]; i.first != source; i=p[i.first]){
                    path.push_back(&path, i);
                }
                path.push_back(&path, i);
                fprintf(pathptr, "%d ", path.pop_back(&path).first);
                fflush(pathptr);
                isRouting = true;       
            }
            else{
                printf("No such route exists. Try again.\n");
                isRouting = false;
            }
        }
        else{
            // Asks whether the user want to continue the program or exit it
            printf("(routing) ");

            if(path.size(&path) <= 0){
                isRouting = false;
                printf("You have arrived at your destination.\n");
                continue;
            }

            scanf(" %c", &yes_no);
            pair road;
            switch(yes_no){
                case 'n':
                case 'N':
                    road = path.pop_back(&path);
                    fprintf(pathptr, "%d ", road.first);
                    uint32_t stri = G.roads[road.second].stri;
                    printf("\nFrom node %d, travel via %s for %dm", road.first, &G.r_names[stri], G.roads[road.first].len);
                    printf(" [%d paths left to cover.]\n", path.size(&path));
                    fflush(pathptr);
                break;

                case 'e':
                case 'E':
                    while(path.size(&path) > 0){
                        road = path.pop_back(&path);
                        fprintf(pathptr, "%d ", road.first);
                        uint32_t stri = G.roads[road.second].stri;
                        printf("\nFrom node %d, travel via %s for %dm", road.first, &G.r_names[stri], G.roads[road.first].len);
                        printf(" [%d paths left to cover.]\n", path.size(&path));
                        fflush(pathptr);
                    }
                    break;
                case 'g':
                case 'G':
                    system("python3 viz_kamada.py");
                break;
            }
        }
    }while(yes_no != 'q' && yes_no != 'Q');
}
