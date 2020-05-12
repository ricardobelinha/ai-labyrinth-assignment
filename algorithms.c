/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   algorithms.c
 * Author: Ricardo
 * 
 * Created on 23 de Outubro de 2019, 23:14
 */

#include "algorithms.h"
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITERATIONS 1000
#define BFS 1
#define ASTAR 2

Cell *findCellByType(Cell *maze, int size, int type) {
    for (int i = 0; i < size * size; i++) {
        if (maze[i].type == type) return &(maze[i]);
    }
    return NULL;
}

Cell *findCellByCoordinates(Cell *maze, int size, int row, int column) {
    if (row < 0 || column < 0)
        return NULL;

    for (int i = 0; i < size * size; i++) {
        if (maze[i].row == row && maze[i].column == column) return &(maze[i]);
    }

    return NULL;
}

bool isCellPathable(Cell cell) {
    return cell.type != CELL_WALL && !cell.visited;
}

void getPathToRoot(Cell *current, Cell *maze, int size) {
    Cell *iterator = findCellByCoordinates(maze, size, current->parent.row, current->parent.column);

    while (iterator != NULL && iterator->type != CELL_START) {
        iterator->type = CELL_PATH;
        iterator = findCellByCoordinates(maze, size, iterator->parent.row, iterator->parent.column);
    }
}

int getBestCellFromQueue(Queue queue, int method) {
    double bestValue = -1, currentValue;
    int bestIndex = -1;

//    printf("Queue size: %d\n", queue.queueSize);

    for (int i = 0; i < queue.queueSize; i++) {
        if (method == BFS) {
            currentValue = getCellHValue(i, queue);
        } else /* if (method == ASTAR) */{
            currentValue = getCellGPlusHValue(i, queue);
        }
        if (bestIndex == -1 || bestValue > currentValue) {
            bestIndex = i;
            bestValue = currentValue;
        }
    }

    return bestIndex;
}

int applyAlgorithm(int method, Cell *maze, int size, int *unsolved) {
    Queue queue;
    int moves = 0, iterations = 0, index;
    Cell *current;
    // Start priority queue
    initQueue(&queue);

    // Add start node to queue (current)
    current = findCellByType(maze, size, CELL_START);
    addToQueue(current, &queue);
    // Mark current visited
    current->visited = 1;
    // seek a path to the target until the queue is empty
    while (iterations <= MAX_ITERATIONS && !isQueueEmpty(queue)) {
        // Gets cell from queue with lower heuristic or cost + heuristic
        index = getBestCellFromQueue(queue, method);
        if (index == -1) {
            printf("[WARNING] Queue is empty");
            break;
        }

        current = queue.cells[index];
        removeFromQueue(queue.cells[index], &queue);
        moves++;

        // if we have reached the target we are done
        if (current->type == CELL_FINISH) {
            getPathToRoot(current, maze, size);
            break;
        }

        // we are not at the target so add all unvisited nodes that are adjacent to the current node to the queue
        // we only consider orthogonally connected unblocked, unvisited cells, there are there row / column offsets relative
        // to the current location

        // orthogonal neighbor offsets (row/column pairs)
        int offsets[] = {1, 0, 0, -1, -1, 0, 0, 1};

        for (int i = 0; i < 8; i += 2) {
            int row = current->row + offsets[i];
            int column = current->column + offsets[i + 1];

            if (row < 0 || row >= size || column < 0 || column >= size)
                continue;

            Cell *newCell = findCellByCoordinates(maze, size, row, column);

            if (newCell != NULL && isCellPathable(*newCell)) {
                // mark cell as visited
                newCell->visited = 1;
                // we can also mark its parent now
                newCell->parent.row = current->row;
                newCell->parent.column = current->column;
                // add the newly discovered vertex to the queue
                addToQueue(newCell, &queue);
            }
        }
        iterations++;
    }

    displayLabyrinth(maze, size);

    if (iterations == MAX_ITERATIONS) {
        printf("\n[WARNING] Maximum iterations exceeded.\n");
    }
    if (current->type != CELL_FINISH) {
        printf("\nUnsolvable problem.\n");
        (*unsolved)++;
        return 0; // Moves from an unsolved problem don't count.
    } else {
        printf("\nReached the end of the labyrinth!\n");
    }

    return moves;
}

int applyBestFirstSearch(Cell *maze, int size, int *unsolved) {
    return applyAlgorithm(BFS, maze, size, unsolved);
}

int applyAStar(Cell *maze, int size, int *unsolved) {
    return applyAlgorithm(ASTAR, maze, size, unsolved);
}