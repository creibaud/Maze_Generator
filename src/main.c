#include "../include/AppGenerateMaze.h"

int main(int argc, char *argv[]) {
    int width, height;
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	Maze *maze;

    if (argc == 2) {
        char *filename = argv[1];
        FileLoaded *fileLoaded = loadGraph(filename);
        if (fileLoaded == NULL) {
            fprintf(stderr, "\033[33;91mError loading file\033[0m\n");
            free(graph);
            exit(EXIT_FAILURE);
        }

        width = fileLoaded->width;
        height = fileLoaded->height;
        *graph = *fileLoaded->graph;

        free(fileLoaded);
    } else {
        bool userUseMazeFile = useMazeFile();

        if (userUseMazeFile) {
            uploadGraph(&width, &height, graph);
        } else {
            generateGraph(&width, &height, graph);
        }
    }

	int algorithm = chooseAlgo();

	if (algorithm == 1) {
		maze = createMaze(graph, width, height, "naive");
	} else {
		maze = createMaze(graph, width, height, "heap");
	}

	printGraph(graph);
    freeGraph(graph);

	printMaze(maze);

	bool userSaveFile = doYouSaveFile();

	if (userSaveFile) {
		saveFile(maze);
	}

    freeMaze(maze);

    exit(EXIT_SUCCESS);
}