#ifndef __HASH
#define __HASH

#define NAME_LEN 10000
#define MAX_INPUTS 100000

typedef struct edge_unit
{
    int start_index, end_index;
    float weight;
    char edge_name[NAME_LEN];
} edge;

unsigned long int GetHash(char *name_str) ;

void Insert(int start_index, int end_index, char name[NAME_LEN], edge *Edge_Table);

void ReadInput_1 (int num_streets, edge* Edge_Table);

#endif