#include <assert.h>
#include "../include/Heap.h"


int main() {
    printf("\nTest Heap\n");

    MinHeap *heap = createMinHeap(50);

    for (int i = 0; i < 50; i++) {
        heap->nodes[i] = createMinHeapNode(i, i);
        heap->positions[i] = i;
        heap->size++;
    }

    for (int i = 50 / 2 - 1; i >= 0; i--) {
        minHeapify(heap, i);
    }

    for (int i = 0; i < 50; i++) {
        MinHeapNode *node = extractMinHeapNode(heap);
        assert(node->idNode == i && node->cost == i);
    }

    free(heap->nodes);
    free(heap->positions);
    free(heap);

    return 0;
}