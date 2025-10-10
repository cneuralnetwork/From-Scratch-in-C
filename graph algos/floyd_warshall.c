#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10
#define INF 99999

struct Edge {
    int dest;
    int weight;
    struct Edge* next;
};

struct Graph {
    int numVertices;
    struct Edge** adjLists;
};

struct Edge* createEdge(int dest, int weight) {
    struct Edge* newEdge = malloc(sizeof(struct Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Edge*));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Edge* newEdge = createEdge(dest, weight);
    newEdge->next = graph->adjLists[src];
    graph->adjLists[src] = newEdge;
}

void floydWarshall(struct Graph* graph) {
    int vertices = graph->numVertices;
    int dist[MAX_VERTICES][MAX_VERTICES];
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }
    
    for (int i = 0; i < vertices; i++) {
        struct Edge* temp = graph->adjLists[i];
        while (temp) {
            dist[i][temp->dest] = temp->weight;
            temp = temp->next;
        }
    }
    
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF) {
                printf("%7s", "INF");
            } else {
                printf("%7d", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    struct Graph* graph = createGraph(4);
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 3, 10);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 2, 3, 1);
    
    floydWarshall(graph);
    
    return 0;
}
