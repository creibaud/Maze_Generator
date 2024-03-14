#include "../include/Heap.h"

MinHeapNode *createMinHeapNode(int idNode, int cost) {
    MinHeapNode *minHeapNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    minHeapNode->idNode = idNode;
    minHeapNode->cost = cost;

    return minHeapNode;
}


MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->positions = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->nodes = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    for (int i = 0; i < capacity; i++) {
        minHeap->nodes[i] = createMinHeapNode(i, INT_MAX);
        minHeap->positions[i] = i;
    }

    return minHeap;
}

void freeMinHeap(MinHeap *minHeap) {
    free(minHeap->positions);
    free(minHeap->nodes);
    free(minHeap);
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
    MinHeapNode *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *minHeap, int idNode) {
    int smallest = idNode;
    int left = 2 * idNode + 1;
    int right = 2 * idNode + 2;

    if (left < minHeap->size && minHeap->nodes[left]->cost < minHeap->nodes[smallest]->cost) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->nodes[right]->cost < minHeap->nodes[smallest]->cost) {
        smallest = right;
    }

    if (smallest != idNode) {
        MinHeapNode *smallestNode = minHeap->nodes[smallest];
        MinHeapNode *indexNode = minHeap->nodes[idNode];

        minHeap->positions[smallestNode->idNode] = idNode;
        minHeap->positions[indexNode->idNode] = smallest;

        swapMinHeapNode(&minHeap->nodes[smallest], &minHeap->nodes[idNode]);
        minHeapify(minHeap, smallest);
    }
}

bool isMinHeapEmpty(MinHeap *minHeap) {
    return minHeap->size == 0;
}

MinHeapNode *extractMinHeapNode(MinHeap *minHeap) {
    if (isMinHeapEmpty(minHeap)) {
        return NULL;
    }

    MinHeapNode *rootNode = minHeap->nodes[0];
    MinHeapNode *lastNode = minHeap->nodes[minHeap->size - 1];

    minHeap->nodes[0] = lastNode;
    minHeap->positions[rootNode->idNode] = minHeap->size - 1;
    minHeap->positions[lastNode->idNode] = 0;

    minHeap->size--;
    minHeapify(minHeap, 0);

    return rootNode;
}

void decreaseMinHeapNodeCost(MinHeap *minHeap, int idNode, int newCost) {
    int idCurrentNode = minHeap->positions[idNode];
    minHeap->nodes[idCurrentNode]->cost = newCost;

    while (idCurrentNode && minHeap->nodes[idCurrentNode]->cost < minHeap->nodes[(idCurrentNode - 1) / 2]->cost) {
        minHeap->positions[minHeap->nodes[idCurrentNode]->idNode] = (idCurrentNode - 1) / 2;
        minHeap->positions[minHeap->nodes[(idCurrentNode - 1) / 2]->idNode] = idCurrentNode;
        swapMinHeapNode(&minHeap->nodes[idCurrentNode], &minHeap->nodes[(idCurrentNode - 1) / 2]);

        idCurrentNode = (idCurrentNode - 1) / 2;
    }
}

bool isInMinHeap(MinHeap *minHeap, int idNode) {
    if (minHeap->positions[idNode] < minHeap->size) {
        return true;
    }

    return false;
}