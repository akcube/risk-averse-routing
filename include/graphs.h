#ifndef __CGRAPH_SUPPORT_LIB
#define __CGRAPH_SUPPORT_LIB

#include <stdint.h>

typedef struct edge{
    uint32_t to;
    uint32_t len;
    uint32_t stri;
} edge;

typedef struct pair{
	int first;
	int second;
} pair;

pair make_pair(int a, int b);

#include "hash.h"

#define DATA_TYPE int
#include "vector.inl"

#define DATA_TYPE pair
#include "heaps.inl"

typedef struct Graph{
	vector_int *adj;
	char *r_names;
	edge *roads;
	Hashtable road_to_id;
	uint32_t size;
	uint32_t edges;
	uint32_t e_lim;
	uint32_t strl;
	bool directed;

	void (*read)(struct Graph *self);
	int* (*dijkstra)(struct Graph *self, uint32_t s, int *p);
	void (*read_weights)(struct Graph *self, uint32_t cars);
} Graph;

void create_graph(Graph *self, uint32_t n, uint32_t m, bool directed);

#endif