#include <stdio.h>
#include <string.h>

typedef struct edge{
    int to;
    int len;
} edge;

#define DATA_TYPE edge
#include "../include/vector.inl"

#define MAX 100010
#define MAXLEN 10000010
vector_edge graph[MAX];

void dijkstra(int st, int* p, int* d, int n){
    int visit[MAX] = {0};
    d[st] = 0;
    for(int i=0;i<n;i++){
        int next = -1;
        for(int j=0;j<n;j++){
            if(visit[j]!=1 && (next==-1 || d[next]>d[j])) next = j;
        }
        if(d[next]==MAXLEN) break;
        visit[next] = 1;
        for(int j=0;j<graph[next].size(&graph[next]);j++){
            edge e = graph[next].get(&graph[next], j);
            int len = e.len;
            int to = e.to;
            if(d[to]>d[next]+len){
                d[to] = d[next] + len;
                p[to] = next;
            }
        }
    }
}
int main(){
    for(int i=0;i<MAX;i++) create_edge_vector(&graph[i] ,2);
    int n,m; scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        edge e1,e2;
        int v1,v2,w;
        scanf("%d %d %d", &v1, &v2, &w);
        v1--;v2--;
        e1.to = v2; e1.len = w;
        e2.to = v1; e2.len = w;
        graph[v1].push_back(&graph[v1], e1);
        graph[v2].push_back(&graph[v2], e2);
    }
    
    int d[n]; int p[n];
    //memset(d, MAX, sizeof(d));
    //memset(p, -1, sizeof(p));
    for(int i=0;i<n;i++){
        d[i] = MAXLEN;
        p[i] = -1; 
    }
    int st; scanf("%d", &st); st--;
    dijkstra(st, p, d, n);
    for(int i=0;i<n;i++) printf("%d ", d[i]);
}
