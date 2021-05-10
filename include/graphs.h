#ifndef __CGRAPH_SUPPORT_LIB
#define __CGRAPH_SUPPORT_LIB

#include <stdint.h>

// Edge in the graph
typedef struct edge{
    uint32_t to;
    uint32_t len;
    uint32_t traffic;
    uint32_t stri;
} edge;

typedef struct pair{
	int first;
	int second;
} pair;

#define INFTY 999999999

pair make_pair(int a, int b);

#include "hash.h"

#define DATA_TYPE int
#include "vector.inl"

#define DATA_TYPE pair
#include "heaps.inl"

// Graph structure containg actual adjacency list of graph, hashtable
// for names of edges, function pointers and other information about the graph
typedef struct Graph{
	vector_int *adj;
	char *r_names;
	edge *roads;
	Hashtable road_to_id;
	uint32_t size;
	uint32_t edges;
	uint32_t e_lim;
	uint32_t strl;
	uint32_t max_traffic;
	bool directed;

	void (*read)(struct Graph *self, FILE *fptr);
	int* (*dijkstra)(struct Graph *self, uint32_t s, pair *p);
	void (*read_weights)(struct Graph *self, uint32_t cars, FILE *fptr);
	void (*output)(struct Graph *self, int *dis);
	char* (*getRoadName)(struct Graph *self, uint32_t edge);
	int* (*dense_dijkstra)(struct Graph *self, uint32_t s, pair *p);

} Graph;

void create_graph(Graph *self, uint32_t n, uint32_t m, bool directed);
void destroy_graph(Graph *self);

#endif
