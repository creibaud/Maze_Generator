#include <time.h>
#include <dirent.h>
#include <string.h>
#include "../include/Heap.h"

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("data/csv");
    if (dir == NULL) {
        fprintf(stderr, "\033[33;91mError opening directory\033[0m\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "dataComplexityHeap") != NULL) {
            count++;
        }
    }

    closedir(dir);

    char *fileName = malloc(200 * sizeof(char));
    sprintf(fileName, "data/csv/dataComplexityHeap%d.csv", count);

    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        fprintf(stderr, "\033[33;91mError opening file\033[0m\n");
        free(fileName);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "nb,time_to_insert,time_to_extract\n");

    for (int nb = 20; nb <= 1000000; nb *= 2) {
        MinHeap *heap = createMinHeap(nb);
        clock_t start, end;

        start = clock();
        for (int i = 0; i < nb; i++) {
            heap->nodes[i] = createMinHeapNode(i, i);
            heap->positions[i] = i;
            heap->size++;
        }
        end = clock();
        double time_to_insert = ((double) (end - start)) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = nb / 2 - 1; i >= 0; i--) {
            minHeapify(heap, i);
        }
        
        for (int i = 0; i < nb; i++) {
            extractMinHeapNode(heap);
        }
        end = clock();
        double time_to_extract = ((double) (end - start)) / CLOCKS_PER_SEC;

        fprintf(file, "%d,%f,%f\n", nb, time_to_insert, time_to_extract);

        free(heap->nodes);
        free(heap->positions);
        free(heap);
    }

    fclose(file);

    char command[256];
    sprintf(command, "python data/plotHeapComplexity.py %s", fileName);
    system(command);

    printf("%s\n", command);

    free(fileName);

    return 0;
}