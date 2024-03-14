#include "../include/Load.h"

FileLoaded *loadGraph(char *filename) {
    FILE *file = fopen(filename, "r");

    printf("Loading graph from %s\n", filename);

    if (file == NULL) {
        fprintf(stderr, "\033[33;91mError opening file\033[0m\n");
        exit(EXIT_FAILURE);
    }

    FileLoaded *fileLoaded = (FileLoaded *)malloc(sizeof(FileLoaded));
    
    int fscanfResult = fscanf(file, "%d %d", &fileLoaded->width, &fileLoaded->height);
    fileLoaded->graph = createGraph(fileLoaded->width * fileLoaded->height);

    while (fscanfResult != EOF) {
        int idSourceNode;
        int idDestinationNode;
        int cost;

        fscanfResult = fscanf(file, "%d %d %d", &idSourceNode, &idDestinationNode, &cost);

        if (fscanfResult != 3) {
            break;
        }

        addEdge(fileLoaded->graph, idSourceNode, idDestinationNode, cost);
    }
    
    fclose(file);

    return fileLoaded;
}