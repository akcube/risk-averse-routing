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
    unsigned long hash = 5381;

    int c;
    int size = strlen(name_str);
    for (int i = 0; i < size; i++)
        hash = ((hash << 5) + hash) + (c = *name_str++); 

    return hash;
}
void AddWeight(char name[NAME_LEN], edge *Edge_Table)
{
    unsigned long int hash_name, key;
    hash_name = GetHash(name);

    for (int k = 0; k < MAX_INPUTS; k++)
    {
        key = (hash_name + k * k) % MAX_INPUTS;
       
        if (strcmp(Edge_Table[key].edge_name, name)==0)
        {
            Edge_Table[key].weight=Edge_Table[key].weight+1/10;
            return;
        }
    }
}
void readpart2(int num_cars,edge *Edge_Table)
{
   int path; 
   char name_street[NAME_LEN];
   for(int i=0;i<num_cars;i++)
   {
      scanf("%d",path);
      for(int j=0;j<path;j++)
      {
          scanf("%s",name_street);
          AddWeight(name_street,Edge_Table);
      }
   }
}
