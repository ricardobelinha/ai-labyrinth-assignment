/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   logic.h
 * Author: Ricardo
 *
 * Created on 22 de Outubro de 2019, 9:07
 */

#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>

#define CELL_OPEN 0
#define CELL_WALL 1
#define CELL_START 2
#define CELL_FINISH 3
#define CELL_PATH 4

#define EUCLIDEAN 1
#define MANHATTAN 2

typedef struct {
    int column, row;
} Parent;

typedef struct {
    int visited; // To know if this Cell was visited before
    int column, row; // Cell position - little waste of memory, but it allows faster generation
    int type; // Type of Cell (OPEN, WALL, START, FINISH, PATH)
    double cost; // Distance between the current cell and the start cell
    double heuristic; // Heuristic value «(Euclidean or Manhattan distance) of the current cell to the finish cell
    Parent parent;  // Coordinates of parent node
} Cell;

typedef struct {
    Cell** cells;
    int queueSize;
} Queue;

void initQueue(Queue *queue);
void addToQueue(Cell *cell, Queue *queue);
void removeFromQueue(Cell* cellToRemove, Queue *queue);
bool isQueueEmpty(Queue queue);
double getCellGPlusHValue(int index, Queue queue);
double getCellHValue(int index, Queue queue);

void generateAndResolveLabyrinth(int size, int walls, int runs, int heuristicFunction);

#endif /* LOGIC_H */
