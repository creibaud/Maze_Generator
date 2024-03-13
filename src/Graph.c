#include "../include/Graph.h"

Node* createNode(int idDestinationNode, int cost) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->idDestinationNode = idDestinationNode;
    newNode->cost = cost;
    newNode->nextNode = NULL;

    return newNode;
}

Graph *createGraph(int numNodes) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;

    graph->adjList = (AdjList*)malloc(numNodes * sizeof(AdjList));
    for (int i = 0; i < numNodes; i++) {
        graph->adjList[i].headNode = NULL;
    }

    return graph;
}

void addEdge(Graph *graph, int idSourceNode, int idDestinationNode, int cost) {
    Node* newNode = createNode(idDestinationNode, cost);
    newNode->nextNode = graph->adjList[idSourceNode].headNode;
    graph->adjList[idSourceNode].headNode = newNode;

    newNode = createNode(idSourceNode, cost);
    newNode->nextNode = graph->adjList[idDestinationNode].headNode;
    graph->adjList[idDestinationNode].headNode = newNode;
}

void printGraph(Graph *graph) {
    int lineLength = snprintf(NULL, 0, "| Edge | %*s Adjacent List %*s |\n", graph->numNodes / 2, "", graph->numNodes / 2, "");
    printf("\n%*sGraph\n", (lineLength - 5) / 2, "");

    printf("\033[33;92m");
    for (int i = 0; i < lineLength - 1; i++) {
        printf("-");
    }
    printf("\033[0m\n");

    printf("\033[33;92m|\033[0m \033[33;33mEdge\033[0m \033[33;92m|\033[0m %*s \033[33;33mAdjacent List\033[0m %*s \033[33;92m|\033[0m\n", graph->numNodes / 2, "", graph->numNodes / 2, "");

    printf("\033[33;92m");
    for (int i = 0; i < lineLength - 1; i++) {
        printf("-");
    }
    printf("\033[0m\n");

    for (int i = 0; i < graph->numNodes; i++) {
        Node* temp = graph->adjList[i].headNode;
        printf("\033[33;92m|\033[0m %4d \033[33;92m|\033[0m \033[33;33m->\033[0m", i);
        int lengthChar = 3;
        while (temp) {
            printf(" %d\033[33;96m(%d)\033[0m", temp->idDestinationNode, temp->cost);
            lengthChar += snprintf(NULL, 0, " %d(%d)", temp->idDestinationNode, temp->cost);
            temp = temp->nextNode;
        }
        printf("%*s \033[33;92m|\033[0m\n", 16 + graph->numNodes - lengthChar, "");
    }

    printf("\033[33;92m");
    for (int i = 0; i < lineLength - 1; i++) {
        printf("-");
    }
    printf("\033[0m\n");
}