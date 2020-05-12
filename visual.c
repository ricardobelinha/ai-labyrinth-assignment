/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   visual.c
 * Author: Ricardo
 * 
 * Created on 22 de Outubro de 2019, 8:37
 */

#include "visual.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function to display the name of the class.
 */
void displayLogo() {
    printf("\n\n\t                _   _  __ _      _       _   _____       _       _ _ _                           \n");
    printf("\t     /\\        | | (_)/ _(_)    (_)     | | |_   _|     | |     | | (_)                          \n");
    printf("\t    /  \\   _ __| |_ _| |_ _  ___ _  __ _| |   | |  _ __ | |_ ___| | |_  __ _  ___ _ __   ___ ___ \n");
    printf("\t   / /\\ \\ | '__| __| |  _| |/ __| |/ _` | |   | | | '_ \\| __/ _ \\ | | |/ _` |/ _ \\ '_ \\ / __/ _ \\\n");
    printf("\t  / ____ \\| |  | |_| | | | | (__| | (_| | |  _| |_| | | | ||  __/ | | | (_| |  __/ | | | (_|  __/\n");
    printf("\t /_/    \\_\\_|   \\__|_|_| |_|\\___|_|\\__,_|_| |_____|_| |_|\\__\\___|_|_|_|\\__, |\\___|_| |_|\\___\\___|\n");
    printf("\t                                                                        __/ |                    \n");
    printf("\t                                                                       |___/                     \n\n");
}

/**
 * Function to display project number and who has created.
 */
void displayCredits() {
    printf("\t\t\tFirst Assignment - Project number 41 - developed by Ricardo Belinha.\n\n");
}

/**
 * Function to display the menu options.
 */
void showMenu() {
    printf("\n\n");
    printf("\t\t\t\t\t\tMenu\n");
    printf("\t\t\t\t1 - Generate random labyrinth 20x20\n");
    printf("\t\t\t\t2 - Generate random labyrinth 30x30\n");
    printf("\t\t\t\t0 - Exit\n\n");

    printf("\t\t\t\tAnswer: ");
}

/**
 * Function to display empty lines.
 * @param numLines Amount of empty lines to add.
 */
void newLine(int numLines) {
    for (int i = 0; i < numLines; i++) {
        printf("\n");
    }
}

/**
 * Function to display which problem our project resolve.
 */
void displayProblem() {
    printf("\t\t\" Comparison between A* and Best-First search (with h as the objective function)\n");
    printf("\t\t  for the labyrinth problemon the same labyrinth of size 20 by 20, then 30 by 30.\n");
    printf("\t\t  Generate random labyrinths with 5, 10, 20, 25, 30 percents of the space as \"walls\".\n");
    printf("\t\t  You should count the number cells visited. There will be a number of labyrinths\n");
    printf("\t\t  which have no solution.The output should be written in a text file as CSV values.\n");
    printf("\t\t  e.g. \"AStar; 20; 20; 253.35; 17\" meaning: for A* on 20 by 20 averaged number\n");
    printf("\t\t  of moves measured on 50 labyrinths is 253.35 ans 17 unsolvable problems \"\n");
}

void convertLabyrinth(Cell *mazeOriginal, int size, char maze[][size]) {
    char ch;
    for (int i = 0; i < size * size; i++) {
        switch (mazeOriginal[i].type) {
            case CELL_FINISH:
                ch = 'F';
                break;
            case CELL_START:
                ch = 'S';
                break;
            case CELL_WALL:
                ch = 219;
                break;
            case CELL_OPEN:
                if (mazeOriginal[i].visited)
                    ch = '@';
                else
                    ch = ' ';
                break;
            case CELL_PATH:
                ch = '#';
                break;
        }
        maze[mazeOriginal[i].row][mazeOriginal[i].column] = ch;
    }
}

/**
 * Function to display the labyrinth.
 * @param maze array of cells
 * @param size size of labyrinth
 */
void displayLabyrinth(Cell *mazeOriginal, int size) {
    char maze[size][size];

    convertLabyrinth(mazeOriginal, size, maze);

    printf("\n\n\t\t\t\t\tLabyrinth %dx%d\n\n", size, size);
    for (int i = 0; i < size; i++) {
        printf("\t\t\t\t");
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < NUM_DISPLAY_COLUMNS; k++) {
                putchar(maze[i][j]);
            }
        }
        putchar('\n');
    }
}

void printQueue(Queue queue) {
    printf("Printing queue:\n");
    for (int i = 0; i < queue.queueSize; i++) {
        printf("Cell[%d] in queue: Row: %d, Column: %d\n", i, queue.cells[i]->row, queue.cells[i]->column);
    }
}

void printCells(Cell *mazeOriginal, int size) {
    for (int i = 0; i < size * size; i++) {
        printf("Cell[%d] in maze: Row: %d, Column: %d\n", i, mazeOriginal[i].row, mazeOriginal[i].column);
    }
}
