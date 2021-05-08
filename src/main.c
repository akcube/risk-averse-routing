#include <include/hash.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
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

    int num_intersections, num_streets, num_cars, garbage1, garbage2;
    char input[50];
    char yes_no;
    char decision;
    bool flag = false;
    edge *Edge_Table;
    int location1, location2;

    while (1)
    {
        // flag is false when user wants to give new set of input .
        if (flag == false)
        {
            FILE *fptr;
            printf("Enter the input file name\n");
            scanf("%s", input);
            fptr = fopen(input, "r");
            fscanf(fptr, "%d", &garbage1);
            fscanf(fptr, "%d", &num_intersections);
            fscanf(fptr, "%d", &num_streets);
            fscanf(fptr, "%d", &num_cars);
            fscanf(fptr, "%d", &garbage2);

            //Creates an struct array to store start index , end index , name of street and weight of street

            Edge_Table = CreateTable();

            //Reads the start index , end index and street name from a file
            //Takes pointer to input file as argument along with number of edges and Edgetable

            ReadInput_1(num_streets, Edge_Table, fptr);

            //Reads the street names from input file and calculates weights of each edge

            readpart2(num_cars, Edge_Table, fptr);

            fclose(fptr);
        }

        //Takes the starting location and destination from user and finds the shortest path

        printf("Enter starting location\n");
        scanf("%d", &location1);
        printf("Enter destination\n");
        scanf("%d", &location2);

        //call dijkstra here

        // Asks whether the user want to continue the program or exit it
        printf("Do you want to continue?(Y/N)\n");
        scanf(" %c", &yes_no);

        //if yes

        if (yes_no == 'Y')
        {
            // Asks the user if he wants to continue with the same input file

            printf("Do you want to continue with same input data?(Y/N)\n");
            scanf(" %c", &decision);

            if (decision == 'Y')
                flag = true;
            else
            {
                flag = false;
                FreeTable(Edge_Table);
            }
        }

        // if no , frees the edgetable and exits the program
        if (yes_no == 'N')
        {
            FreeTable(Edge_Table);
            exit(0);
        }
    }
}
