#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int vals[1000];
    int f;
    int r;
} Queue;


void create_queue(Queue* q) {
    q->f = 0;
    q->r = -1;
}

bool is_empty(Queue* q) {
    return q->f > q->r;
}

void enqueue(Queue* q, int val) {
    q->vals[++q->r] = val;
}

int dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->vals[q->f++];
}

int peek(Queue* q){
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->vals[q->f];
}

void print_queue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = q->f; i <= q->r; i++) {
        printf("%d ", q->vals[i]);
    }
    printf("\n");
}