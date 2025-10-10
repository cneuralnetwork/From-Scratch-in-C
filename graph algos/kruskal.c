#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 20

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int vertices, edges;
    struct Edge edge[MAX_EDGES];
};

int find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return find(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    
    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void kruskalMST(struct Graph* graph) {
    int vertices = graph->vertices;
    struct Edge result[vertices];
    int e = 0;
    int i = 0;
    
    qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compare);
    
    int parent[vertices];
    int rank[vertices];
    
    for (int v = 0; v < vertices; v++) {
        parent[v] = v;
        rank[v] = 0;
    }
    
    while (e < vertices - 1 && i < graph->edges) {
        struct Edge next_edge = graph->edge[i++];
        
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        
        if (x != y) {
            result[e++] = next_edge;
            unionSet(parent, rank, x, y);
        }
    }
    
    printf("Kruskal's Minimum Spanning Tree:\n");
    printf("Edge \tWeight\n");
    int totalWeight = 0;
    for (i = 0; i < e; ++i) {
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total MST weight: %d\n", totalWeight);
}

int main() {
    struct Graph graph;
    graph.vertices = 4;
    graph.edges = 5;
    
    graph.edge[0].src = 0;
    graph.edge[0].dest = 1;
    graph.edge[0].weight = 10;
    
    graph.edge[1].src = 0;
    graph.edge[1].dest = 2;
    graph.edge[1].weight = 6;
    
    graph.edge[2].src = 0;
    graph.edge[2].dest = 3;
    graph.edge[2].weight = 5;
    
    graph.edge[3].src = 1;
    graph.edge[3].dest = 3;
    graph.edge[3].weight = 15;
    
    graph.edge[4].src = 2;
    graph.edge[4].dest = 3;
    graph.edge[4].weight = 4;
    
    kruskalMST(&graph);
    
    return 0;
}
