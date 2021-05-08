#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hash.h"
#define NAME_LEN 10000
#define MAX_INPUTS 100000

void AddWeight(char name[NAME_LEN], edge *Edge_Table)
{
    unsigned long int hash_name, key;
    hash_name = GetHash(name);

    for (int k = 0; k < MAX_INPUTS; k++)
    {
        key = (hash_name + k * k) % MAX_INPUTS;

        if (strcmp(Edge_Table[key].edge_name, name) == 0)
        {
            Edge_Table[key].weight = Edge_Table[key].weight + 0.1;
            return;
        }
    }
}
void readpart2(int num_cars, edge *Edge_Table, FILE *fptr)
{
    int path;
    char name_street[NAME_LEN];
    for (int i = 0; i < num_cars; i++)
    {
        fscanf(fptr, "%d", &path);
        for (int j = 0; j < path; j++)
        {
            fscanf(fptr, "%s", name_street);
            AddWeight(name_street, Edge_Table);
        }
    }
}
