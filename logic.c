/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   logic.c
 * Author: Ricardo
 * 
 * Created on 22 de Outubro de 2019, 9:07
 */

#include "visual.h"
#include "utils.h"
#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double getEuclideanHFunction(Cell current, Cell finish) {
    // Euclidean distance from current to end
    return euclideanDistance(current.row, current.column, finish.row, finish.column);
}

int getManhattanFunction(Cell current, Cell target) {
    // Euclidean distance from current to end
    return manhattanDistance(current.row, current.column, target.row, target.column);
}

void setHeuristicValues(Cell *maze, int size, int heuristicFunction) {
    Cell *finish = findCellByType(maze, size, CELL_FINISH);
    Cell *start = findCellByType(maze, size, CELL_START);

    if (finish == NULL) {
        fprintf(stderr, "Unexpected error: labyrinth doesn't have the finish cell.");
        exit(-1);
    }

    for (int i = 0; i < size * size; i++) {
        maze[i].cost = getManhattanFunction(maze[i], *start);
        if (heuristicFunction == EUCLIDEAN)
            maze[i].heuristic = getEuclideanHFunction(maze[i], *finish);
        else if (heuristicFunction == MANHATTAN)
            maze[i].heuristic = getManhattanFunction(maze[i], *finish);
    }
}

void initializeLabyrinth(Cell *maze, int size, int walls, int heuristicFunction) {
    for (int i = 0; i < size * size; i++) {
        maze[i].row = i / size;
        maze[i].column = i % size;
        maze[i].visited = 0;

        if (maze[i].row == 1 && maze[i].column == 0) {
            maze[i].type = CELL_START;
        } else if (maze[i].row == size - 2 && maze[i].column == size - 1) {
            maze[i].type = CELL_FINISH;
        } else if (maze[i].row == size - 1 || maze[i].row == 0 || maze[i].column == size - 1 || maze[i].column == 0) {
            maze[i].type = CELL_WALL;
        } else {
            if (walls >= getRandomNumber(100)) {
                maze[i].type = CELL_WALL;
            } else {
                maze[i].type = CELL_OPEN;
            }
        }
    }

    setHeuristicValues(maze, size, heuristicFunction);
}

void cleanMaze(Cell *maze, int size) {
    for (int i = 0; i < size * size; i++) {
        maze[i].visited = 0;
    }
}

void generateAndResolveLabyrinth(int size, int walls, int runs, int heuristicFunction) {
    Cell maze[size * size];
    int movesBFS, allMovesBFS = 0, unsolvedProblemsBFS = 0;
    int movesAStar, allMovesAStar = 0, unsolvedProblemsAStar = 0;
    double averageMoves;

    for (int it = 1; it <= runs; it++) {
        printf("\nRun #%d\n", it);
        initializeLabyrinth(maze, size, walls, heuristicFunction);
        printf("\nA Star method\n");
        movesAStar = applyAStar(maze, size, &unsolvedProblemsAStar);
        printf("Moves on run #%d: %d\n", it, movesAStar);
        allMovesAStar += movesAStar;
        cleanMaze(maze, size);
        printf("\nBest First Search method\n");
        movesBFS = applyBestFirstSearch(maze, size, &unsolvedProblemsBFS);
        printf("Moves on run #%d: %d\n", it, movesBFS);
        allMovesBFS += movesBFS;

    }
    printf("\nALL MOVES A*: %d\n", allMovesAStar);
    printf("\nTotal unsolved problems A*: %d\n", unsolvedProblemsAStar);
    averageMoves = (double) allMovesAStar / (runs - unsolvedProblemsAStar);
    writeToFile("AStar", size, averageMoves, unsolvedProblemsAStar);

    printf("\nALL MOVES BFS: %d\n", allMovesBFS);
    printf("\nTotal unsolved problems BFS: %d\n", unsolvedProblemsBFS);
    averageMoves = (double) allMovesBFS / (runs - unsolvedProblemsBFS);
    writeToFile("BestFirstSearch", size, averageMoves, unsolvedProblemsBFS);
}

// Priority queue management
void initQueue(Queue *queue) {
    queue->cells = NULL;
    queue->queueSize = 0;
}

void add(Queue *queue) {
    Cell **newQueue;

    if (queue->cells == NULL) {
        newQueue = malloc(sizeof(Cell *));
    } else {
        newQueue = realloc(queue->cells, (queue->queueSize + 1) * sizeof(Cell *));
    }
    if (newQueue == NULL) {
        printf("%s\n", strerror(errno));
        printf("\n[DEBUG] Error on increasing queue\n");
    } else {
        queue->cells = newQueue;
        queue->queueSize += 1;
    }
}

void delete(Cell *cellToRemove, Queue *queue) { // "remove" already exists in <stdio.h>
    Cell **newQueue = NULL;
    bool decreaseStack = false;

    if (queue->queueSize == 0)
        return;

    if (queue->queueSize > 1) {
        newQueue = malloc((queue->queueSize - 1) * sizeof(Cell *));
        if (newQueue == NULL) {
            printf("\n[DEBUG] Error on shortening queue\n");
        } else {
            for (int i = 0, j = 0; i < queue->queueSize; i++) {
                if (cellToRemove->row != queue->cells[i]->row ||
                    cellToRemove->column != queue->cells[i]->column) { // remove cell
                    newQueue[j++] = queue->cells[i];
                    decreaseStack = true;
                }
            }
            free(queue->cells);
            queue->cells = newQueue;
            if (decreaseStack) {
                queue->queueSize = queue->queueSize - 1;
            }
        }
    } else {
        free(queue->cells);
        queue->cells = NULL;
        queue->queueSize = 0;
    }
}

void addToQueue(Cell *cell, Queue *queue) {
    add(queue);
    queue->cells[queue->queueSize - 1] = cell;
}

double getCellGPlusHValue(int index, Queue queue) {
    return queue.cells[index]->cost + queue.cells[index]->heuristic;
}

double getCellHValue(int index, Queue queue) {
    return queue.cells[index]->heuristic;
}

bool isQueueEmpty(Queue queue) {
    return queue.queueSize == 0;
}

void removeFromQueue(Cell *cellToRemove, Queue *queue) {
    int size = queue->queueSize;

    if (size > 0 && cellToRemove != NULL) {
        delete(cellToRemove, queue);
    }
}