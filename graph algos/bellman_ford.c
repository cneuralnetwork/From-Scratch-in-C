#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_EDGES 20
#define MAX_VERTICES 10

struct Edge {
    int src, dest, weight;
};

void bellmanFord(struct Edge edges[], int vertices, int edgeCount, int src) {
    int dist[MAX_VERTICES];
    
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    
    for (int i = 0; i < vertices - 1; i++) {
        for (int j = 0; j < edgeCount; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    for (int j = 0; j < edgeCount; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }
    
    printf("Vertex distances from source %d:\n", src);
    for (int i = 0; i < vertices; i++) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
}

int main() {
    int vertices = 5;
    int edgeCount = 8;
    
    struct Edge edges[MAX_EDGES] = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };
    
    bellmanFord(edges, vertices, edgeCount, 0);
    
    return 0;
}
