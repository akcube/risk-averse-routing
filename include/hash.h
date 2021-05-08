#ifndef __HASH
#define __HASH

#define NAME_LEN 10000
#define MAX_INPUTS 100000

// struct to store starting intersection / vertex , ending intersection
// street name and  weight of the street 
// weight refers to number of cars passing a street

typedef struct edge_unit
{
    int start_index, end_index;
    float weight;
    char *edge_name;
} edge;

// Creates a Hash Table of structs

edge *CreateTable();

// Generates hash key for a street name

unsigned long int GetHash(char *name_str);

// inserts data of a struct into hash table

void Insert(int start_index, int end_index, char name[NAME_LEN], edge *Edge_Table);

//Reads indexes and edge name as inputs

void ReadInput_1(int num_streets, edge *Edge_Table, FILE *fptr);

// Reads input to calculate weight of edge

void readpart2(int num_cars, edge *Edge_Table, FILE *fptr);

// Calculates weight of an edge

void AddWeight(char name[NAME_LEN], edge *Edge_Table);

#endif
