#ifndef __HASH
#define __HASH

#define NAME_LEN 10000
#define MAX_INPUTS 100000

typedef struct edge_unit
{
    int start_index, end_index;
    float weight;
    char *edge_name;
} edge;

unsigned long int GetHash(char *name_str);

void Insert(int start_index, int end_index, char name[NAME_LEN], edge *Edge_Table);

void ReadInput_1(int num_streets, edge *Edge_Table, FILE *fptr);

void AddWeight(char name[NAME_LEN], edge *Edge_Table);

void readpart2(int num_cars, edge *Edge_Table, FILE *fptr);

edge *CreateTable();

void Traffic_Output(edge *Edge_Table, FILE *ptr);

#endif
