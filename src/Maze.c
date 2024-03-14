#include "../include/Maze.h"

Maze *createMaze(Graph *graph, int width, int height, char *typePrim) {
    PrimResult *resultPrim = NULL;

    if (strcmp(typePrim, "heap") == 0) {
        resultPrim = primHeap(graph, true);
    } else {
        resultPrim = prim(graph, true);
    }

    Maze *maze = (Maze *)malloc(sizeof(Maze));
    maze->width = 2 * width - 1;
    maze->height = 2 * height - 1;

    maze->matrix = (bool **)malloc(maze->height * sizeof(bool *));
    for (int i = 0; i < maze->height; i++) {
        maze->matrix[i] = (bool *)malloc(maze->width * sizeof(bool));
        for (int j = 0; j < maze->width; j++) {
            maze->matrix[i][j] = false;

            if (i % 2 == 0 && j % 2 == 0) {
                maze->matrix[i][j] = true;
            }
        }
    }

    for (int i = 1; i < graph->numNodes; i++) {
        int predecessor = resultPrim->predecessors[i];
        int rowGraphPredecessor = predecessor / width;
        int colGraphPredecessor = predecessor % width;
        int rowMazePredecessor = rowGraphPredecessor * 2;
        int colMazePredecessor = colGraphPredecessor * 2;

        int rowGraphCurrent = i / width;
        int colGraphCurrent = i % width;
        int rowMazeCurrent = rowGraphCurrent * 2;
        int colMazeCurrent = colGraphCurrent * 2;

        int rowMazeMiddle = (rowMazePredecessor + rowMazeCurrent) / 2;
        int colMazeMiddle = (colMazePredecessor + colMazeCurrent) / 2;

        maze->matrix[rowMazeMiddle][colMazeMiddle] = true;
    }

    free(resultPrim->predecessors);
    free(resultPrim);

    return maze;
}

void freeMaze(Maze *maze) {
    for (int i = 0; i < maze->height; i++) {
        free(maze->matrix[i]);
    }
    free(maze->matrix);
    free(maze);
}

void printPPM(Maze *maze, char *filename) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "P1\n");
    fprintf(file, "%d %d\n", maze->width + 2, maze->height + 2);
    
    for (int i = 0; i < maze->width + 2; i++) {
        fprintf(file, "0 ");
    }
    fprintf(file, "\n");

    for (int i = 0; i < maze->height; i++) {
        fprintf(file, "0 ");
        for (int j = 0; j < maze->width; j++) {
            fprintf(file, "%d ",  maze->matrix[i][j] ? 1 : 0);
        }
        fprintf(file, "0\n");
    }

    for (int i = 0; i < maze->width + 2; i++) {
        fprintf(file, "0 ");
    }
    fprintf(file, "\n");

    fclose(file);
}

void printMaze(Maze *maze) {
    printf("\n%*sMaze\n", maze->width - 1, "");
    for (int i = 0; i < maze->width + 2; i++) {
        printf("# ");
    }
    printf("\n");

    for (int i = 0; i < maze->height; i++) {
        printf("# ");
        for (int j = 0; j < maze->width; j++) {
            printf("%s", maze->matrix[i][j] ? "  " : "# ");
        }
        printf("#\n");
    }

    for (int i = 0; i < maze->width + 2; i++) {
        printf("# ");
    }
    printf("\n");
}