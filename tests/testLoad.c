#include "../include/Load.h"

int main(int argc, char *argv[]) {
    printf("\nTest loadGraph\n");

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FileLoaded *fileLoaded = loadGraph(argv[1]);
    printGraph(fileLoaded->graph);

    return 0;
}