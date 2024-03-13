#include <assert.h>
#include "Prim.h"

void testMinCostIndex() {
    int cost[] = {5, 2, 7, 3, 1};
    bool mstSet[] = {true, false, false, false, false};
    int numNodes = 5;

    int minIndex = minCostIndex(cost, mstSet, numNodes);
    assert(minIndex == 4);
}

void testPrim() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 1);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 1, 4, 4);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 4, 3);

    PrimResult* result = prim(graph);

    assert(result->totalCost == 9);

    assert(result->predecessors[0] == -1);
    assert(result->predecessors[1] == 0);
    assert(result->predecessors[2] == 1);
    assert(result->predecessors[3] == 0);
    assert(result->predecessors[4] == 3);

    free(result->predecessors);
    free(result);
}

void testPrimHeap() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 1);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 1, 4, 4);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 4, 3);

    PrimResult* result = primHeap(graph);

    assert(result->totalCost == 9);

    assert(result->predecessors[0] == -1);
    assert(result->predecessors[1] == 0);
    assert(result->predecessors[2] == 1);
    assert(result->predecessors[3] == 0);
    assert(result->predecessors[4] == 3);

    free(result->predecessors);
    free(result);
}

int main() {
    printf("\nTest Prim\n");

    testMinCostIndex();
    testPrim();

    printf("All tests passed!\n");

    printf("\nTest PrimHeap\n");

    testPrimHeap();

    printf("All tests passed!\n");

    return 0;
}