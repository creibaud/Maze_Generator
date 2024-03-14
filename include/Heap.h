/******************************************************************************************
 * @file Heap.h
 * @brief This file contains the declarations of the MinHeap data structure and related 
 * functions.
 ******************************************************************************************/

#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/******************************************************************************************
 * @struct MinHeapNode
 * @brief Represents a node in the MinHeap.
 ******************************************************************************************/
typedef struct {
    int idNode;                                   /**< The ID of the node. */
    int cost;                                     /**< The cost associated with the node. */
} MinHeapNode;

/******************************************************************************************
 * @struct MinHeap
 * @brief Represents a MinHeap data structure.
 ******************************************************************************************/
typedef struct {
    int size;               /**< The current size of the MinHeap. */
    int capacity;           /**< The maximum capacity of the MinHeap. */
    int *positions;         /**< An array to store the positions of nodes in the MinHeap. */
    MinHeapNode **nodes;    /**< An array of MinHeapNode pointers. */
} MinHeap;

/******************************************************************************************
 * @brief Creates a new MinHeapNode with the given ID and cost.
 * @param idNode The ID of the node.
 * @param cost The cost associated with the node.
 * @return A pointer to the newly created MinHeapNode.
 ******************************************************************************************/
MinHeapNode *createMinHeapNode(int idNode, int cost);

/******************************************************************************************
 * @brief Creates a new MinHeap with the given capacity.
 * @param capacity The maximum capacity of the MinHeap.
 * @return A pointer to the newly created MinHeap.
 ******************************************************************************************/
MinHeap *createMinHeap(int capacity);

/******************************************************************************************
 * @brief Frees the memory allocated for the given MinHeap.
 * @param minHeap Pointer to the MinHeap to be freed.
 ******************************************************************************************/
void freeMinHeap(MinHeap *minHeap);

/******************************************************************************************
 * @brief Swaps two MinHeapNode pointers.
 * @param a Pointer to the first MinHeapNode pointer.
 * @param b Pointer to the second MinHeapNode pointer.
 ******************************************************************************************/
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b);

/******************************************************************************************
 * @brief Restores the MinHeap property starting from the given node index.
 * @param minHeap Pointer to the MinHeap.
 * @param idNode The index of the node to start heapify from.
 ******************************************************************************************/
void minHeapify(MinHeap *minHeap, int idNode);

/******************************************************************************************
 * @brief Checks if the MinHeap is empty.
 * @param minHeap Pointer to the MinHeap.
 * @return True if the MinHeap is empty, false otherwise.
 ******************************************************************************************/
bool isMinHeapEmpty(MinHeap *minHeap);

/******************************************************************************************
 * @brief Extracts the node with the minimum cost from the MinHeap.
 * @param minHeap Pointer to the MinHeap.
 * @return A pointer to the MinHeapNode with the minimum cost.
 ******************************************************************************************/
MinHeapNode *extractMinHeapNode(MinHeap *minHeap);

/******************************************************************************************
 * @brief Decreases the cost of the node with the given ID in the MinHeap.
 * @param minHeap Pointer to the MinHeap.
 * @param idNode The ID of the node.
 * @param newCost The new cost for the node.
 ******************************************************************************************/
void decreaseMinHeapNodeCost(MinHeap *minHeap, int idNode, int newCost);

/******************************************************************************************
 * @brief Checks if the node with the given ID is present in the MinHeap.
 * @param minHeap Pointer to the MinHeap.
 * @param idNode The ID of the node.
 * @return True if the node is present in the MinHeap, false otherwise.
 ******************************************************************************************/
bool isInMinHeap(MinHeap *minHeap, int idNode);

#endif // HEAP_H