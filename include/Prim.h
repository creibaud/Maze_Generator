/**
 * @file Prim.h
 * @brief Header file for Prim's algorithm implementation.
 * 
 * This file contains the declarations of functions and structures related to Prim's algorithm.
 * Prim's algorithm is used to find the minimum spanning tree (MST) of a graph.
 */

#ifndef PRIM_H
#define PRIM_H

#include "Graph.h"
#include "Heap.h"
#include <limits.h>
#include <stdbool.h>

/**
 * @struct PrimResult
 * @brief Structure to store the result of Prim's algorithm.
 * 
 * This structure contains the predecessors array and the total cost of the MST.
 */
typedef struct {
    int *predecessors;                  /**< Array of predecessors for each node in the MST. */
    int totalCost;                      /**< Total cost of the minimum spanning tree. */
} PrimResult;

/**
 * @brief Find the index of the node with the minimum cost that is not yet included in the MST.
 * 
 * This function takes an array of costs and a boolean array indicating whether a node is already
 * included in the MST. It returns the index of the node with the minimum cost that is not yet included
 * in the MST.
 * 
 * @param cost The array of costs for each node.
 * @param mstSet The boolean array indicating whether a node is already included in the MST.
 * @param numNodes The number of nodes in the graph.
 * @return The index of the node with the minimum cost that is not yet included in the MST.
 */
int minCostIndex(int *cost, bool *mstSet, int numNodes);

/**
 * @brief Find the minimum spanning tree (MST) of a graph using Prim's algorithm.
 * 
 * This function takes a graph and returns the minimum spanning tree (MST) using Prim's algorithm.
 * It uses an adjacency matrix representation of the graph.
 * 
 * @param graph The graph for which to find the MST.
 * @return A pointer to the PrimResult structure containing the MST.
 */
PrimResult *prim(Graph* graph);

/**
 * @brief Find the minimum spanning tree (MST) of a graph using Prim's algorithm with a heap.
 * 
 * This function takes a graph and returns the minimum spanning tree (MST) using Prim's algorithm.
 * It uses a binary heap to efficiently find the node with the minimum cost.
 * 
 * @param graph The graph for which to find the MST.
 * @return A pointer to the PrimResult structure containing the MST.
 */
PrimResult *primHeap(Graph* graph);

/**
 * @brief Print the minimum spanning tree (MST) of a graph.
 * 
 * This function takes a graph, an array of predecessors, and an array of costs, and prints the minimum
 * spanning tree (MST) of the graph.
 * 
 * @param graph The graph for which to print the MST.
 * @param predecessors The array of predecessors for each node in the MST.
 * @param costs The array of costs for each node in the MST.
 */
void printMST(Graph* graph, int *predecessors, int *costs);

#endif // PRIM_H