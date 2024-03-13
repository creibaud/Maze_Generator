/**
 * @file Load.h
 * @brief This file contains the declarations of the functions used to load a graph from a file.
 */

#ifndef LOAD_H
#define LOAD_H

#include "Maze.h"

/**
 * @struct FileLoaded
 * @brief Represents the loaded file data.
 */
typedef struct {
    int width;                      /**< The width of the loaded graph. */
    int height;                     /**< The height of the loaded graph. */
    Graph *graph;                   /**< The graph loaded from the file. */
} FileLoaded;

/**
 * @brief Loads a graph from a file.
 * 
 * @param filename The name of the file to load.
 * @return A pointer to the loaded file data.
 */
FileLoaded *loadGraph(char *filename);

#endif // LOAD_H