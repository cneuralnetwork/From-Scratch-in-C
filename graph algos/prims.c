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

int minKey(int key[], bool mstSet[], int vertices) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < vertices; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int key[], int vertices) {
    printf("Edge \tWeight\n");
    int totalWeight = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, key[i]);
        totalWeight += key[i];
    }
    printf("Total MST weight: %d\n", totalWeight);
}

void primMST(struct Graph* graph) {
    int vertices = graph->numVertices;
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];

    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minKey(key, mstSet, vertices);
        mstSet[u] = true;

        struct AdjListNode* crawl = graph->adjLists[u];
        while (crawl != NULL) {
            int v = crawl->dest;
            int weight = crawl->weight;
            if (!mstSet[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
            crawl = crawl->next;
        }
    }

    printMST(parent, key, vertices);
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

int main() {
    int vertices = 5;
    struct Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);

    printf("Prim's Minimum Spanning Tree:\n");
    primMST(graph);

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
