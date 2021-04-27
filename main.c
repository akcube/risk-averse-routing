#include <include/hash.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int num_intersections, num_streets, num_cars;
   
    scanf("%d%d%d", &num_intersections, &num_streets, &num_cars);

    edge *Edge_Table = (edge *)malloc(MAX_INPUTS * sizeof(edge));

    for (int i = 0; i < MAX_INPUTS; i++)
    {
        Edge_Table[i].edge_name[0] = '\0';
    }

    ReadInput_1 (num_streets,Edge_Table);
}
