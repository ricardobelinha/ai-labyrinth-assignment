/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.c
 * Author: Ricardo
 * 
 * Created on 23 de Outubro de 2019, 19:31
 */

#include "utils.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define FILE_NAME "results.txt"

void initializeRandom() {
    srand(time(NULL));
}

int getRandomNumber(int max) {
    return rand() % max;
}

double euclideanDistance(int xCurrent, int yCurrent, int xTarget, int yTarget) {
    return fabs(sqrt(pow((double) xTarget - (double) xCurrent, 2) + pow((double) yTarget - (double) yCurrent, 2)));
}

int manhattanDistance(int xCurrent, int yCurrent, int xTarget, int yTarget) {
    return abs(xCurrent - xTarget) + abs(yTarget - yCurrent);
}

void writeToFile(char *methodName, int size, double moves, int unsolvedProblems) {
    FILE *f;

    f = fopen(FILE_NAME, "at");
    if (f == NULL) {
        puts("[ERROR] File not able to open");
        return;
    }
    fprintf(f, "%s;%d;%d;%.2lf;%d\n", methodName, size, size, moves, unsolvedProblems);

    fclose(f);
}