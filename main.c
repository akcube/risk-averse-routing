#include <include/hash.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int num_intersections, num_streets, num_cars;
   
    scanf("%d%d%d", &num_intersections, &num_streets, &num_cars);

    edge *Edge_Table = CreateTable();
    
    ReadInput_1 (num_streets,Edge_Table);
}
