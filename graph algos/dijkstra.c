#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 10

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct Graph {
    int numVertices;
    struct AdjListNode* adjLists[MAX_VERTICES];
};

struct AdjListNode* createNode(int dest, int weight) {
    struct AdjListNode* newNode = malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

int minDistance(int dist[], bool sptSet[], int vertices) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < vertices; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(struct Graph* graph, int src) {
    int vertices = graph->numVertices;
    int dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, sptSet, vertices);
        if (u == -1) break;
        sptSet[u] = true;
        struct AdjListNode* crawl = graph->adjLists[u];
        while (crawl != NULL) {
            int v = crawl->dest;
            int weight = crawl->weight;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
            crawl = crawl->next;
        }
    }
    printf("Vertex distances from source %d:\n", src);
    for (int i = 0; i < vertices; i++) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

int main() {
    int vertices = 6;
    struct Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);

    dijkstra(graph, 0);

    for (int i = 0; i < vertices; i++) {
        struct AdjListNode* current = graph->adjLists[i];
        while (current) {
            struct AdjListNode* tmp = current;
            current = current->next;
            free(tmp);
        }
    }
    free(graph);

    return 0;
}
