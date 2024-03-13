/**
 * @file Maze.h
 * @brief This file contains the declarations of the functions used to create and print a maze.
 */

#ifndef MAZE_H
#define MAZE_H

#include "Prim.h"
#include <string.h>

/**
 * @brief Structure representing a maze.
 */
typedef struct {
    int width;                      /**< Width of the maze. */
    int height;                     /**< Height of the maze. */
    bool **matrix;                  /**< 2D matrix representing the maze. */
} Maze;

/**
 * @brief Creates a maze based on a given graph and dimensions.
 *
 * @param graph The graph used to generate the maze.
 * @param width The width of the maze.
 * @param height The height of the maze.
 * @param typePrim The type of Prim's algorithm to use.
 * @return A pointer to the created maze.
 */
Maze *createMaze(Graph *graph, int width, int height, char *typePrim);

/**
 * @brief Prints the maze as a PPM image file.
 *
 * @param maze The maze to print.
 * @param filename The name of the PPM image file.
 */
void printPPM(Maze *maze, char *filename);

/**
 * @brief Prints the maze to the console.
 *
 * @param maze The maze to print.
 */
void printMaze(Maze *maze);

#endif // MAZE_H