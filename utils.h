/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: Ricardo
 *
 * Created on 23 de Outubro de 2019, 19:31
 */

#ifndef UTILS_H
#define UTILS_H
void initializeRandom();
int getRandomNumber(int max);
double euclideanDistance(int xCurrent, int yCurrent, int xTarget, int yTarget);
int manhattanDistance(int xCurrent, int yCurrent, int xTarget, int yTarget);
void writeToFile(char *methodName, int size, double moves, int unsolvedProblems);
#endif /* UTILS_H */
