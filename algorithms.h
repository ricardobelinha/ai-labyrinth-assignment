/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   algorithms.h
 * Author: Ricardo
 *
 * Created on 23 de Outubro de 2019, 23:14
 */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "visual.h"
Cell * findCellByType(Cell * maze, int size, int type);
int applyAStar(Cell * maze, int size, int * unsolved);
int applyBestFirstSearch(Cell * maze, int size, int * unsolved);
#endif /* ALGORITHMS_H */
