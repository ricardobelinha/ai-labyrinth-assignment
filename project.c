/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.c
 * Author: Ricardo
 * 
 * Created on 22 de Outubro de 2019, 8:52
 */

#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include "visual.h"
#include "logic.h"

#define MAX_RUNS 1000

int askPercentageOfWalls() {
    int walls;
    do {
        newLine(2);
        printf("\t\t\t\tPercentage of walls inside the labyrinth: ");
        scanf(" %d", &walls);
    } while (walls < 0 || walls > 100);
    return walls;
}

int askNumberOfRepetitions() {
    int runs;
    do {
        printf("\t\t\t\tNumber of repetitions for the algorithms: ");
        scanf(" %d", &runs);
    } while (runs < 0 || runs > MAX_RUNS);
    return runs;
}

int askHeuristicFunction() {
    int option;
    do {
        printf("\t\t\t\tHeuristic function to be applied:\n");
        printf("\t\t\t\t%d-Euclidean distance\n\t\t\t\t%d-Manhattan distance\n\n\t\t\t\tAnswer: ", EUCLIDEAN, MANHATTAN);
        scanf(" %d", &option);
    } while (option != EUCLIDEAN && option != MANHATTAN);
    return option;
}

/**
 * Menu function, where the loop to run the program is created.
 */
void menu() {
    int sair = 0, op, walls, runs, heuristicFunction;

    while (!sair) {
        showMenu();
        scanf(" %d", &op);

        switch (op) {
            case 0:
                sair = 1;
                break;
            case 1:
            case 2:
                walls = askPercentageOfWalls();
                runs = askNumberOfRepetitions();
                heuristicFunction = askHeuristicFunction();
                generateAndResolveLabyrinth(10 + op * 10, walls, runs, heuristicFunction);
                break;
            default:
                break;
        }
    }
    newLine(2);
}