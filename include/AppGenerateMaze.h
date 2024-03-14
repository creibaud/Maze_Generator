/******************************************************************************************
 * @file AppGenerateMaze.h
 * @brief This file contains the declarations of the functions used to generate a maze.
 ******************************************************************************************/

#ifndef APP_GENERATE_MAZE_H
#define APP_GENERATE_MAZE_H

#include <dirent.h>
#include "Load.h"

/******************************************************************************************
 * Checks if the user wants to use a maze file.
 * 
 * @return true if the user wants to use a maze file, false otherwise.
 ******************************************************************************************/
bool useMazeFile();

/******************************************************************************************
 * Uploads the graph from a maze file.
 * 
 * @param width The width of the maze.
 * @param height The height of the maze.
 * @param graph The graph to upload the maze to.
 ******************************************************************************************/
void uploadGraph(int *width, int *height, Graph *graph);

/******************************************************************************************
 * Generates a graph for the maze.
 * 
 * @param width The width of the maze.
 * @param height The height of the maze.
 * @param graph The graph to generate the maze on.
 ******************************************************************************************/
void generateGraph(int *width, int *height, Graph *graph);

/******************************************************************************************
 * Prompts the user to choose an algorithm for maze generation.
 * 
 * @return The chosen algorithm.
 ******************************************************************************************/
int chooseAlgo();

/******************************************************************************************
 * Asks the user if they want to save the generated maze to a file.
 * 
 * @return true if the user wants to save the maze to a file, false otherwise.
 ******************************************************************************************/
bool doYouSaveFile();

/******************************************************************************************
 * Saves the generated maze to a file.
 * 
 * @param maze The maze to save.
 ******************************************************************************************/
void saveFile(Maze *maze);

#endif // APP_GENERATE_MAZE_H