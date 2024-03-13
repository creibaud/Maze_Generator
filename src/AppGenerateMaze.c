#include "../include/AppGenerateMaze.h"

bool useMazeFile() {
	char userInput;
	printf("Do you want to load a maze from a file? (y/n)\n");
	
	while (1) {
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
		exit(EXIT_FAILURE);
	}

	printf("Choose file to load the maze from upload/: \n");
	int count = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (strstr(entry->d_name, ".txt") != NULL) {
			printf("\033[33;33m%d.\033[0m %s\n", count, entry->d_name);
			fileNames[count] = entry->d_name;
			count++;
		}
	}
	closedir(dir);

	int fileNumber;
	while (1) {
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
	char *filePath = malloc(200 * sizeof(char));
	strcpy(filePath, "upload/");
	strcat(filePath, fileName);
	
	FileLoaded *fileLoaded = loadGraph(filePath);
	if (fileLoaded == NULL) {
		fprintf(stderr, "\033[33;91mError loading file\033[0m\n");
		exit(EXIT_FAILURE);
	}

	*width = fileLoaded->width;
	*height = fileLoaded->height;
	graph = fileLoaded->graph;
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
	graph = createGraph(w * h);
	int count = 0;
	int idSourceNode, idDestinationNode, cost;

	while (count < graph->numNodes) {
		printf("Enter the edges of the graph (source destination cost): ");
		printf("\033[33;92m>\033[0m \033[33;96m");
		int scanfResult = scanf("%d %d %d", &idSourceNode, &idDestinationNode, &cost);
		printf("\033[0m");

		if (scanfResult != 3) {
			fprintf(stderr, "\033[33;91mInvalid input. Please enter 3 integers\033[0m\n");
			continue;
		}

		if (idSourceNode < 0 || idSourceNode >= graph->numNodes || idDestinationNode < 0 || idDestinationNode >= graph->numNodes) {
			fprintf(stderr, "\033[33;91mInvalid input. Please enter valid nodes\033[0m\n");
			continue;
		}

		addEdge(graph, idSourceNode, idDestinationNode, cost);
		count++;
	}
}

int chooseAlgo() {
	printf("What algorithm do you want to use ?\n");
	printf("\033[33;33m1.\033[0m Naive Prim\n");
	printf("\033[33;33m2.\033[0m Prim with Heap\n");

	int algorithm;
	while (1) {
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
	
	while (1) {
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
}