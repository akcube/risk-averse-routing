#include <include/hash.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *fptr;
    FILE *ptr;
    int num_intersections, num_streets, num_cars,garbage1,garbage2;

    char input[50];
    printf("Enter the input file name\n");
    scanf("%s", input);
    fptr = fopen(input, "r");
    fscanf(fptr, "%d", &garbage1);
    fscanf(fptr, "%d", &num_intersections);
    fscanf(fptr, "%d", &num_streets);
    fscanf(fptr, "%d", &num_cars);
    fscanf(fptr, "%d", &garbage2);
    
    edge *Edge_Table = CreateTable();

    ReadInput_1(num_streets, Edge_Table, fptr);

    readpart2(num_cars, Edge_Table, fptr);

    Traffic_Output(Edge_Table, ptr);

    fclose(ptr);
    fclose(fptr);
}
