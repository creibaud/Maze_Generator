#include "../include/AppGenerateMaze.h"

bool useMazeFile() {
	char userInput;
	printf("Do you want to load a maze from a file? (y/n)\n");
	
	while (true) {
		printf("\033[33;92m>\033[0m \033[33;96m");
		scanf("%c", &userInput);
		printf("\033[0m");

		if (userInput == 'y' || userInput == 'n') {
			break;
		} else {
			fprintf(stderr, "\033[33;91mInvalid input. Please enter 'y' or 'n'\033[0m\n");
		}
	}

	return userInput == 'y';
}

void uploadGraph(int *width, int *height, Graph *graph) {
	DIR *dir;
	struct dirent *entry;
	char **fileNames = malloc(100 * sizeof(char *));

	dir = opendir("upload/");
	if (dir == NULL) {
		fprintf(stderr, "\033[33;91mError opening directory\033[0m\n");
		for (int i = 0; i < 100; i++) {
			free(fileNames[i]);
		}
		free(fileNames);
		free(graph);
		exit(EXIT_FAILURE);
	}

	printf("Choose file to load the maze from upload/: \n");
	int count = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (strstr(entry->d_name, ".txt") != NULL) {
			printf("\033[33;33m%d.\033[0m %s\n", count, entry->d_name);
			fileNames[count] = malloc(strlen(entry->d_name) + 1);
            strcpy(fileNames[count], entry->d_name);
			count++;
		}
	}
	closedir(dir);

	int fileNumber;
	while (true) {
		printf("\033[33;92m>\033[0m \033[33;96m");
		scanf("%d", &fileNumber);
		printf("\033[0m");

		if (fileNumber >= 0 && fileNumber < count) {
			break;
		} else {
			fprintf(stderr, "\033[33;91mInvalid input. Please enter a valid number\033[0m\n");
		}
	}

	char *fileName = fileNames[fileNumber];
	for (int i = 0; i < count; i++) {
		if (i != fileNumber) {
			free(fileNames[i]);
		}
	}
	free(fileNames);

	char *filePath = malloc(200 * sizeof(char));
	strcpy(filePath, "upload/");
	strcat(filePath, fileName);
	
	FileLoaded *fileLoaded = loadGraph(filePath);
	if (fileLoaded == NULL) {
		fprintf(stderr, "\033[33;91mError loading file\033[0m\n");
		free(fileName);
		free(filePath);
		free(graph);
		exit(EXIT_FAILURE);
	}

	*width = fileLoaded->width;
	*height = fileLoaded->height;
	*graph = *fileLoaded->graph;

	free(fileName);
	free(filePath);
	free(fileLoaded);
}

void generateGraph(int *width, int *height, Graph *graph) {
	printf("Enter the width of the graph: ");
	printf("\033[33;92m>\033[0m \033[33;96m");
	scanf("%d", width);
	printf("\033[0m");

	printf("Enter the height of the graph: ");
	printf("\033[33;92m>\033[0m \033[33;96m");
	scanf("%d", height);
	printf("\033[0m");

	int w = *width;
	int h = *height;
	*graph = *createGraph(w * h);
	int idSourceNode, idDestinationNode, cost;
	int numVertices;

	for (idSourceNode = 0; idSourceNode < graph->numNodes; idSourceNode++) {
		while (true) {
			printf("Enter the number of vertices connected to vertex %d: ", idSourceNode);
			printf("\033[33;92m>\033[0m \033[33;96m");
			scanf("%d", &numVertices);
			printf("\033[0m");

			if (numVertices >= 0 && numVertices < graph->numNodes) {
				break;
			} else {
				fprintf(stderr, "\033[33;91mInvalid input. Please enter a valid number\033[0m\n");
			}
		}

		for (int i = 0; i < numVertices; i++) {
			while (true) {
				printf("Enter the ID of the destination vertex: ");
				printf("\033[33;92m>\033[0m \033[33;96m");
				scanf("%d", &idDestinationNode);
				printf("\033[0m");

				if (idDestinationNode >= 0 && idDestinationNode < graph->numNodes) {
					break;
				} else {
					fprintf(stderr, "\033[33;91mInvalid input. Please enter a valid number\033[0m\n");
				}
			}

			printf("Enter the cost of the edge: ");
			printf("\033[33;92m>\033[0m \033[33;96m");
			scanf("%d", &cost);
			printf("\033[0m");

			addEdge(graph, idSourceNode, idDestinationNode, cost);
		}
	}
}

int chooseAlgo() {
	printf("What algorithm do you want to use ?\n");
	printf("\033[33;33m1.\033[0m Naive Prim\n");
	printf("\033[33;33m2.\033[0m Prim with Heap\n");

	int algorithm;
	while (true) {
		printf("\033[33;92m>\033[0m \033[33;96m");
		scanf("%d", &algorithm);
		printf("\033[0m");

		if (algorithm == 1 || algorithm == 2) {
			break;
		} else {
			fprintf(stderr, "\033[33;91mInvalid input. Please enter 1 or 2\033[0m\n");
		}
	}

	return algorithm;
}

bool doYouSaveFile() {
	char userInput;
	printf("Do you want to save the maze to a file ? (y/n)\n");
	
	while (true) {
		printf("\033[33;92m>\033[0m \033[33;96m");
		scanf("%c", &userInput);
		printf("\033[0m");

		if (userInput == 'y' || userInput == 'n') {
			break;
		} else {
			fprintf(stderr, "\033[33;91mInvalid input. Please enter 'y' or 'n'\033[0m\n");
		}
	}

	return userInput == 'y';
}

void saveFile(Maze *maze) {
	printf("Enter the name of the file: ");
	char *fileName = malloc(100 * sizeof(char));
	printf("\033[33;92m>\033[0m ");
	scanf("%s", fileName);
	
	char *filePath = malloc(200 * sizeof(char));
	strcpy(filePath, "generated/");
	strcat(filePath, fileName);
	strcat(filePath, ".ppm");

	printPPM(maze, filePath);

	free(fileName);
	free(filePath);
}