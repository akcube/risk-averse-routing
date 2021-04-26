#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 10000
#define MAX_INPUTS 100000

typedef struct edge_unit
{
    int start_index, end_index;
    int weight;
    char edge_name[NAME_LEN];
} edge;

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
       
        if (!Edge_Table[key].start_index)
        {
            strcpy(Edge_Table[key].edge_name, name);
            Edge_Table[key].start_index = start_index;
            Edge_Table[key].end_index = end_index;
            return;
        }
    }
}

int main(void)
{
    int num_intersections, num_streets, num_cars;
    int start, end;
    unsigned long int key;
    char name[NAME_LEN];
    scanf("%d%d%d", &num_intersections, &num_streets, &num_cars);

    edge *Edge_Table = (edge *)malloc(MAX_INPUTS * sizeof(edge));

    for (int i = 0; i < MAX_INPUTS; i++)
    {
        Edge_Table[i].edge_name[0] = '\0';
    }

    for (int i = 0; i < num_streets; i++)
    {
        scanf("%d%d", &start, &end);
        scanf(" %s", name);
       
        Insert(start, end, name, Edge_Table);
    }
}