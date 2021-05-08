#include "../include/hash.h"
#include <string.h>
#include <stdio.h>

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

void ReadInput_1(int num_streets, edge *Edge_Table, FILE *fptr)
{
    int start, end, time;
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
void Traffic_Output(edge *Edge_Table, FILE *ptr)
{
    printf("Enter the output file name\n");
    char output[50];
    scanf("%s", output);
    ptr = freopen(output, "w", stdout);
    ptr = freopen(output, "a", stdout);
    fprintf(ptr, "Start\tEnd \tStreetName\tWeight\n\n");
    for (int i = 0; i < MAX_INPUTS; i++)
    {
        if (Edge_Table[i].edge_name[0] != '\0')
            fprintf(ptr, "%d\t\t%d\t\t%s\t\t%g\n", Edge_Table[i].start_index, Edge_Table[i].end_index, Edge_Table[i].edge_name, Edge_Table[i].weight);
    }
}