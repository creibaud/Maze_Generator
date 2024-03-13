#include "../include/Prim.h"

int minCostIndex(int *cost, bool *mstSet, int numNodes) {
    int min = INT_MAX;
    int minIndex;

    for (int v = 0; v < numNodes; v++) {
        if (mstSet[v] == false && cost[v] < min) {
            min = cost[v];
            minIndex = v;
        }
    }

    return minIndex;
}

PrimResult *prim(Graph* graph) {
    int *predecessors = (int*)malloc(graph->numNodes * sizeof(int));
    int *costs = (int*)malloc(graph->numNodes * sizeof(int));
    bool *visited = (bool*)malloc(graph->numNodes * sizeof(bool));
    int totalCost = 0;

    for (int i = 0; i < graph->numNodes; i++) {
        costs[i] = INT_MAX;
        visited[i] = false;
    }

    costs[0] = 0;
    predecessors[0] = -1;

    for (int _ = 0; _ < graph->numNodes - 1; _++) {
        int currentNodeIndex = minCostIndex(costs, visited, graph->numNodes);
        visited[currentNodeIndex] = true;

        Node* temp = graph->adjList[currentNodeIndex].headNode;
        while (temp != NULL) {
            int v = temp->idDestinationNode;
            if (visited[v] == false && temp->cost < costs[v]) {
                predecessors[v] = currentNodeIndex;
                costs[v] = temp->cost;
                totalCost += temp->cost;
            }
            temp = temp->nextNode;
        }
    }

    printMST(graph, predecessors, costs);

    PrimResult *result = (PrimResult *)malloc(sizeof(PrimResult));
    result->predecessors = predecessors;
    result->totalCost = totalCost;

    return result;
}

PrimResult *primHeap(Graph* graph) {
    int *predecessors = (int*)malloc(graph->numNodes * sizeof(int));
    int *costs = (int*)malloc(graph->numNodes * sizeof(int));
    MinHeap *minHeap = createMinHeap(graph->numNodes);
    int totalCost = 0;

    for (int i = 0; i < graph->numNodes; i++) {
        predecessors[i] = -1;
        costs[i] = INT_MAX;
        minHeap->nodes[i] = createMinHeapNode(i, costs[i]);
        minHeap->positions[i] = i;
    }

    int startNodeId = 0;
    costs[startNodeId] = 0;
    minHeap->nodes[startNodeId] = createMinHeapNode(startNodeId, costs[startNodeId]);
    minHeap->positions[startNodeId] = startNodeId;
    minHeap->size = graph->numNodes;

    while (!isMinHeapEmpty(minHeap)) {
        MinHeapNode *currentNode = extractMinHeapNode(minHeap);
        int currentNodeIndex = currentNode->idNode;

        Node* temp = graph->adjList[currentNodeIndex].headNode;
        while (temp != NULL) {
            int idDestinationNode = temp->idDestinationNode;
            if (isInMinHeap(minHeap, idDestinationNode) && temp->cost < costs[idDestinationNode]) {
                costs[idDestinationNode] = temp->cost;
                totalCost += temp->cost;
                predecessors[idDestinationNode] = currentNodeIndex;
                decreaseMinHeapNodeCost(minHeap, idDestinationNode, costs[idDestinationNode]);
            }
            temp = temp->nextNode;
        }
    }

    printMST(graph, predecessors, costs);

    PrimResult *result = (PrimResult *)malloc(sizeof(PrimResult));
    result->predecessors = predecessors;
    result->totalCost = totalCost;
    
    return result;
}

void printMST(Graph* graph, int *predecessors, int *costs) {
    printf("\n%*sMST\n", 16, "");
    printf("\033[33;92m-----------------------------------\033[0m\n");
    printf("\033[33;92m|\033[0m \033[33;33mSources\033[0m \033[33;92m|\033[0m \033[33;33mDestinations\033[0m \033[33;92m|\033[0m \033[33;33mWeight\033[0m \033[33;92m|\033[0m\n");
    printf("\033[33;92m-----------------------------------\033[0m\n");

    for (int i = 1; i < graph->numNodes; i++) {
        printf("\033[33;92m|\033[0m %-7d \033[33;92m|\033[0m %-12d \033[33;92m|\033[0m %-6d \033[33;92m|\033[0m\n", predecessors[i], i, costs[i]);
    }

    printf("\033[33;92m-----------------------------------\033[0m\n");
}