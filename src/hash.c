#include "../include/hash.h"
#include <string.h>
#include <stdio.h>

// Generates a key for an edge using Street name (String Hashing)

unsigned long int GetHash(char *name_str)
{
    // unsigned long hash = 0 ;
    // int str_size = strlen(name_str);

    // for(int j = 1 ; j < str_size ; j++)
    // {
    //     hash = hash * 33 + (name_str[j]);
    // }

    // return hash;

    // unsigned long hash = 5381;
    // int c;

    // while (c = *name_str++)
    //     hash = ((hash << 5) + hash) + c;

    // return hash;

    unsigned long hash = 5381;

    int c;
    int size = strlen(name_str);
    for (int i = 0; i < size; i++)
        hash = ((hash << 5) + hash) + (c = *name_str++);

    return hash;
}

// Inserts start index , end index and name of a edge / street into hash table
// Inserts into table by performing Quadratic hashing

void Insert(int start_index, int end_index, char name[NAME_LEN], edge *Edge_Table)
{
    unsigned long int hash_name, key;
    hash_name = GetHash(name);

    for (int k = 0; k < MAX_INPUTS; k++)
    {
        key = (hash_name + k * k) % MAX_INPUTS;

        if (Edge_Table[key].edge_name[0] == '\0')
        {
            strcpy(Edge_Table[key].edge_name, name);
            Edge_Table[key].start_index = start_index;
            Edge_Table[key].end_index = end_index;
            return;
        }
    }
}

// Creates a Hash table for storing starting and ending vertex of an edge along with edge name and weight of edge .

edge *CreateTable()
{
    edge *table;
    table = (edge *)malloc(MAX_INPUTS * sizeof(edge));
    for (int i = 0; i < MAX_INPUTS; i++)
    {
        table[i].edge_name = (char *)malloc(sizeof(char) * NAME_LEN);
        table[i].edge_name[0] = '\0';
        table[i].weight = 0;
    }
    return table;
}

// Takes number of edges , Hash Table and Pointer to input file as arguments
// Takes starting vertex , ending vertex and street name from input file and inserts them into hash table .

void ReadInput_1(int num_streets, edge *Edge_Table, FILE *fptr)
{
    int start, end, time; //time is not used anywhere (input data has time , took input to avoid errors )
    char name[NAME_LEN];

    for (int i = 0; i < num_streets; i++)
    {
        fscanf(fptr, "%d", &start);
        fscanf(fptr, "%d", &end);
        fscanf(fptr, "%s", name);
        fscanf(fptr, "%d", &time);
        Insert(start, end, name, Edge_Table);
    }
}
