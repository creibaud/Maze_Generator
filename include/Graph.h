/**
 * @file Graph.h
 * @brief This file contains the declarations of the Graph data structure and related functions.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Node
 * @brief Represents a node in the graph.
 */
typedef struct Node {
    int idDestinationNode;          /**< The ID of the destination node. */
    int cost;                       /**< The cost of the edge to the destination node. */
    struct Node* nextNode;          /**< Pointer to the next node in the adjacency list. */
} Node;

/**
 * @struct AdjList
 * @brief Represents the adjacency list for a node in the graph.
 */
typedef struct {
    Node *headNode;                 /**< Pointer to the head node of the adjacency list. */
} AdjList;

/**
 * @struct Graph
 * @brief Represents the graph.
 */
typedef struct {
    int numNodes;                   /**< The number of nodes in the graph. */
    AdjList* adjList;               /**< Pointer to the array of adjacency lists. */
} Graph;

/**
 * @brief Creates a new node with the given destination node ID and cost.
 * @param idDestinationNode The ID of the destination node.
 * @param cost The cost of the edge to the destination node.
 * @return Pointer to the newly created node.
 */
Node* createNode(int idDestinationNode, int cost);

/**
 * @brief Creates a new graph with the given number of nodes.
 * @param numNodes The number of nodes in the graph.
 * @return Pointer to the newly created graph.
 */
Graph* createGraph(int numNodes);

/**
 * @brief Destroys the given graph and frees the memory.
 * @param graph Pointer to the graph to be destroyed.
 */
void destroyGraph(Graph* graph);

/**
 * @brief Adds an edge between the source node and the destination node with the given cost.
 * @param graph Pointer to the graph.
 * @param idSourceNode The ID of the source node.
 * @param idDestinationNode The ID of the destination node.
 * @param cost The cost of the edge.
 */
void addEdge(Graph* graph, int idSourceNode, int idDestinationNode, int cost);

/**
 * @brief Prints the graph.
 * @param graph Pointer to the graph to be printed.
 */
void printGraph(Graph* graph);

#endif // GRAPH_H