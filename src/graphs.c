#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/graphs.h"

bool cmpfunc(pair a, pair b){
    return a.second < b.second;
}

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

pair make_pair(int a, int b){
    pair p;
    p.first = a;
    p.second = b;
    return p;
}

void graph_read(Graph *self, FILE *fptr){
    edge *buff = self->roads;
    char *name;
    vector_int *adj = self->adj;
    uint32_t from, slen, temp;
    Hashtable *road_to_id = &(self->road_to_id);
    for(int i=self->edges; i<self->e_lim; i++){
        name = &(self->r_names[self->strl]);
        fscanf(fptr, "%d %d %n%s%n %d", &from, &buff[i].to, &temp, name, &slen, &buff[i].len);
        slen -= temp;
        buff[i].stri = self->strl;
        adj[from].push_back(&adj[from], i);
        road_to_id->insert(road_to_id, name, slen, i);
        if(self->directed){
            buff[i+1].to = from;
            buff[i+1].len = buff[i].len;
            buff[i+1].stri = self->strl;
            from = buff[i].to;
            adj[from].push_back(&adj[from], i+1);
            i++;
        }
        self->strl += slen+1;
    }
}

int *dense_dijkstra(Graph *self, uint32_t s, int *p){
    
    bool *vis = calloc(1, sizeof(bool)*self->size);
    int *dis = malloc(sizeof(int)*self->size);
    const int INFTY = 999999999;
    
    for(int i=0; i<self->size; i++) dis[i] = INFTY;
    
    vector_int *adj = self->adj;
    dis[s] = 0;
    
    if(p) p[s] = s;
    
    for(int j=0;j<n;j++){
		int node = -1;
		for(int i=0;i<n;i++){
			if(vis[i]!=true && (node==-1 || dis[node]>dis[i])){
				node = i;
			}
		}
        vis[node] = true;

        for(int i=0; i<adj[node].size(&adj[node]); i++){
            int e = adj[node].get(&adj[node], i);
            edge ed = self->roads[e];
    
            if(dis[node] + ed.len < dis[ed.to]){
                if(p) p[ed.to] = node;
                dis[ed.to] = dis[node] + ed.len;
            }
        }
    }
    free(vis);
    return dis;
}

int *dijkstra(Graph *self, uint32_t s, pair *p){
    
    bool *vis = calloc(1, sizeof(bool)*self->size);
    int *dis = malloc(sizeof(int)*self->size);
    
    for(int i=0; i<self->size; i++) dis[i] = INFTY;
    
    vector_int *adj = self->adj;
    dis[s] = 0;
    
    heap_pair pq;
    create_pair_heap(self->size, cmpfunc, &pq);
    pq.push(make_pair(s, 0), &pq);
    if(p) p[s].first = s;
    
    while(!pq.empty(&pq)){
        pair top = pq.pop(&pq);
        int node = top.first;
        int curr_d = top.second;
        vis[node] = true;

        if(dis[node] != curr_d) continue;

        for(int i=0; i<adj[node].size(&adj[node]); i++){
            int e = adj[node].get(&adj[node], i);
            edge ed = self->roads[e];
            uint32_t weight = ed.len*10 + ed.traffic*90;
            if(dis[node] + weight < dis[ed.to]){
                if(p){
                    p[ed.to].first = node;
                    p[ed.to].second = e;
                }
                dis[ed.to] = dis[node] + weight;
                pq.push(make_pair(ed.to, dis[ed.to]), &pq);
            }
        }
    }
    free(vis);
    return dis;
}

void output_data(Graph *self, int *dis){
    edge *roads = self->roads;
    char *r_names = self->r_names;

    FILE *fptr = fopen("data/trafficmap.txt", "w+");
    if(!fptr){
        printf("Couldn't create temporary trafficmap. Insufficient memory/permissions.\n");
        exit(0);
    }
    for(int i=0; i<self->size; i++){
        vector_int *adj = self->adj;
        for(int j=0; j < adj[i].size(&adj[i]); j++){
            uint32_t idx = adj[i].get(&adj[i], j);
            uint32_t stri = roads[idx].stri;
            uint32_t traffic = ((double)roads[idx].traffic/self->max_traffic)*100;
            fprintf(fptr, "%d %d %s %d %d\n", i, roads[idx].to, &(r_names[stri]), roads[idx].len, traffic);
            fflush(fptr);
        }
    }
}

void assign_weights(Graph *self, uint32_t cars, FILE *fptr){
    uint32_t path_len, temp, slen;
    char road[32];
    Hashtable *road_to_id = &(self->road_to_id);
    for(int i=0; i<cars; i++){
        fscanf(fptr, "%d", &path_len);
        for(int i=0; i<path_len; i++){
            fscanf(fptr, " %n%s%n", &temp, road, &slen);
            slen -= temp;
            uint32_t idx = road_to_id->get(road_to_id, road, slen);
            self->roads[idx].traffic++;
            if(self->directed)
                self->roads[idx+1].traffic++;
            self->max_traffic = max(self->max_traffic, self->roads[idx].traffic++);
        }
    }
}

char *getRoadName(Graph *self, uint32_t e){
    uint32_t stri = self->roads[e].stri;
    return &(self->r_names[stri]);
}

void create_graph(Graph *self, uint32_t n, uint32_t m, bool directed){
    self->size = n;
    self->edges = 0;
    self->e_lim = m;
    self->max_traffic = 0;
    if(directed) self->e_lim *= 2;
    self->strl = 0;
    self->adj = calloc(n, sizeof(vector_int));
    self->r_names = calloc(1, 32 * self->e_lim);
    self->roads = calloc(1, sizeof(edge) * self->e_lim);
    self->directed = directed;

    for(int i=0; i<n; i++) 
        create_int_vector(&self->adj[i], 4);
    create_hash_table(&self->road_to_id, (m<<1));

    self->read = graph_read;
    self->dijkstra = dijkstra;
    self->read_weights = assign_weights;
    self->output = output_data;
    self->getRoadName = getRoadName;
}

