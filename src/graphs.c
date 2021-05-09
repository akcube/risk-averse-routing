#include <stdio.h>
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

void graph_read(Graph *self){
    edge *buff = self->roads;
    char *name;
    vector_int *adj = self->adj;
    uint32_t from, slen, temp;
    Hashtable *road_to_id = &(self->road_to_id);
    for(int i=self->edges; i<self->e_lim; i++){
        name = &(self->r_names[self->strl]);
        scanf("%d %d %n%s%n %d", &from, &buff[i].to, &temp, name, &slen, &buff[i].len);
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

int *dijkstra(Graph *self, uint32_t s, int *p){
    
    bool *vis = calloc(1, sizeof(bool)*self->size);
    int *dis = malloc(sizeof(int)*self->size);
    const int INFTY = 999999999;
    
    for(int i=0; i<self->size; i++) dis[i] = INFTY;
    
    vector_int *adj = self->adj;
    dis[s] = 0;
    
    heap_pair pq;
    create_pair_heap(self->size, cmpfunc, &pq);
    pq.push(make_pair(s, 0), &pq);
    if(p) p[s] = s;
    
    while(!pq.empty(&pq)){
        pair top = pq.pop(&pq);
        int node = top.first;
        int curr_d = top.second;
        vis[node] = true;

        if(dis[node] != curr_d) continue;

        for(int i=0; i<adj[node].size(&adj[node]); i++){
            int e = adj[node].get(&adj[node], i);
            edge ed = self->roads[e];
    
            if(dis[node] + ed.len < dis[ed.to]){
                if(p) p[ed.to] = node;
                dis[ed.to] = dis[node] + ed.len;
                pq.push(make_pair(ed.to, dis[ed.to]), &pq);
            }
        }
    }
    free(vis);
    return dis;
}

