/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   visual.h
 * Author: Ricardo
 *
 * Created on 22 de Outubro de 2019, 8:37
 */

#ifndef VISUAL_H
#define VISUAL_H
#include "logic.h"

#define NUM_DISPLAY_COLUMNS 2

void displayLogo();
void displayProblem();
void displayCredits();
void showMenu();
void newLine();
void displayLabyrinth(Cell * mazeOriginal, int size);
void printQueue(Queue queue);
void printCells(Cell * mazeOriginal, int size);
#endif /* VISUAL_H */
